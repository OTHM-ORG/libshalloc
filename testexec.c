#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#include "shalloc.h"

void send_exec(int num)
{
	void *mem;
	unsigned char code[] = { 0xb8, /* mov eax, */
				 0x00, 0x00, 0x00, 0x00, /* 0 */
				 0xc3 /* ret */ };

	memcpy(&code[1], &num, 4);

        mem = shalloc(sizeof(code));
	memcpy(mem, code, sizeof(code));

	shapass_pt(mem);

}

void get_exec(void)
{
	int (*func)(void) = shacatch_pt();

	shasetexec(func);
	printf("Your number was %i\n", func());
	shafree(func);
}



int main(int argc, char *argv[])
{
	int num;

	if (argc < 2)
		get_exec();
	else
		send_exec(atoi(argv[1]));

	return 0;
}
