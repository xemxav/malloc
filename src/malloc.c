//
// Created by Xavier-emmanuel Moreau on 2019-09-10.
//

#include "../includes/malloc.h"


void		*get_tiny(size_t size)
{
	void 	*new_tiny_ptr;
	t_alloc	*new_alloc;
	t_zone	*current_zone;


	if ((init_zoning(TINY) < 0))
		return (NULL);
	else
		current_zone = get_current_zone(TINY, size);
	new_alloc = make_new_alloc(size, current_zone);
	new_tiny_ptr = (void*)new_alloc + 1;
	return (new_tiny_ptr);
}

void		*ft_malloc(size_t size)
{
	void	*new_ptr;

	new_ptr = NULL;
	if (size <= 0)
		return new_ptr;
	if (size <=  TINY * 64)
		new_ptr = get_tiny(size);
//	else if (size <= SMALL)
//		new_ptr = get_small(size);
//	else
//		new_ptr = get_large(size);
	return (new_ptr);
}