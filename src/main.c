//
// Created by Xavier-emmanuel Moreau on 2019-09-11.
//

#include "../includes/malloc.h"

int		main()
{
	char	*ptr_test;
	char	*ptr_test2;
	int i = 0;
	ptr_test = ft_malloc(sizeof(char) * 8);
	if (ptr_test == NULL)
		printf("ptr_test est NULL");
	ft_memcpy((void*)ptr_test, "1234567\0", 8);
	printf("tiny ptr_test = %s\n", ptr_test);
	ptr_test2 = ft_malloc(sizeof(char) * 256);
	if (ptr_test == NULL)
		printf("ptr_test est NULL");
	while (i < 256)
	{	ptr_test2[i] = 'A';
		i++;
	}
	ptr_test2[i] = '\0';
	show_alloc_mem();
	show_alloc_mem_ex((void*)ptr_test, 100);
	ft_free(ptr_test);
	show_alloc_mem();
	ft_free(ptr_test2);
	printf("\n\n");
	show_alloc_mem();
	ft_putstr("ptr_test 1:");
	print_adress((void*)ptr_test);
	ft_putstr("\nptr_test 2:");
	print_adress((void*)ptr_test2);
	return (0);
}