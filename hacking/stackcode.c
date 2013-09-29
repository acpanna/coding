#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char shellcode[] = "\xeb\xfe";

int main(int argc, char *argv[]){

	void (*f)();
	char x[4];

	memcpy(x, shellcode, sizeof(shellcode));
	f = (void (*)()) x;
	f();

	return 0;
}
