/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   allocations.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 16:19:08 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 16:19:08 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/malloc.h"

void			retrieve_alloc_from_ptr(t_info *info)
{
	t_zone			*zone;
	t_alloc			*alloc;

	zone = g_zone;
	while (zone != NULL)
	{
		alloc = zone->allocs;
		while (alloc != NULL)
		{
			if (get_ptr_from_alloc(alloc) == info->old_ptr)
			{
				info->zone = zone;
				info->alloc = alloc;
				return ;
			}
			alloc = alloc->next;
		}
		zone = zone->next;
	}
}

static t_alloc			*find_proper_alloc(t_zone *current_zone, size_t size)
{
	t_alloc		*new;
	t_alloc		*last;

	new = NULL;
	last = current_zone->allocs;
	while (last->next != NULL)
	{
		if (get_new_alloc_from_last(last) != (void*)last->next)
		{
			if ((void*)last->next - size - sizeof(t_alloc) >
					(void*)get_new_alloc_from_last(last))
			new = get_new_alloc_from_last(last);
			new->next = last->next;
			last->next = new;
			return (new);
		}
		last = last->next;
	}
	if (get_max_zone_adresse(current_zone, size) <= (void*)get_new_alloc_from_last(last))
		return (NULL);
	last->next = get_new_alloc_from_last(last);
	new = last->next;
	return (new);
}

t_alloc			*make_new_alloc(size_t size, t_zone *current_zone)
{
	t_alloc		*last;
	t_alloc		*adr_new_alloc;

	adr_new_alloc = NULL;
	last = NULL;
	if (current_zone->allocs == NULL)
	{
		if (get_max_zone_adresse(current_zone, size) <=
			(void*)(current_zone) + sizeof(t_zone) + sizeof(t_alloc) + size)
			return (NULL);
		adr_new_alloc = (void*)(current_zone) + sizeof(t_zone);
		current_zone->allocs = adr_new_alloc;
		adr_new_alloc->next = NULL;
	}
	else
		adr_new_alloc = find_proper_alloc(current_zone, size);
	if (adr_new_alloc == NULL)
		return (NULL);
	adr_new_alloc->size = size;
	current_zone->allocated += sizeof(t_alloc) + size;
	return (adr_new_alloc);
}
