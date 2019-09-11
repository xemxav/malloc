//
// Created by Xavier-emmanuel Moreau on 2019-09-10.
//

#include "../includes/malloc.h"


void	*get_tiny(size_t size)
{
	void *new_tiny_ptr;
	t_alloc	*new_alloc;

	if ((init_zoning(size) < 0)
		return(NULL);

	return (NULL);
}

void	*ft_malloc(size_t size)
{
	void		*new_ptr;

	new_ptr = NULL;
	if (size <= 0)
		return new_ptr;
	if (size <=  TINY)
		new_ptr = get_tiny(size);
//	else if (size <= SMALL)
//		new_ptr = get_small(size);
//	else
//		new_ptr = get_large(size);
	return (new_ptr);
}