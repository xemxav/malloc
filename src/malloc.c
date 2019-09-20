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

static void		*get_ptr(size_t size)
{
	t_large		*new_large;

	new_large = NULL;
	if (size <= TINY)
		return (get_tiny_zone(size));
	if (size <= SMALL)
		return (get_small_zone(size));
	if (size >= LARGE)
	{
		new_large = init_large(size);
		new_large->size = size;
		return (new_large->zone_adr);
	}
	return (NULL);
}

void			*ft_malloc(size_t size)
{
	void		*new_ptr;

	new_ptr = NULL;
	if (size <= 0)
		return (new_ptr);
	new_ptr = get_ptr(size);
	return (new_ptr);
}
