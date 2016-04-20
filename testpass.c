#include <string.h>
#include "shalloc.h"

#define HELLO "hello, world!\n"

int main(int argc, char *argv[])
{
	char *str;

	if (argc > 1) {
		str = shalloc(strlen(argv[1]) + 1);
		sprintf(str, "%s\n", argv[1]);
	} else {
		str = shalloc(sizeof(HELLO));
		sprintf(str, HELLO);
	}

        shapass(str);
	return 0;
}
