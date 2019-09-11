//
// Created by Xavier-emmanuel Moreau on 2019-09-10.
//

#include "../includes/malloc.h"

t_zone		*g_zone = NULL;


int	init_zoning(size_t size)
{
	ft_putstr("taille de la size : ");
	ft_putnbr(size);
	if (g_zone == NULL)
	{
		if ((g_zone = (t_zone*)mmap(0, getpagesize() * 1, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0)) == MAP_FAILED)
			return (-1)
		g_zone->allocated = 0;
		g_zone->type_size = TINY;
		g_zone->next = NULL;
		g_zone->allocs = NULL;
	}
	return (0)
}
