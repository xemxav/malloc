//
// Created by Xavier-emmanuel Moreau on 2019-09-10.
//

#include "../includes/malloc.h"

t_zone		*g_zone = NULL;

t_zone		*get_current_zone(int zone_size, int req_size)
{
	t_zone	*tmp;

	tmp = g_zone;
	if (zone_size == LARGE)
		return (create_zone(zone_size));
	while(tmp != NULL)
	{
//		Todo : Changer la taille du multiple de get page size (faire un macor avec zone size ?
		if (tmp->type_size == zone_size)
			if ((tmp->allocated + req_size + sizeof(t_alloc)) <= (unsigned long)(getpagesize() * 1))
				return (tmp);
		tmp = tmp->next;
	}
	return (create_zone(zone_size));
}

//todo : creer une fonction qui verifie si il y a de la place pour une alloc entre 2 allocs
t_alloc			*make_new_alloc(size_t size, t_zone *current_zone)
{
	t_alloc		*new;
	t_alloc		*last;
	unsigned char *addr;

	new = NULL;
	last = NULL;
	if (current_zone->allocs == NULL)
	{
		addr = (unsigned char*)current_zone;
		addr = addr + sizeof(current_zone) + 1;
		new = (t_alloc*)addr;
		new->size = size;
		new->next = NULL;
		current_zone->allocated += sizeof(t_alloc) + size;
		current_zone->allocs = new;
	}
	else
	{
		last = current_zone->allocs;
		while(last->next != NULL)
			last = last->next;
		addr = (unsigned char*)last;
		addr = addr + sizeof(last) + 1;
		new = (t_alloc*)addr;
		last->next = new;
		new->next = NULL;
		new->size = size;
		current_zone->allocated += sizeof(t_alloc) + size;
	}
	return (new);
}


t_zone		*create_zone(int zone_size)
{
	t_zone	*new_zone;
	t_zone	*tmp;

//	Todo : Changer la taille du multiple de get page size (faire un macor avec zone size ?
	if ((new_zone = (t_zone*)mmap(0, getpagesize() * 1, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	if (g_zone == NULL)
		g_zone = new_zone;
	else
	{
		tmp = g_zone;
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_zone;
	}
	new_zone->allocated = sizeof(t_zone);
	new_zone->type_size = zone_size;
	new_zone->next = NULL;
	new_zone->allocs = NULL;
	return (new_zone);
}
