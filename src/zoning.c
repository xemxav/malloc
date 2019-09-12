//
// Created by Xavier-emmanuel Moreau on 2019-09-10.
//

#include "../includes/malloc.h"

t_zone		*g_zone = NULL;

t_zone		*get_current_zone(int type_size, int req_size)
{
	t_zone	*tmp;
	tmp = g_zone;

	while(tmp->next != NULL)
	{
		if (tmp->type_size == type_size)
		{
			if ((tmp->allocated + req_size + sizeof(t_alloc)) > (unsigned long)(getpagesize() * type_size))
				return tmp;
		}
	}
	return g_zone;
}


t_alloc			*make_new_alloc(size_t size, t_zone *current_zone)
{
	t_alloc		*new;
	t_alloc		*last;


	new = NULL;
	last = NULL;
	if (current_zone->allocs == NULL)
	{
		new = (t_alloc*)(current_zone + 1);
		new->size = size;
		new->next = NULL;
		current_zone->allocated = sizeof(new) + size;
		current_zone->allocs = new;
	}
	else
	{
		last = (t_alloc*)(current_zone->allocs);
		while(last->next != NULL)
			last = (t_alloc*)(last->next);
		new = last;
		new = new + last->size;
		last->next = new;
		new->next = NULL;
		new->size = size;
		current_zone->allocated = sizeof(new) + size;
	}
	return (new);
}

int	init_zoning(int page_nb)
{
	if (g_zone == NULL)
	{
		// mettre un truc pour determiner le multiple de getpagesize()
		if ((g_zone = (t_zone*)mmap(0, getpagesize() * page_nb, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0)) == MAP_FAILED)
			return (-1);
		g_zone->allocated = sizeof(g_zone);
		g_zone->type_size = page_nb;
		g_zone->next = NULL;
		g_zone->allocs = NULL;
	}
	return (0);
}
