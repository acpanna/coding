#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

char shellcode[] = "\xeb\xfe"; // Infinite Loop
//char shellcode[] = "\x90"; // NOP

int main(int argc, char *argv[]) {
	void (*f)();
	void *page;
/*
	page = (void *)((uintptr_t)shellcode & ~(getpagesize() - 1));
	mprotect(page, sizeof shellcode, PROT_EXEC);

	f = (void (*)()) shellcode;
	f();
*/
	char *x = malloc(2);
	memcpy(x, shellcode, sizeof(shellcode));
	
	page = (void *)((uintptr_t)x & ~(getpagesize() - 1));
	mprotect(page, sizeof x, PROT_EXEC);

	f = (void (*)()) x;
	f();
	
	return 0;
}
