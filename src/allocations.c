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



t_alloc			*find_proper_alloc(t_alloc *last, size_t size)
{
	t_alloc		*new;

	new = NULL;
	while (last->next != NULL)
	{
		if (get_new_alloc_from_last(last) != (void*)last->next)
		{ //todo : a tester avec realloc
			if ((void*)last->next - size - sizeof(t_alloc) >
					get_new_alloc_from_last(last))
			new = get_new_alloc_from_last(last);
			new->next = last->next;
			last->next = new;
			return (new);
		}
		last = last->next;
	}
	last->next = get_new_alloc_from_last(last);
	new = last->next;
	//todo : verifier si on ne sort pas de la zone en cas de realloc
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
		adr_new_alloc = (void*)(current_zone) + sizeof(t_zone);
		current_zone->allocs = adr_new_alloc;
		adr_new_alloc->next = NULL;
	}
	else
		adr_new_alloc = find_proper_alloc(current_zone->allocs, size);
	//todo : verifier si on ne sort pas de la zone en cas de realloc
	adr_new_alloc->size = size;
	current_zone->allocated += sizeof(t_alloc) + size;
	return (adr_new_alloc);
}
