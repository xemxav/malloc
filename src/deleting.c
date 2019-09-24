/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   deleting.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/23 13:49:44 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/23 13:49:44 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/malloc.h"

void			delete_large_zone(t_info *info)
{
	t_large		*tmp;

	if (info->large == g_mapping->large && info->large->next == NULL)
		g_mapping->large = NULL;
	else
	{
		tmp = g_mapping->large;
		while (tmp->next != NULL && tmp->next != info->large)
		tmp = tmp->next;
		if (info->large->next == NULL)
			tmp->next = NULL;
		else
		tmp->next = info->large->next;
	}
	if (munmap(info->large->zone_adr, info->large->size) == -1)
		printf("fail de munmap de la large allouée");
	if (munmap(info->large, sizeof(t_large)) == -1)
		printf("fail de munmap de la structure large");
}

void			delete_tiny_zone(t_info	*info)
{
	t_tiny		*before;
	t_tiny		*tiny;

	before = NULL;
	tiny = info->tiny;
	info->tiny = NULL;
	if (tiny->nb_alloc != 0)
		return ;
	if (g_mapping->tiny == tiny && tiny->next == NULL)
		return ;
	before = g_mapping->tiny;
	while (before->next != NULL && before->next != tiny)
		before = before->next;
	before->next = tiny->next;
	if (munmap(tiny->zone_adr, TINY_TAB_SIZE) == -1)
		ft_putstr("fail de munmap de la tiny allouée\n");
	if (munmap(tiny, sizeof(t_tiny)) == -1)
		ft_putstr("fail de munmap de la structure tiny\n");
}

void			delete_small_zone(t_info *info)
{
	t_small		*before;
	t_small		*small;

	before = NULL;
	small = info->small;
	info->small = NULL;
	if (small->nb_alloc != 0)
		return ;
	if (g_mapping->small == small && small->next == NULL)
		return ;
	before = g_mapping->small;
	while (before->next != NULL && before->next != small)
		before = before->next;
	before->next = small->next;
	if (munmap(small->zone_adr, SMALL_TAB_SIZE) == -1)
		ft_putstr("fail de munmap de la small allouée\n");
	if (munmap(small, sizeof(t_small)) == -1)
		ft_putstr("fail de munmap de la structure small\n");
}

void			delete_ptr(t_info	*info)
{
	if (info->tiny != NULL)
	{
		info->tiny->nb_alloc--;
		g_mapping->nb_allocated -=
				(unsigned long long)info->tiny->tab[1][info->index];
		ft_bzero(info->ptr, info->tiny->tab[1][info->index]);
		info->tiny->tab[0][info->index] = 0;
		info->tiny->tab[1][info->index] = 0;
		delete_tiny_zone(info);
	}
	if (info->small != NULL)
	{
		info->small->nb_alloc--;
		g_mapping->nb_allocated -=
				(unsigned long long)info->small->tab[1][info->index];
		ft_bzero(info->ptr, info->small->tab[1][info->index]);
		info->small->tab[0][info->index] = 0;
		info->small->tab[1][info->index] = 0;
		delete_small_zone(info);
	}
	if (info->large != NULL)
	{
		g_mapping->nb_allocated -= info->large->size;
		delete_large_zone(info);
	}
	info->ptr = NULL;
}