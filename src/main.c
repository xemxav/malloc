//
// Created by Xavier-emmanuel Moreau on 2019-09-11.
//

#include "../includes/malloc.h"

int		main()
{
	int	*ptr_test;

	ptr_test = ft_malloc(sizeof(int) * 4);
	if (ptr_test == NULL)
	{
		ft_putstr("c'est fini\n");
	}
	return (0);
}