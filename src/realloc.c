/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 14:03:31 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 14:03:31 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void				*create_new_ptr(t_info *info, size_t size)
{
	void				*new_ptr;

	if ((new_ptr = malloc(size)) == NULL)
		return (NULL);
	if (info->tiny != NULL && (int)size > info->tiny->tab[1][info->index])
		size = (size_t)(info->tiny->tab[1][info->index]);
	if (info->small != NULL && (int)size > info->small->tab[1][info->index])
		size = (size_t)(info->small->tab[1][info->index]);
	if (info->large != NULL && size > info->large->size)
		size = info->large->size;
	ft_memcpy(new_ptr, info->ptr, size);
	delete_ptr(info);
	return (new_ptr);
}

static void				*reallocate_tiny_small(t_info *info, size_t size)
{
	if (info->tiny != NULL)
	{
		if ((int)size < info->tiny->tab[1][info->index])
			ft_bzero(info->ptr + size, TINY - info->tiny->tab[1][info->index]);
		g_mapping.nb_allocated += size - info->tiny->tab[1][info->index];
		info->tiny->tab[1][info->index] = (int)size;
	}
	if (info->small != NULL)
	{
		if ((int)size < info->small->tab[1][info->index])
			ft_bzero(info->ptr + size, SMALL - info->small->tab[1][info->index]);
		g_mapping.nb_allocated += size - info->small->tab[1][info->index];
		info->small->tab[1][info->index] = (int)size;
	}
	return (info->ptr);
}

void    				*realloc(void *ptr, size_t size)
{
	t_info				info;

	if (g_mapping.tiny != NULL && g_mapping.small != NULL &&
	g_mapping.large != NULL)
		return (malloc(size));
	if (ptr == NULL)
		return malloc(size);
	ft_bzero((void*)&info, sizeof(t_info));
	info.ptr = ptr;
	if (find_in_tiny(&info) == 1)
	{
		if((int)size <= TINY)
			return (reallocate_tiny_small(&info, size));
		return (create_new_ptr(&info, size));
	}
	if (find_in_small(&info) == 1)
	{
		if((int)size <= SMALL && (int)size > TINY)
			return (reallocate_tiny_small(&info, size));
		return (create_new_ptr(&info, size));
	}
	if (find_in_large(&info) == 1)
		return (create_new_ptr(&info, size));
	return (NULL);
}