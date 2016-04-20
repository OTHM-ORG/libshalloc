#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#include "shalloc.h"

int main(int argc, char *argv[])
{
	int num;
	void *mem;
	int (*func)(void);
	unsigned char code[] = { 0xb8, /* mov eax, */
				 0x00, 0x00, 0x00, 0x00, /* 0 */
				 0xc3 /* ret */ };

	if (argc < 2) {
		fprintf(stderr, "Usage: testexec <int>\n");
		return 1;
	}

	num = atoi(argv[1]);
	memcpy(&code[1], &num, 4);

        mem = shalloc(sizeof(code));
	memcpy(mem, code, sizeof(code));
	shasetexec(mem);

	func = mem;
	printf("Your number was %i\n", func());

	shafree(mem);

	return 0;
}
