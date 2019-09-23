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

static int		find_in_large_2(void *ptr, t_large *tmp)
{
	t_large		*before;

	before = tmp;
	tmp = tmp->next;
	while (tmp != NULL)
	{
		if (tmp->zone_adr == ptr)
		{
			if (munmap(tmp->zone_adr, tmp->size) == -1)
				printf("fail de munmap de la large allouée");
			before->next = tmp->next;
			g_mapping->nb_allocated -= (unsigned long long)tmp->size;
			if (munmap(tmp, sizeof(t_large)) == -1)
				printf("fail de munmap de la structure large");
			return (1);
		}
		before = tmp;
		tmp = tmp->next;
	}
	return (0);
}

static int		find_in_large(void *ptr)
{
	t_large		*tmp;

	tmp = NULL;
	if (g_mapping->large == NULL)
		return (0);
	tmp = g_mapping->large;
	if (tmp->zone_adr == ptr)
	{
		if (munmap(tmp->zone_adr, tmp->size) == -1)
			printf("fail de munmap de la large allouée");
		if (tmp->next == NULL)
			g_mapping->large = NULL;
		else
			g_mapping->large = tmp->next;
		g_mapping->nb_allocated -= (unsigned long long)tmp->size;
		if (munmap(tmp, sizeof(t_large)) == -1)
			printf("fail de munmap de la structure large");
		return (1);
	}
	return (find_in_large_2(ptr, tmp));
}

//todo : il faut que le ptr de retour soit egale a 0x0;
void			ft_free(void *ptr)
{
	t_info		info;

	ft_bzero((void*)&info, sizeof(t_info));
	info.ptr = ptr;
	if (find_in_tiny(&info) == 1 || find_in_small(&info) == 1)
	{
		delete_ptr(&info);
		return ;
	}
	if (find_in_large(ptr) == 1)
		return ;
}
