/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 14:03:31 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 14:03:31 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void			get_old_alloc(void	*old_ptr, t_info *info)
{
	t_zone			*zone;
	t_alloc			*alloc;

	zone = g_zone;
	while (zone != NULL)
	{
		alloc = zone->allocs;
		while (alloc != NULL)
		{
			if ((void*)(alloc) + sizeof(t_alloc) + 1 == ptr)
			{
				info->zone = zone;
				info->alloc = alloc;
				return ;
			}
			alloc = alloc->next;
		}
		zone = zone->next;
	}
}


void    			*ft_realloc(void *ptr, size_t size)
{
	void		*new_ptr;
	t_info		info;
	int			req_zone_type;

	new_ptr = NULL;
	ft_bzero((void*)&info, sizeof(t_info));
	if (size <= 0)
		return (new_ptr);
	get_old_alloc(ptr, &info);
	if (info.alloc == NULL || info.zone == NULL)
		return (NULL);
	req_zone_type = get_zone_type(size);
	if (req_zone_type == info.zone->type_size)
	{
		si info.alloc->next == NULL et assez de place -> modifier size
		si info.alloc et diff avec la prochaine assez grande -> modifier size
		si info.alloc et diff avec next pas assez grande -> nouvele aloc si assez de place

	}
}