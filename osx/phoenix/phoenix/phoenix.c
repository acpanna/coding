/*
 * osx kernel phoenix module
 */

#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <sys/fcntl.h>
#include <sys/syscall.h>
#include <sys/systm.h>
#include <sys/uio.h>
#include <sys/vnode.h>

// #include <sys/types.h>
// #include <mach/mach_types.h>
// #include <sys/kernel.h>

#define _DEBUG_

#define SYSENT_NSYSENT_OFFSET   0x1c028
#define SYSENT_SCAN_RANGE       0x20000

#define PT_DENY_ATTACH 31

#ifdef _DEBUG_
#define LOG(args...)   printf(args)
#else
#define LOG(args...)   /* */
#endif

#define PAD(t) (sizeof(uint64_t) <= sizeof(t) ? 0 : sizeof(uint64_t) - sizeof(t))

#if BYTE_ORDER == LITTLE_ENDIAN
#define PADL(t) 0
#define PADR(t) PAD(t)
#else
#define PADL(t) PAD(t)
#define PADR(t) 0
#endif

struct ptrace_args {
    
    char req_l_[PADL(int)];
    int req;
    char req_r_[PADR(int)];
    
    char pid_l_[PADL(pid_t)];
    pid_t pid;
    char pid_r_[PADR(pid_t)];
    
    char addr_l_[PADL(caddr_t)];
    caddr_t addr;
    char addr_r_[PADR(caddr_t)];
    
    char data_l_[PADL(int)];
    int data;
    char data_r_[PADR(int)];
};

typedef int	ptrace_func_t (struct proc *, struct ptrace_args *, int *);

/* struct sysent -- see: xnu/bsd/sys/sysent.h ... */

typedef int32_t sy_call_t(struct proc *, void *, int *);
typedef void sy_munge_t(const void *, void *);

struct sysent {
    int16_t     sy_narg;
    int8_t      sy_resv;
    int8_t      sy_flags;
    sy_call_t   *sy_call;
    sy_munge_t  *sy_arg_munge32;
    sy_munge_t	*sy_arg_munge64;
    int32_t     sy_return_type;
    uint16_t    sy_arg_bytes;
};

/* Clear the WP flag in the Control Register CR0 */

#define DISABLE_WRITE_PROTECTION()  __asm__ volatile(   \
"cli\n"                                             \
"mov    %cr0,%rax\n"                                \
"and    $0xfffffffffffeffff,%rax\n"                 \
"mov    %rax,%cr0"                                  \
)

/* Set the WP flag in the Control Register CR0 */

#define ENABLE_WRITE_PROTECTION()   __asm__ volatile(   \
"mov    %cr0,%rax\n"                                \
"or     $0x10000,%rax\n"                            \
"mov    %rax,%cr0\n"                                \
"sti"                                               \
)

kern_return_t phoenix_start(kmod_info_t * ki, void *d);
kern_return_t phoenix_stop(kmod_info_t *ki, void *d);

/* --- ********* ---- * ---- ********* --- */

uint64_t kernelbase_addr;

int *nsysent;
struct sysent *sysent;

ptrace_func_t *original_ptrace;

vm_offset_t kaslr_offset = -2;

/* --- ********* ---- * ---- ********* --- */

static uint64_t kernelbase_address( )
{
    struct IDT_R { // IDT register
        uint16_t limit;
        uint8_t address[8];
    } idtr;
    
    struct IDT_ED { // IDT entry descriptor
        uint16_t offset_low;
        uint16_t seg_selector;
        uint8_t reserved;
        uint8_t flag;
        uint16_t offset_middle;
        
        uint32_t offset_high;
        uint32_t reserved2;
    } int0_descriptor;
    
    uint8_t temp_buffer[4];
    
    uint32_t middle;
    uint64_t high, idt, int0;
    
    __asm__ volatile ("sidt %0": "=m" (idtr));
    
    idt = *((uint64_t *) &idtr.address);
    
    LOG("[phoenix] IDT address: 0x%llx\n", idt);
    
    bcopy((void*) idt, &int0_descriptor, sizeof(struct IDT_ED));
    
    high = (uint64_t) int0_descriptor.offset_high << 32;
    middle = (uint32_t) int0_descriptor.offset_middle << 16;
    
    int0 = (uint64_t)(high + middle + int0_descriptor.offset_low);
    
    LOG("[phoenix] INT0 address: 0x%llx\n", int0);
    
    while (int0 > 0) {
        
        bcopy((void *) int0, temp_buffer, 4);
        
        if (*(uint32_t *) (temp_buffer) == MH_MAGIC_64) {
            LOG("[phoenix] Mach-Kernel address: 0x%llx\n", int0);
            return int0;
        }
        
        int0 -= 1;
    }
    
    return 0;
}

