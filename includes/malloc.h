/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 13:35:02 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 13:35:02 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>

# include <stdio.h>

# define TINY 1024
# define SMALL 4096
# define LARGE 4097
# define TINY_MULT 25
# define SMALL_MULT 100

typedef struct		s_alloc
{
	size_t			size;			// taille du malloc
	struct s_alloc	*next;			// adresse de la suivante
}					t_alloc; 		// adresse du debut d'un malloc

typedef struct		s_zone
{

	int				allocated;		// nb d'octet aloués dans la zone
	int				type_size;  	// type de zone
	t_alloc			*allocs;		//liste chainé des differentes allocs
	struct s_zone	*next;

}					t_zone;

extern t_zone		*g_zone;

typedef struct 		s_info
{
	struct s_alloc	*alloc;
	struct s_zone	*zone;
	void			*old_ptr;
}					t_info;

/*
**		MALLOC.C
*/
void				*ft_malloc(size_t size);
t_alloc				*make_new_alloc(size_t size, t_zone *current_zone);
int					get_zone_type(size_t size);
/*
**		GET_ADRESSES.C
*/
void				*get_ptr_from_alloc(t_alloc	*alloc);
t_alloc				*get_new_alloc_from_last(t_alloc *last);
void				*get_max_zone_adresse(t_zone	*zone,size_t size);

/*
**		REALLOC.C
*/
void    			*ft_realloc(void *ptr, size_t size);
/*
** 		ZONING.C
*/
t_zone				*create_zone(int zone_size, size_t size);
t_zone				*get_current_zone(int z_size, int req_size,
												t_zone *current_zone);
int 				has_enough_place(t_zone *zone, size_t req_size,
												int to_create);
size_t				get_mult(int zone_size, size_t size);

/*
**		ALLOCATIONS.C
*/
t_alloc				*make_new_alloc(size_t size, t_zone *current_zone);
void				retrieve_alloc_from_ptr(t_info *info);

/*
**		SHOw_ALLOC_MEM.C
*/
void				show_alloc_mem();
void				print_adress(void *adrr);
/*
**		SHOw_ALLOC_MEM_EX.C
*/
void				show_alloc_mem_ex(void *zone, size_t size);
/*
**		FREE.C
*/
void    			ft_free(void *ptr);
void				delete_alloc(t_info *info);

#endif
