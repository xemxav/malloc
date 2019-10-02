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

//int				find_in_tiny(t_info *info)
//{
//	t_tiny			*tmp;
//
//	//ft_putstr("rentre find_in_tiny\n");
//	if (g_mapping->tiny == NULL)
//		return (0);
//	tmp = g_mapping->tiny;
//	while (tmp != NULL)
//	{
//		if (info->ptr <= (void*)tmp->zone_adr + (TINY_PAGE_SIZE - 1) &&
//			info->ptr >= (void*)tmp->zone_adr)
//		{
//			if ((unsigned long)info->ptr % (unsigned long)TINY == 0)
//			{
//				info->index = (int)(((unsigned long)info->ptr -
//									 (unsigned long)tmp->zone_adr)
//									 		/ (unsigned long)TINY);
//				info->tiny = tmp;
//				//ft_putstr("find_in_small a trouve ptr\n");
//				return (1);
//			}
//		}
//		tmp = tmp->next;
//	}
//	//ft_putstr("ne trouve pas dans tiny\n");
//	return (0);
//}

int				find_in_tiny(t_info *info)
{
	t_tiny			*tmp;
	int				i;

	i = 0;
	//ft_putstr("rentre find_in_tiny\n");
	if (g_mapping->tiny == NULL)
		return (0);
	tmp = g_mapping->tiny;
	while (tmp != NULL)
	{
		if (info->ptr <= (void*)tmp->zone_adr + (TINY_PAGE_SIZE - 1) &&
			info->ptr >= (void*)tmp->zone_adr)
		{
			while (i < TINY_PAGE_SIZE)
			{
				if ((void *)tmp->zone_adr + (i * TINY) == info->ptr && tmp->tab[0][i] == 1)
				{
					info->index = i;
					info->tiny = tmp;
					//ft_putstr("find_in_tiny a trouve ptr\n");
					return (1);
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
	//ft_putstr("ne trouve pas dans tiny\n");
	return (0);
}

void			*get_tiny_ptr(t_tiny *tiny, size_t size)
{
	int			i;
	void		*new_ptr;

	i = 0;
	new_ptr = NULL;
	//ft_putstr("rentre dans a get_tiny_ptr\n");
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
			//ft_putstr("return tiny ptr : ");
			//print_adress((void *)tiny->zone_adr + (i * TINY));
			//ft_putchar('\n');
			return ((void *)tiny->zone_adr + (i * TINY));
		}
		i++;
	}
	//ft_putstr("return NULL a get_tiny_ptr\n");
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
			//ft_putstr("rentre else get_tiny_zone\n");
			if (new_tiny->nb_alloc < TINY_TAB_SIZE)
				return (get_tiny_ptr(new_tiny, size));
			new_tiny = new_tiny->next;
		}
		//ft_putstr("va creer une nouvelle zone tiny\n");
		return (get_tiny_ptr(init_tiny(), size));
	}
}
