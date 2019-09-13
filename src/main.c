//
// Created by Xavier-emmanuel Moreau on 2019-09-11.
//

#include "../includes/malloc.h"

int		main()
{
	char	*ptr_test;
	char	*ptr_test2;


	ptr_test = ft_malloc(sizeof(char) * 8);
	if (ptr_test == NULL)
		ft_putstr("c'est fini 1\n");
	ptr_test2 = ft_malloc(sizeof(int) * 5);
	if (ptr_test2 == NULL)
		ft_putstr("c'est fini 2\n");
	show_alloc_mem();
	ft_putstr("ptr_test :");
	print_adress((void*)ptr_test);
	ft_putstr("\nptr_test :");
	print_adress((void*)ptr_test2);
	return (0);
}