struct segment_command_64* find_segment_64(struct mach_header_64 *mh, const char *segname)
{
    struct load_command *lc = (struct load_command *) ((uint64_t) mh + sizeof(struct mach_header_64));
    
    while ((uint64_t) lc < (uint64_t) mh + (uint64_t) mh->sizeofcmds) {
        
        if (lc->cmd == LC_SEGMENT_64)
            if (strcmp(((struct segment_command_64 *) lc)->segname, segname) == 0)
                return (struct segment_command_64 *) lc;
        
        lc = (struct load_command *) ((uint64_t) lc + (uint64_t) lc->cmdsize);
    }
    
    return NULL;
}

struct load_command* find_load_command(struct mach_header_64 *mh, uint32_t cmd)
{
    struct load_command *lc = (struct load_command *) ((uint64_t) mh + sizeof(struct mach_header_64));
    
    while ((uint64_t) lc < (uint64_t) mh + (uint64_t) mh->sizeofcmds) {
        
        if (lc->cmd == cmd)
            return (struct load_command *) lc;
        
        lc = (struct load_command *) ((uint64_t) lc + (uint64_t) lc->cmdsize);
    }
    
    return NULL;
}

static int* find_symbol(struct mach_header_64 *mh, const char *name)
{
    static struct segment_command_64 *linkedit;
    static struct symtab_command *symtab;
    
    static char *strtab = NULL;
    
    struct nlist_64 *nl;
    
    uint64_t i;
    
    if (strtab == NULL) {
        
        if (mh->magic != MH_MAGIC_64) {
            LOG("[phoenix] Magic kernel number doesn't match - 0x%x\n", mh->magic);
            return NULL;
        }
        
        linkedit = find_segment_64(mh, SEG_LINKEDIT); // Find LINKEDIT segment
        
        if (!linkedit) {
            LOG("[phoenix] Couldn't find LINKEDIT segment!\n");
            return NULL;
        }
        
        symtab = (struct symtab_command *) find_load_command(mh, LC_SYMTAB);
        
        if (!symtab) {
            LOG("[phoenix] Couldn't find SYMTAB load command!\n");
            return NULL;
        }
        
        strtab = (char *) linkedit->vmaddr + (symtab->stroff - linkedit->fileoff);
        LOG("[phoenix] String table address 0x%llx\n", (uint64_t) strtab);
    }
    
    /* Search for the desired symbol ... */
    
    nl = (struct nlist_64 *) (linkedit->vmaddr + (symtab->symoff - linkedit->fileoff));
    
    for (i=0; i<symtab->nsyms; i++) {
        
        if (strcmp(strtab + nl->n_un.n_strx, name) == 0)
            return (int *) nl->n_value;
        
        nl = (struct nlist_64 *) ((uint64_t) nl + sizeof(struct nlist_64));
    }
    
    return NULL;
}

static boolean_t check_sysent(struct sysent *sysent)
{
    /* Sanity check */
    
    if (sysent[SYS_syscall].sy_narg == 0 && sysent[SYS_fork].sy_narg == 0 &&
        sysent[SYS_exit].sy_narg == 1 && sysent[SYS_read].sy_narg == 3 &&
        sysent[SYS_ptrace].sy_narg == 4 && sysent[SYS_wait4].sy_narg == 4 &&
        
        sysent[SYS_fork].sy_call
        == (sy_call_t *) find_symbol((struct mach_header_64 *) kernelbase_addr, "_fork") &&
        sysent[SYS_exit].sy_call
        == (sy_call_t *) find_symbol((struct mach_header_64 *) kernelbase_addr, "_exit") &&
        sysent[SYS_read].sy_call
        == (sy_call_t *) find_symbol((struct mach_header_64 *) kernelbase_addr, "_read") &&
        sysent[SYS_ptrace].sy_call
        == (sy_call_t *) find_symbol((struct mach_header_64 *) kernelbase_addr, "_ptrace")) {
        
        return TRUE;
    }
    
    return FALSE;
}

static struct sysent* locate_sysent(int *_nsysent)
{
    struct sysent* _sysent;
    long offset;
    
