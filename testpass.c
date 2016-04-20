#include <string.h>
#include "shalloc.h"

#define HELLO "hello, world!\n"

int main(int argv, char *args[])
{
	char *str;

	if (argv > 1) {
		str = shalloc(strlen(args[1]) + 1);
		sprintf(str, "%s\n", args[1]);
	} else {
		str = shalloc(sizeof(HELLO));
		sprintf(str, HELLO);
	}

        shapass(str);
}
