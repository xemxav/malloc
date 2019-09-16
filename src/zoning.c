//
// Created by Xavier-emmanuel Moreau on 2019-09-10.
//

#include "../includes/malloc.h"

t_zone		*g_zone = NULL;


//todo : creer une fonction qui verifie si il y a de la place pour une alloc entre 2 allocs
t_alloc			*make_new_alloc(size_t size, t_zone *current_zone)
{
	t_alloc		*last;
	t_alloc		*adr_new_alloc;


	adr_new_alloc = NULL;
	last = NULL;
	ft_printf("allocated = %d et type size = %d\n", current_zone->allocated, current_zone->type_size);
	if (current_zone->allocs == NULL)
	{
		printf("current zone = %p\n", current_zone);
		adr_new_alloc = (void*)(current_zone) + sizeof(t_zone);
		printf("adr_new_alloc  = %p\n", adr_new_alloc);
		current_zone->allocs = adr_new_alloc;
	}
	else
	{
		last = current_zone->allocs;
		while(last->next != NULL)
			last = last->next;
		printf("last = %p\n", last);
		last->next = (void *)(last + 1) + (last->size + 1);
		adr_new_alloc = last->next;
		printf("adr_new_alloc  = %p\n", adr_new_alloc);

	}
	adr_new_alloc->next = NULL;
	adr_new_alloc->size = size;
	current_zone->allocated += sizeof(t_alloc) + size;
	printf("current_zone->allocs = %p\n", current_zone->allocs);
	return (adr_new_alloc);
}


t_zone		*create_zone(int zone_size)
{
//	t_zone	*adr_new_zone;
	t_zone	*tmp;
	t_zone	*zone;

//	Todo : Changer la taille du multiple de get page size (faire un macor avec zone size ?
//	adr_new_zone = NULL;
	if ((zone = (t_zone*)mmap(0, getpagesize() * 1, PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	if (g_zone == NULL)
		g_zone = zone;
	else
	{
		tmp = g_zone;
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = zone;
	}
//	zone = adr_new_zone;
	zone->allocated = sizeof(t_zone);
	zone->type_size = zone_size;
	zone->next = NULL;
	zone->allocs = NULL;
//	ft_memcpy((void*)adr_new_zone, (void*)&zone, sizeof(zone));
	return (zone);
}


t_zone		*get_current_zone(int zone_size, int req_size)
{
	t_zone	*tmp;

	tmp = g_zone;
	if (zone_size == LARGE || g_zone == NULL)
		return (create_zone(zone_size));
	while(tmp != NULL)
	{
//		Todo : Changer la taille du multiple de get page size (faire un macro avec zone size) ?
		if (tmp->type_size == zone_size)
		{
			if ((tmp->allocated + req_size + sizeof(t_alloc)) <= (unsigned long)(getpagesize() * 1))
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (create_zone(zone_size));
}