    _sysent = (struct sysent *) (((char *) _nsysent) + SYSENT_NSYSENT_OFFSET);
    
    if (check_sysent(_sysent))
        return _sysent;
    
    LOG("[phoenix] Scanning for SYSENT table ...\n");
    
    for (offset=-SYSENT_SCAN_RANGE; offset<SYSENT_SCAN_RANGE; offset++) {
        _sysent = (struct sysent *) (((char *) _nsysent) + offset);
        
        if (check_sysent(_sysent))
            return _sysent;
    }
    
    return NULL;
}

static void * find_symbol_from_disk(const char *name)
{
    #define MY_BSIZE 1024*1000 // ~1 MByte

    struct mach_header_64 *mmh;
    
    struct symtab_command *fsymtab = NULL;
    struct segment_command_64 *flinkedit = NULL;
    
    struct nlist_64 *nl = NULL;

    vnode_t kernel_node = NULL;
    vfs_context_t ctx = NULL;
    
    uio_t uio = NULL;
    
    void *addr = NULL, *fstrtab = NULL;
    
    char header_buffer[PAGE_SIZE_64];

    uint64_t i;
    
    if (vnode_lookup("/mach_kernel", 0, &kernel_node, NULL) != 0) {
        LOG( "[phoenix] vnode_lookup failed!\n" );
        return NULL;
    }
    
    ctx = vfs_context_current();
    
    if (vnode_open( "/mach_kernel", O_RDONLY, 0, 0, &kernel_node, ctx)) {
        LOG( "[phoenix] vnode_open failed!\n" );
        return NULL;
    }

    uio = uio_create(1, 0, UIO_SYSSPACE, UIO_READ);
    
    if (uio_addiov(uio, CAST_USER_ADDR_T(header_buffer), PAGE_SIZE_64)) {
        LOG( "[phoenix] uio_addiov failed!\n" );
        return NULL;
    }
    
    if (VNOP_READ(kernel_node, uio, 0, ctx)) {
        LOG( "[phoenix] VNOP_READ failed!\n" );
        return NULL;
    }
    
    mmh = (struct mach_header_64 *) ((void *) header_buffer);
    
    if (mmh->magic != MH_MAGIC_64) {
        LOG("Magic kernel number doesn't match - 0x%x\n", mmh->magic);
        return NULL;
    }
      
    flinkedit = find_segment_64(mmh, SEG_LINKEDIT);
    
    if (!flinkedit) {
        LOG("[phoenix] Couldn't find LINKEDIT segment!\n");
        return NULL;
    }
    
    fsymtab = (struct symtab_command *) find_load_command(mmh, LC_SYMTAB);
    
    if (!fsymtab) {
        LOG("[phoenix] Couldn't find SYMTAB load command!\n");
        return NULL;
    }
    
    uio_free(uio);
        
    /* Read the symbols from the kernel file ... */
    
    /**
     * Why can't I replace the MALLOC/FREE calls by using a
     *  statically allocated, nullify-ed buffer ... ???
     */

    void *sec_buffer = _MALLOC(MY_BSIZE, M_TEMP, (M_ZERO | M_WAITOK)); //char sec_buffer[MY_BSIZE] = { 0 };
    
    if (sec_buffer == NULL) {
        LOG( "[+] _MALLOC failed!\n" );
        return NULL;
    }
    
    uio = uio_create(1, flinkedit->fileoff, UIO_SYSSPACE, UIO_READ);
    
    if (uio_addiov(uio, CAST_USER_ADDR_T(sec_buffer), MY_BSIZE)) {
        LOG( "[+] FAIL: uio_addiov\n" );
        return NULL;
    }
    
    if (VNOP_READ(kernel_node, uio, 0, ctx)) {
        LOG( "[+] FAIL: VNOP_READ!\n");
        return NULL;
    }
    
    fstrtab = (void *) ((int64_t) sec_buffer + (fsymtab->stroff - flinkedit->fileoff));
    
    /*
     * Enumerate symbols until we find the one we're after
     */
    
    nl = (struct nlist_64 *) ((void *) sec_buffer + (fsymtab->symoff - flinkedit->fileoff));
    
    for (i=0; i<fsymtab->nsyms; i++) {
        
        if (strcmp((char *) fstrtab + nl->n_un.n_strx, name) == 0) {
            addr = (void *) nl->n_value;
            break;
        }
        
        nl = (struct nlist_64 *) ((uint64_t) nl + sizeof(struct nlist_64));
    }
    
    _FREE(sec_buffer, M_TEMP); // Do I really need a dynamically allocated buffer ... ?!
    
    uio_free(uio);
    
    vnode_close(kernel_node, FREAD, ctx);
    
    if (addr == NULL)
        return NULL;
    else {
        
        if (kaslr_offset == -1)
            return addr;
        else if (kaslr_offset == -2) {
            kaslr_offset = -1;
            kaslr_offset = ((void *) &vsscanf - find_symbol_from_disk("_vsscanf"));
            
            LOG("[phoenix] Kernel ASL randomization offset: 0x%lx\n", kaslr_offset);
        }
        
        return (addr + kaslr_offset);
    }
}

