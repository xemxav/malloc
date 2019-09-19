
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>

# include <stdio.h>
#include <stdlib.h>

# define SMALL ((512 * 100) / getpagesize())



int main()
{
	printf("%d\n", SMALL);
	return (0);
}