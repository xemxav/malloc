//
// Created by Xavier-emmanuel Moreau on 2019-09-11.
//

#include "../includes/malloc.h"

#define TEST 15

int         main()
{
	int		i;
	char 	*ptr;

	i = 0;
	ptr = NULL;
//	while (i < 300)
//	{
//		malloc(15);
//		total += 15;
//		malloc(400);
//		total += 400;
//		malloc(513);
//		total += 513;
//		i++;
//	}
	ptr = malloc(TEST);
	ptr = realloc(ptr, TEST+56);
	free(ptr);

	show_alloc_mem();

}

//int		main()
//{
//	char	*ptr_test;
//	char	*ptr_test2;
//	int i = 0;
//	ptr_test = malloc(sizeof(char) * 8);
//	if (ptr_test == NULL)
//		printf("ptr_test est NULL");
//	ft_memcpy((void*)ptr_test, "1234567\0", 8);
//	printf("tiny ptr_test = %s\n", ptr_test);
//	ptr_test2 = malloc(sizeof(char) * 256);
//	if (ptr_test == NULL)
//		printf("ptr_test est NULL");
//	while (i < 256)
//	{	ptr_test2[i] = 'A';
//		i++;
//	}
//	ptr_test2[i] = '\0';
//	realloc(ptr_test2, sizeof(char) * 514);
//	show_alloc_mem();
//	show_alloc_mem_ex((void*)ptr_test, 100);
//	free(ptr_test);
//	show_alloc_mem();
//	free(ptr_test2);
//	printf("\n\n");
//	show_alloc_mem();
//	ft_putstr("ptr_test 1:");
//	print_adress((void*)ptr_test);
//	ft_putstr("\nptr_test 2:");
//	print_adress((void*)ptr_test2);
//	return (0);
//}