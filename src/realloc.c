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

t_alloc				*change_alloc_size(t_info *info, size_t req_size)
{
	info->zone->allocated += req_size - info->alloc->size;
	info->alloc->size = req_size;
	return (info->alloc);
}

t_alloc				*same_zone_alloc(t_info *info, size_t req_size)
{
	t_alloc			*fwd_alloc;

	fwd_alloc = NULL;
	if (info->zone->allocs->next == NULL &&
			get_max_zone_adresse(info->zone, req_size) >=
							(void*)info->old_ptr + req_size - 1)
		return (change_alloc_size(info, req_size));
	fwd_alloc = info->alloc->next;
	if (info->old_ptr + req_size <= (void*)fwd_alloc)
		return (change_alloc_size(info, req_size));
	return (NULL);
}

void    			*ft_realloc(void *ptr, size_t size)
{
	void			*new_ptr;
	t_info			info;
	int				req_zone_type;
	t_alloc			*new_alloc;

	new_ptr = NULL;
	new_alloc = NULL;
	ft_bzero((void*)&info, sizeof(t_info));
	if (size <= 0 || ptr == NULL || g_zone == NULL)
		return (ptr); //todo: verifier si return NULL ou le ptr
	info.old_ptr = ptr;
	retrieve_alloc_from_ptr(&info);
	if (info.alloc == NULL || info.zone == NULL)
		return (NULL);
	req_zone_type = get_zone_type(size);
//	if (req_zone_type == info.zone->type_size)
//		new_alloc = same_zone_alloc(&info);
////		si info.alloc->next == NULL et assez de place -> modifier size ok
////		todo : si info.alloc->next == NULL et pas assez de place -> trouver de la placxe
////		si info.alloc et diff avec la prochaine assez grande -> modifier size ok
////		todo : si info.alloc et diff avec next pas assez grande -> nouvele aloc si assez de place
//
//
//	else
//	{
//		//trouver une place avec de la place -> get_current va donner une page ou la créer
//		//
//	}
	new_ptr = get_ptr_from_alloc(new_alloc);
	return (new_ptr);
}