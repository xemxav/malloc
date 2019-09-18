//
// Created by Xavier-emmanuel Moreau on 2019-09-11.
//

#include "../includes/malloc.h"

int		main()
{
	char	*ptr_test;
	char	*ptr_test2;
	t_alloc *tmp;


	tmp = NULL;
	ptr_test = ft_malloc(sizeof(char) * 8);
	if (ptr_test == NULL)
		ft_putstr("c'est fini 1\n");
	ft_memcpy((void*)ptr_test, "1234567\0", sizeof(char) * 8);
	show_alloc_mem_ex((void*)g_zone, 100);
	ptr_test2 = ft_malloc(sizeof(char) * 5);
	ft_memcpy((void*)ptr_test2, "AAAA\0", sizeof(char) * 5);
	if (ptr_test2 == NULL)
		ft_putstr("c'est fini 2\n");
	show_alloc_mem_ex((void*)g_zone, 100);
	ft_free(ptr_test);
	printf("apres free\n");
	show_alloc_mem_ex((void*)g_zone, 100);
	ptr_test = ft_malloc(sizeof(char) * 5);
	ft_memcpy((void*)ptr_test, "1234\0", sizeof(char) * 5);
	printf("apres nouveau malloc\n");
	show_alloc_mem_ex((void*)g_zone, 100);
	printf("\n\n");

	show_alloc_mem();

	printf("\n\n");

	ft_putstr("ptr_test 1:");
	print_adress((void*)ptr_test);
	ft_putstr("\nptr_test 2:");
	print_adress((void*)ptr_test2);
	return (0);
}