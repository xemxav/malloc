/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/18 17:01:29 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/18 17:01:29 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#include "../includes/malloc.h"

static void make_clean(t_alloc *tmp, t_info *info)
{
	info->zone->allocated -= info->alloc->size;
	ft_bzero(info->old_ptr, info->alloc->size);
	ft_bzero(tmp, sizeof(t_alloc));
}

void	delete_alloc(t_info *info)
{
	t_alloc		*tmp;

	tmp = info->zone->allocs;
	if (tmp == info->zone->allocs)
	{
		if (tmp->next != NULL)
			info->zone->allocs = tmp->next;
		else
			info->zone->allocs = NULL;
		return make_clean(tmp, info);
	}
	while (tmp->next != info->zone->allocs)
		tmp = tmp->next;
	if (info->zone->allocs->next == NULL)
	{
		tmp->next = NULL;
		return make_clean(tmp, info);
	}
	tmp->next = info->zone->allocs->next;
	return make_clean(tmp, info);
}

void	ft_free(void *ptr)
{
	t_info	info;

	if (ptr == NULL || g_zone == NULL)
		return ;
	ft_bzero((void*)&info, sizeof(t_info));
	info.old_ptr = ptr;
	retrieve_alloc_from_ptr(&info);
	if (info.alloc == NULL || info.zone == NULL)
		return ;
	delete_alloc(&info);
}