/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   zoning.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 12:18:01 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 12:18:01 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_mapping			*g_mapping = NULL;

t_mapping			*init_mapping(void)
{
	t_mapping		*new_map;
	//ft_putstr("rentre dans init_mapping\n");
	new_map = NULL;
	new_map = (t_mapping*)mmap(0, getpagesize(),
							   PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (new_map == MAP_FAILED)
		return (NULL);
	ft_bzero((void*)new_map, sizeof(t_mapping));
	g_mapping = new_map;
	//ft_putstr("return une new_map\n");
	return (new_map);
}

t_large				*init_large(size_t size)
{
	t_large			*large;
	t_large			*tmp;

	//ft_putstr("rentre dans init_large\n");
	large = NULL;
	large = (t_large*)mmap(0, getpagesize(),
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (large == MAP_FAILED)
		return (NULL);
	ft_bzero((void*)large, sizeof(t_large));
	if (g_mapping->large == NULL)
		g_mapping->large = large;
	else
	{
		tmp = g_mapping->large;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = large;
	}
	large->zone_adr = (void*)mmap(0, size, PROT_READ
	| PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (large->zone_adr == MAP_FAILED)
		return (NULL);
	//ft_putstr("retune une zone large\n");
	return (large);
}

t_small				*init_small(void)
{
	t_small			*small;
	t_small			*tmp;

	//ft_putstr("rentre dans init_small\n");
	small = NULL;
	small = (t_small*)mmap(0, getpagesize(),
						   PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (small == MAP_FAILED)
		return (NULL);
	ft_bzero((void*)small, sizeof(t_small));
	if (g_mapping->small == NULL)
		g_mapping->small = small;
	else
	{
		tmp = g_mapping->small;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = small;
	}
	small->zone_adr = (void*)mmap(0, SMALL_PAGE_SIZE, PROT_READ
	| PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (small->zone_adr == MAP_FAILED)
		return (NULL);
	//ft_putstr("return une zone small\n");
	return (small);
}

t_tiny				*init_tiny(void)
{
	t_tiny			*tiny;
	t_tiny			*tmp;
	//ft_putstr("rentre dans init_tiny\n");

	tiny = NULL;
	tiny = (t_tiny*)mmap(0, getpagesize(),
						 PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (tiny == MAP_FAILED)
		return (NULL);
	ft_bzero((void*)tiny, sizeof(t_tiny));
	if (g_mapping->tiny == NULL)
		g_mapping->tiny = tiny;
	else
	{
		tmp = g_mapping->tiny;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = tiny;
	}
	tiny->zone_adr = (void*)mmap(0, TINY_PAGE_SIZE, PROT_READ
	| PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (tiny->zone_adr == MAP_FAILED)
		return (NULL);
	//ft_putstr("return une zone tiny\n");
	return (tiny);
}
