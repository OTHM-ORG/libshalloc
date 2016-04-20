#include <string.h>
#include "shalloc.h"

int main(void)
{
	char *str = shacatch();

	printf("%s", str);
	shafree(str);
}
