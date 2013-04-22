/*
 * knark, adore, rtkit as reference

 * < -- > carbonite, kstat, rkscan
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/unistd.h>

#define DEBUG

/*
#include <linux/syscalls.h>
#include <linux/unistd.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/namei.h>




#include <linux/signal.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/types.h>
#include <linux/ptrace.h>
#include <linux/mman.h>
#include <linux/mm.h>
#include <linux/swap.h>
#include <linux/smp.h>
#include <linux/init.h>
#include <linux/initrd.h>
#include <linux/pagemap.h>
#include <linux/bootmem.h>
#include <linux/proc_fs.h>
#include <linux/pci.h>
#include <linux/pfn.h>
#include <linux/poison.h>
#include <linux/dma-mapping.h>
#include <linux/module.h>
#include <linux/memory_hotplug.h>
#include <linux/nmi.h>

#include <asm/processor.h>
#include <asm/bios_ebda.h>
#include <asm/system.h>
#include <asm/uaccess.h>
#include <asm/pgtable.h>
#include <asm/pgalloc.h>
#include <asm/dma.h>
#include <asm/fixmap.h>
#include <asm/e820.h>
#include <asm/apic.h>
#include <asm/tlb.h>
#include <asm/mmu_context.h>
#include <asm/proto.h>
#include <asm/smp.h>
#include <asm/sections.h>
#include <asm/kdebug.h>
#include <asm/numa.h>
#include <asm/cacheflush.h>
#include <asm/init.h>



*/

MODULE_LICENSE ("GPL");
/*
int flag = 0;

#define MAX_TRY 1024;

unsigned long *sys_call_table;

asmlinkage int (*orig_sys_open)(const char *filename, int flags, int mode);

asmlinkage int fake_sys_open(const char *filename, int flags, int mode)
{
	int error;
	//	struct nameidata nd, nd_t;
	struct path path, path_t;

	struct inode *inode, *inode_t;
	mm_segment_t fs;

	error = user_path(filename, &path);
	//error = user_path_walk(filename, &nd);

	if (!error) {

		inode = path.dentry->d_inode;

		//Have to do this before calling user_path_walk( )
		 // from kernel space:

		fs = get_fs( );
		set_fs(get_ds( ));

		//Protect /tmp/test. Change this to whatever file you
		 // want to protect

		error = user_path("/tmp/test", &path_t);
		//error = user_path_walk("/tmp/test", &nd_t);

		set_fs(fs);

		if(!error) {
			inode_t = path_t.dentry->d_inode;
			if(inode == inode_t)
				return -EACCES;
		}
	}

	return orig_sys_open(filename, flags, mode);
}

int set_page_rw(long unsigned int _addr)
{
    return set_memory_rw(_addr, 1);
}

int set_page_ro(long unsigned int _addr)
{
    return set_memory_ro(_addr, 1);
}

unsigned long **find_sys_call_table(void) 
{
	extern unsigned long loops_per_jiffy;

	unsigned long **sctable;
	unsigned long ptr;

	sctable = NULL;
	//for (ptr = (unsigned long) &unlock_kernel; ptr < (unsigned long) &loops_per_jiffy; ptr += sizeof(void *)) {
	for (ptr = (unsigned long)&loops_per_jiffy;
			ptr < (unsigned long)&boot_cpu_data; ptr += sizeof(void *)){

		unsigned long *p;
		p = (unsigned long *)ptr;

		if (p[__NR_close] == (unsigned long) sys_close){
			sctable = (unsigned long **)p;
			return &sctable[0];
		}
	}

	return NULL;
}
*/


static int get_sct(void) 
{
	unsigned long *ptr;

	void **syscall_table = NULL;

	ptr = (unsigned long *) ((init_mm.end_code + 4) & 0xfffffffc);
	while ((unsigned long) ptr < (unsigned long) init_mm.end_data) {

		if ((unsigned long *) *ptr == (unsigned long *) sys_close) {
#ifdef DEBUG
			printk(KERN_INFO "Matching detected at %p\n", ptr);
#endif
			if ((unsigned long *) *((ptr - __NR_close) + __NR_read) == (unsigned long *) sys_read 
				&&  (unsigned long *) *((ptr - __NR_close) + __NR_open) == (unsigned long *) sys_open) {

				syscall_table = (void **) ((unsigned long *)(ptr - __NR_close));
				break;
			}
		}

		ptr++;
	}

#ifdef DEBUG
	printk(KERN_INFO "syscall_table base found at: %p\n", syscall_table);
#endif

	if (syscall_table == NULL) 
		return -1;
	else
		return 1;
}

static int my_init (void)
{
	if (get_sct())
		printk(KERN_INFO "oki");
	else
		printk(KERN_INFO "noki");

	
/*	unsigned long **sys_call_table = find_sys_call_table();
	
	if (sys_call_table != NULL) {
		
		set_page_rw(sys_call_table);
		orig_sys_open = (void *) xchg(&sys_call_table[__NR_open], fake_sys_open);
		set_page_ro( sys_call_table);

		flag = 1;
		printk("SYSCalls found!");

	} else { 
		printk("SYSCalls not found!");
		flag = 0;
	}
*/
	return 0;
}
static void my_exit (void)
{
	/*
	if (flag) {
		set_page_rw(sys_call_table);
		xchg(&sys_call_table[__NR_open], orig_sys_open);
		set_page_ro(sys_call_table);
	}
	*/
}

module_init(my_init);
module_exit(my_exit);