static int our_ptrace (struct proc *p, struct ptrace_args *uap, int *retval)
{
    if (uap->req == PT_DENY_ATTACH) {
        printf("[pt_deny_attach] Blocking PT_DENY_ATTACH for pid %d\n", uap->pid);
        return 0;
    }
    
    printf("[pt_deny_attach] Forwarding call to original ptrace for pid %d\n", uap->pid);
    original_ptrace(p, uap, retval);
    
    return 1;
}

kern_return_t phoenix_start(kmod_info_t * ki, void *d)
{
    LOG("Loading [phoenix] module ...\n");
    
    kernelbase_addr = kernelbase_address();
    
    if (kernelbase_addr == 0) {
        LOG("[phoenix] Can't find kernel base address!\n" );
        return KERN_FAILURE;
    }
    
    /**
     * The next function call implicitly computes the KASLR offset -
     * BUT as this is not really needed - it and can be left out ...
     *
     * LOG("[phoenix] _vsscanf file adress: %p\n", find_symbol_from_disk("_vsscanf") - kaslr_offset);
     */
    
    nsysent = find_symbol((struct mach_header_64 *) kernelbase_addr, "_nsysent");
    
    if (nsysent == NULL) {
        LOG("[phoenix] Could not localize NSYSENT symbol!\n");
        return KERN_FAILURE;
    }
    
    LOG("[phoenix] NSYSENT address: %p (Value: %d)\n", nsysent, *nsysent);
    
    sysent = locate_sysent(nsysent);
    
    if (sysent == NULL) {
        LOG("[phoenix] Could not localize SYSENT table!\n");
        return KERN_FAILURE;
    }
    
    LOG("[phoenix] SYSENT address: %p\n", sysent);
    LOG("[phoenix] SYSENT - NSYSENT offset: 0x%lx\n", (void *) sysent - (void *) nsysent);
       
    original_ptrace = (ptrace_func_t *) sysent[SYS_ptrace].sy_call;
    
    DISABLE_WRITE_PROTECTION();
    sysent[SYS_ptrace].sy_call = (sy_call_t *) our_ptrace;
    ENABLE_WRITE_PROTECTION();
    
    printf("[phoenix] Succesfully loaded ...\n");
    
    return KERN_SUCCESS;
}

#if 0

/*** --- * --------------------------------- **** --------------------------------- * --- ***/

#define _VSSCANF_OSX_12_4_0_    0xffffff8000608c30  // nm -g /mach_kernel | grep " _vsscanf$"
#define _NSYSENT_OSX_12_4_0_    0xffffff8000839818  //       ...          | grep " _nsysent$"

static vm_offset_t calc_kaslr_offset(void)
{
    vm_offset_t offset = (vm_offset_t) (&vsscanf - _VSSCANF_OSX_12_4_0_);
    
    LOG("[phoenix] sec Kernel address space layout randomisation offset: 0x%lx\n", offset);
    return offset;
}

static int* nsysent_address()
{
    int *nsysent = (int *) (_NSYSENT_OSX_12_4_0_ + calc_kaslr_offset());
    
    LOG("[phoenix] Memory address of nsysent: 0x%lx\n", (unsigned long) nsysent);
    return nsysent;
}

/*** --- * --------------------------------- **** --------------------------------- * --- ***/

#endif

kern_return_t phoenix_stop(kmod_info_t *ki, void *d)
{
    if (sysent != NULL) {
        DISABLE_WRITE_PROTECTION();
        sysent[SYS_ptrace].sy_call = (sy_call_t *) original_ptrace;
        ENABLE_WRITE_PROTECTION();
    }
       
    LOG("Unloaded [phoenix] module ...\n");
    return KERN_SUCCESS;
}

