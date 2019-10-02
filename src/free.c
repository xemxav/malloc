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

	//ft_putstr("rentre dans find in large\n");
	tmp = NULL;
	if (g_mapping->large == NULL)
		return (0);
	tmp = g_mapping->large;
	while (tmp != NULL && tmp->zone_adr != info->ptr)
		tmp = tmp->next;
	if (tmp == NULL)
		return (0);
	info->large = tmp;
	//ft_putstr("find in large a trouve\n");
	return (1);
}


void			free(void *ptr)
{
	t_info		info;

	//ft_putstr("rentre dans free pour : ");
	//print_adress(ptr);
	//ft_putstr("\n");
	if (g_mapping == NULL || ptr == 0 || ptr == NULL) {
//		write(1, "FREE OUT\n", 9);
		return;
	}
	ft_bzero((void*)&info, sizeof(t_info));
	info.ptr = ptr;
	if (find_in_tiny(&info) == 1 || find_in_small(&info) == 1
		|| find_in_large(&info) == 1)
	{
		delete_ptr(&info);
		return;
	}
	//ft_putstr("free n'a pas trouve pour : ");
	//print_adress(ptr);
	//ft_putstr("\n");
	return;
}
