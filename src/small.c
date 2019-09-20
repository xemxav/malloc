/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   small.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/20 11:31:59 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/20 11:31:59 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/malloc.h"

int				find_in_small(void *ptr)
{
	t_small			*tmp;
	int				i;

	i = 0;
	if (g_mapping->small == NULL)
		return (0);
	tmp = g_mapping->small;
	while (tmp != NULL)
	{
		if (ptr <= tmp->zone_adr + (SMALL_PAGE_SIZE) &&
			ptr >= tmp->zone_adr)
		{
			i =(int)(((unsigned long)ptr - (unsigned long)tmp->zone_adr)
					/ (unsigned long)SMALL);
			tmp->nb_alloc--;
			ft_bzero(ptr, tmp->tab[1][i]);
			tmp->tab[0][i] = 0;
			tmp->tab[1][i] = 0;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void			*get_small_ptr(t_small *small, size_t size)
{
	int			i;
	void		*new_ptr;

	i = 0;
	new_ptr = NULL;
	while(i < SMALL_TAB_SIZE)
	{
		if (small->tab[0][i] == 0)
		{
			small->tab[1][i] = (int)size;
			small->tab[0][i] = 1;
			small->nb_alloc += 1;
			return ((void *) small->zone_adr + (i * SMALL));
		}
		i++;
	}
	return (NULL);
}

void			*get_small_zone(size_t size)
{
	t_small		*new_small;

	if (g_mapping == NULL)
		init_mapping();
	if (g_mapping->small == NULL)
		return (get_small_ptr(init_small(), size));
	else
	{
		new_small = g_mapping->small;
		while (new_small != NULL)
		{
			if (new_small->nb_alloc < SMALL_TAB_SIZE)
				return (get_small_ptr(new_small, size));
			new_small = new_small->next;
		}
		return (get_small_ptr(init_small(), size));
	}
}
