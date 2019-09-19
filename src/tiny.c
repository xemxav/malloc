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

void			*get_tiny_ptr(t_tiny *tiny, size_t size)
{
	int			i;
	void		*new_ptr;

	i = 0;
	new_ptr = NULL;
	printf("get_tiny\n");
	while(i < TINY_TAB_SIZE)
	{
		if (tiny->tab[0][i] == 0)
		{
			tiny->tab[1][i] = (int)size;
			tiny->tab[0][i] = 1;
			return ((void *) tiny->zone_adr + (i * TINY));
		}
		i++;
	}
	return (NULL);
}

void			*get_tiny_zone(size_t size)
{
	t_tiny		*new_tiny;

	printf("get_tiny_zone\n");
	if (g_mapping == NULL)
		init_mapping();
	printf("init_mapping\n");
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