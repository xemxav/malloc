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

int				find_in_small(t_info *info)
{
	t_small		*tmp;
	int			i;

	i = 0;
	//ft_putstr("rentre find_in_small\n");
	if (g_mapping->small == NULL)
		return (0);
	tmp = g_mapping->small;
	while (tmp != NULL)
	{
		if (info->ptr <= (void*)tmp->zone_adr + (SMALL_PAGE_SIZE - 1) &&
			info->ptr >= (void*)tmp->zone_adr)
		{
			while (i < SMALL_PAGE_SIZE)
			{
				if ((void *)tmp->zone_adr + (i * SMALL) == info->ptr && tmp->tab[0][i] == 1)
				{
					info->index = i;
					info->small = tmp;
					//ft_putstr("find_in_small a trouve ptr\n");
					return (1);
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
	//ft_putstr("ne trouve pas dans smalll\n");
	return (0);
}

void			*get_small_ptr(t_small *small, size_t size)
{
	int			i;
	void		*new_ptr;

	i = 0;
	new_ptr = NULL;
	//ft_putstr("rentre get_small_ptr\n");
	if (small == NULL)
		return (NULL);
	while (i < SMALL_TAB_SIZE)
	{
		if (small->tab[0][i] == 0)
		{
			small->tab[1][i] = (int)size;
			g_mapping->nb_allocated += (unsigned long long)size;
			small->tab[0][i] = 1;
			small->nb_alloc += 1;
			//ft_putstr("return small ptr ");
			//print_adress((void *)small->zone_adr + (i * SMALL));
			//ft_putchar('\n');
			return ((void *)small->zone_adr + (i * SMALL));
		}
		i++;
	}
	//ft_putstr("return NULL a get_small_ptr\n");
	return (NULL);
}

void			*get_small_zone(size_t size)
{
	t_small		*new_small;

	//ft_putstr("rentre get_small_ptr\n");
	if (g_mapping == NULL)
		init_mapping();
	if (g_mapping->small == NULL)
		return (get_small_ptr(init_small(), size));
	else
	{
		//ft_putstr("rentre else get_small_zone\n");
		new_small = g_mapping->small;
		while (new_small != NULL)
		{
			if (new_small->nb_alloc < SMALL_TAB_SIZE)
				return (get_small_ptr(new_small, size));
			new_small = new_small->next;
		}
		//ft_putstr("va creer une nouvelle zone small\n");
		return (get_small_ptr(init_small(), size));
	}
}
