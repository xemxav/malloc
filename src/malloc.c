//
// Created by Xavier-emmanuel Moreau on 2019-09-10.
//

#include "../includes/malloc.h"


static void		*get_ptr(size_t size, int zone_size)
{
	void 		*new_ptr;
	t_alloc		*new_alloc;
	t_zone		*current_zone;

	current_zone = get_current_zone(zone_size, size);
	if (current_zone == NULL)
		return (NULL);
	new_alloc = make_new_alloc(size, current_zone);
	new_ptr = (void*)new_alloc + 1;
	return (new_ptr);
}

void			*ft_malloc(size_t size)
{
	void		*new_ptr;

	new_ptr = NULL;
	if (size <= 0)
		return new_ptr;
	if (size <=  TINY * 64)
		new_ptr = get_ptr(size, TINY);
	else if (size <= SMALL)
		new_ptr = get_ptr(size, SMALL);
	else
		new_ptr = get_ptr(size, LARGE);
	return (new_ptr);
}