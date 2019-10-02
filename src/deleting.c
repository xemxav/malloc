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

	//ft_putstr("rentre delete_large_zone\n");
	if (info->large == g_mapping->large && info->large->next == NULL)
		g_mapping->large = NULL;
	else
	{
		if (info->large == g_mapping->large && info->large->next != NULL)
			g_mapping->large = info->large->next;
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
	}
	munmap(info->large->zone_adr, info->large->size);
	munmap(info->large, getpagesize());
	//ft_putstr("quitte delete_large_zone\n");
}

void			delete_tiny_zone(t_info	*info)
{
	t_tiny		*before;
	t_tiny		*tiny;

	//ft_putstr("rentre delete_tiny_zone\n");
	before = NULL;
	tiny = info->tiny;
	if (tiny->nb_alloc != 0)
		return ;
	if (g_mapping->tiny == tiny && tiny->next == NULL)
		return ;
	if (g_mapping->tiny == tiny && tiny->next != NULL)
		g_mapping->tiny = tiny->next;
	else
	{
		before = g_mapping->tiny;
		while (before->next != NULL && before->next != tiny)
			before = before->next;
		before->next = tiny->next;
	}
	munmap(tiny->zone_adr, TINY_PAGE_SIZE);
	munmap(tiny, getpagesize());
	//ft_putstr("quitte delete_tiny_zone\n");
}

void			delete_small_zone(t_info *info)
{
	t_small		*before;
	t_small		*small;
	//ft_putstr("rentre delete_small_zone\n");

	before = NULL;
	small = info->small;
	if (small->nb_alloc != 0)
		return ;
	if (g_mapping->small == small && small->next == NULL)
		return ;
	if (small == g_mapping->small && small->next != NULL)
		g_mapping->small = small->next;
	else
	{
		before = g_mapping->small;
		while (before->next != NULL && before->next != small)
			before = before->next;
		before->next = small->next;
	}
	munmap(small->zone_adr, SMALL_PAGE_SIZE);
	munmap(small, getpagesize());
	//ft_putstr("quitte delete_small_zone\n");
}

void			delete_ptr(t_info	*info)
{
	//ft_putstr("rentre dans delete_ptr\n");
	if (info->tiny != NULL)
	{
		//ft_putstr("rentre dans delete_ptr tiny\n");
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
		//ft_putstr("rentre dans delete_ptr small\n");
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
	//ft_putstr("delete_ptr fini\n");
}