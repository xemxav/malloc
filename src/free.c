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

int 		find_in_large(t_info *info)
{
	t_large		*tmp;

	tmp = NULL;
	if (g_mapping->large == NULL)
		return (0);
	tmp = g_mapping->large;
	if (tmp->zone_adr == info->ptr)
	{
		info->large = tmp;
		return (1);
	}
	tmp = tmp->next;
	while (tmp != NULL && tmp->zone_adr != info->ptr)
		tmp = tmp->next;
	if (tmp == NULL)
		return (0);
	info->large = tmp;
	return (1);
}

//todo : il faut que le ptr de retour soit egale a 0x0;
void			ft_free(void *ptr)
{
	t_info		info;

	ft_bzero((void*)&info, sizeof(t_info));
	info.ptr = ptr;
	if (find_in_tiny(&info) == 1 || find_in_small(&info) == 1
		|| find_in_large(&info) == 1)
		delete_ptr(&info);
	ptr = NULL;
	return;
}
