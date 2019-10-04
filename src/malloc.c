/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 13:45:41 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 13:45:41 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/malloc.h"

void			*calloc(size_t nmemb, size_t size)
{
	void		*ptr;
	size_t		i;

	i = 0;
	if (size == 0)
		return (NULL);
	if ((ptr = malloc(nmemb * size)) == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void			*malloc(size_t size)
{
	t_large		*new_large;

	new_large = NULL;
	if (size <= TINY)
		return (get_tiny_zone(size));
	if (size <= SMALL && size > TINY)
		return (get_small_zone(size));
	if (size >= LARGE)
	{
		if (g_mapping == NULL)
			init_mapping();
		new_large = init_large(size);
		new_large->size = size;
		g_mapping->nb_allocated += (unsigned long long)size;
		return (new_large->zone_adr);
	}
	return (NULL);
}
