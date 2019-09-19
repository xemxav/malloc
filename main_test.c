
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>

# include <stdio.h>
#include <stdlib.h>

typedef struct s_test
{
	char			a[256];
//	struct s_test		*next;
} t_test;


int main()
{
	printf("sizeof t_test = %lu", sizeof(t_test));
	return (0);
}