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

t_mapping			g_mapping = {NULL, NULL, NULL, 0};

//int					**init_tab(int tab_size)
//{
//	int				**tab;
//
//	tab = (int**)mmap(0, sizeof(int**), PROT_READ |
//	PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
//	if (tab == NULL)
//		return (NULL);
//	tab[0] = (int*)mmap(0, tab_size, PROT_READ |
//	PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
//	tab[1] = (int*)mmap(0, tab_size, PROT_READ |
//	PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
//	if (tab[0] == MAP_FAILED || tab[1] == MAP_FAILED)
//		return (NULL);
//	ft_bzero(tab[0], tab_size);
//	ft_bzero(tab[1], tab_size);
//	return (tab);
//}

t_large				*init_large(size_t size)
{
	t_large			*large;
	t_large			*tmp;

	large = NULL;
//	large = (t_large*)mmap(0, sizeof(t_large),
//			PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	large = (t_large*)mmap(0, getpagesize(),
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (large == MAP_FAILED)
		return (NULL);
	ft_bzero((void*)large, sizeof(t_large));
	if (g_mapping.large == NULL)
		g_mapping.large = large;
	else
	{
		tmp = g_mapping.large;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = large;
	}
	large->zone_adr = (void*)mmap(0, size, PROT_READ
	| PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (large->zone_adr == MAP_FAILED)
		return (NULL);
	return (large);
}

t_small				*init_small(void)
{
	t_small			*small;
	t_small			*tmp;

	small = NULL;
//	small = (t_small*)mmap(0, sizeof(t_small),
//			PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	small = (t_small*)mmap(0, getpagesize(),
						   PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (small == MAP_FAILED)
		return (NULL);
	ft_bzero((void*)small, sizeof(t_small));
	if (g_mapping.small == NULL)
		g_mapping.small = small;
	else
	{
		tmp = g_mapping.small;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = small;
	}
	small->zone_adr = (void*)mmap(0, SMALL_PAGE_SIZE, PROT_READ
	| PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (small->zone_adr == MAP_FAILED)
		return (NULL);
//	if ((small->tab = init_tab(SMALL_TAB_SIZE)) == NULL)
//		return (NULL);
	return (small);
}

t_tiny				*init_tiny(void)
{
	t_tiny			*tiny;
	t_tiny			*tmp;

	tiny = NULL;
//	tiny = (t_tiny*)mmap(0, sizeof(t_tiny),
//			PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	tiny = (t_tiny*)mmap(0, getpagesize(),
						 PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (tiny == MAP_FAILED)
		return (NULL);
	ft_bzero((void*)tiny, sizeof(t_tiny));
	if (g_mapping.tiny == NULL)
		g_mapping.tiny = tiny;
	else
	{
		tmp = g_mapping.tiny;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = tiny;
	}
	tiny->zone_adr = (void*)mmap(0, TINY_PAGE_SIZE, PROT_READ
	| PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
	if (tiny->zone_adr == MAP_FAILED)
		return (NULL);
//	if ((tiny->tab = init_tab(TINY_TAB_SIZE)) == NULL)
//		return (NULL);
	return (tiny);
}
