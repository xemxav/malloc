/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tiny.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/19 16:30:30 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/19 16:30:30 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/malloc.h"

int				find_in_tiny(t_info *info)
{
	t_tiny			*tmp;

	if (g_mapping->tiny == NULL)
		return (0);
	tmp = g_mapping->tiny;
	while (tmp != NULL)
	{
		if (info->ptr <= (void*)tmp->zone_adr + (TINY_PAGE_SIZE - 1) &&
			info->ptr >= (void*)tmp->zone_adr)
		{
			info->index = (int)(((unsigned long)info->ptr -
					(unsigned long)tmp->zone_adr) / (unsigned long)TINY);
			info->tiny = tmp;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void			*get_tiny_ptr(t_tiny *tiny, size_t size)
{
	int			i;
	void		*new_ptr;

	i = 0;
	new_ptr = NULL;
	if (tiny == NULL)
		return (NULL);
	while (i < TINY_TAB_SIZE)
	{
		if (tiny->tab[0][i] == 0)
		{
			tiny->tab[1][i] = (int)size;
			tiny->tab[0][i] = 1;
			tiny->nb_alloc += 1;
			g_mapping->nb_allocated += (unsigned long long)size;
			return ((void *)tiny->zone_adr + (i * TINY));
		}
		i++;
	}
	return (NULL);
}

void			*get_tiny_zone(size_t size)
{
	t_tiny		*new_tiny;

	if (g_mapping == NULL)
		init_mapping();
	if (g_mapping->tiny == NULL)
		return (get_tiny_ptr(init_tiny(), size));
	else
	{
		new_tiny = g_mapping->tiny;
		while (new_tiny != NULL)
		{
			if (new_tiny->nb_alloc < TINY_TAB_SIZE)
				return (get_tiny_ptr(new_tiny, size));
			new_tiny = new_tiny->next;
		}
		return (get_tiny_ptr(init_tiny(), size));
	}
}
