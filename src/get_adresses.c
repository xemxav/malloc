/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_adresses.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 10:34:17 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/18 10:34:17 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/malloc.h"

void			*get_ptr_from_alloc(t_alloc	*alloc)
{
	return ((void*)(alloc) + sizeof(t_alloc));
}

t_alloc			*get_new_alloc_from_last(t_alloc *last)
{
	return ((void *)(last) + sizeof(t_alloc) + (last->size));
}

void			*get_max_zone_adresse(t_zone *zone,size_t size)
{
	return ((void*)zone + (getpagesize() * get_mult(zone->type_size, size) - 1));
}
