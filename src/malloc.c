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

static void		*get_ptr(size_t size, int zone_size)
{
	t_alloc		*new_alloc;
	t_zone		*current_zone;
	void		*new_ptr;

	current_zone = get_current_zone(zone_size, size);
	if (current_zone == NULL)
		return (NULL);
	new_alloc = make_new_alloc(size, current_zone);
	printf("current_zone = %p\nsizeof current_zone = %lu\n", current_zone, sizeof(t_zone));
	printf("new_alloc = %p\nsizeof new_alloc = %lu\n", new_alloc, sizeof(t_alloc));
	new_ptr = (void*)(new_alloc) + sizeof(t_alloc) + 1;
	printf("new_ptr = %p\n", new_ptr);
	return (new_ptr);
}

int				get_zone_type(size_t size)
{
	if (size <= TINY)
		return TINY;
	else if (size <= SMALL)
		return TINY;
	return (LARGE);
}

void			*ft_malloc(size_t size)
{
	void		*new_ptr;
	int			zone_type;

	new_ptr = NULL;
	if (size <= 0)
		return (new_ptr);
	zone_type = get_zone_type(size);
	new_ptr = get_ptr(size, zone_type);
	return (new_ptr);
}
