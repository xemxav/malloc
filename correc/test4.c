#include "../includes/malloc.h"
//#include <stdlib.h>
# include <unistd.h>


void print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
	char *addr;

	addr = malloc(16);
//	show_alloc_mem();
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 10) == NULL)
		print("Bonjours\n");
//	show_alloc_mem();
}