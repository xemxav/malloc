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

void	delete_alloc(t_info *info)
{
	t_alloc		*tmp;

	tmp = info->zone->allocs;
	if (tmp == info->zone->allocs)
	{
		if (tmp->next != NULL)
			info->zone->allocs->next = tmp->next;
		else
			info->zone->allocs->next = NULL;
		ft_bzero(info->old_ptr, info->alloc->size);
		ft_bzero(tmp, sizeof(t_alloc));
		return;
	}
	while (tmp->next != info->zone->allocs)
		tmp = tmp->next;
	if (info->zone->allocs->next == NULL)
	{
		tmp->next = NULL;
		ft_bzero(info->old_ptr, info->alloc->size);
		ft_bzero(tmp, sizeof(t_alloc));
		return;
	}
	tmp->next = info->zone->allocs->next;
	ft_bzero(info->old_ptr, info->alloc->size);
	ft_bzero(tmp, sizeof(t_alloc));
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
	{		printf("a pas retrieve\n");
		return ;}
	printf("coucou\n");
	delete_alloc(&info);
}