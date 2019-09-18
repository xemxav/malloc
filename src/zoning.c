/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zoning.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 12:18:01 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 12:18:01 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_zone			*g_zone = NULL;

size_t		get_mult(int zone_size, size_t size)
{
	size_t			mult;

	if (zone_size == TINY)
		return (TINY_MULT);
	if (zone_size == SMALL)
		return (SMALL_MULT);
	if ((size + sizeof(t_alloc) + sizeof(t_zone)) % getpagesize() > 0)
		mult = ((size + sizeof(t_alloc) + sizeof(t_zone)) / getpagesize() + 1);
	else
		mult = ((size + sizeof(t_alloc) + sizeof(t_zone)) / getpagesize());
	if (mult == 0)
		mult = 1;
	printf("LARGE mult = %zu", mult);
	return (mult);
}

t_zone			*create_zone(int zone_size, size_t size)
{
	t_zone		*tmp;
	t_zone		*zone;

	if ((zone = (t_zone*)mmap(0, getpagesize() * get_mult(zone_size, size),
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0))
			== MAP_FAILED)
		return (NULL);
	if (g_zone == NULL)
		g_zone = zone;
	else
	{
		tmp = g_zone;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = zone;
	}
	zone->allocated = sizeof(t_zone);
	zone->type_size = zone_size;
	zone->next = NULL;
	zone->allocs = NULL;
	return (zone);
}

int 			has_enough_place(t_zone *zone, size_t req_size, int to_create)
{
	if (to_create == 1)
	{
		if ((zone->allocated + req_size + sizeof(t_alloc)) <=
			(unsigned long)(getpagesize() * get_mult(zone->type_size, req_size)))
				return (1);
	}
	else
	{
		if ((zone->allocated + req_size) <=
			(unsigned long)(getpagesize() * get_mult(zone->type_size, req_size)))
				return (1);
	}
	return (0);

}


t_zone			*get_current_zone(int zone_size,
									int req_size, t_zone *current_zone)
{
	t_zone		*tmp;

	tmp = g_zone;
	if (zone_size == LARGE || g_zone == NULL)
		return (create_zone(zone_size, req_size));
	while (tmp != NULL)
	{
		if (current_zone != NULL)
		{
			if (tmp->type_size == zone_size && tmp != current_zone &&
				has_enough_place(tmp, req_size, 1) == 1)
					return (tmp);
		}
		else
		{
			if (tmp->type_size == zone_size &&
				has_enough_place(tmp, req_size, 1) == 1)
					return (tmp);
		}
		tmp = tmp->next;
	}
	return (create_zone(zone_size, req_size));
}
