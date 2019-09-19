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

# define TINY 16
# define SMALL 512
# define LARGE 513
# define TINY_PAGE_SIZE (1 * getpagesize())
# define SMALL_PAGE_SIZE (12 * getpagesize())

#define TYNY_TAB_SIZE (getpagesize() / TYNY)
#define SMALL_TAB_SIZE ((SMALL * 100) / getpagesize())

typedef struct		s_tiny
{
	void			*zone_adr;
	char			tab[2][TYNY_TAB_SIZE];
	int 			*nb_alloc;
	struct s_tyny	*next;
}					t_tiny;

typedef struct		s_small
{
	void			*zone_adr;
	int				tab[2][SMALL_TAB_SIZE];
	int 			*nb_alloc;
	struct s_small	*next;
}					t_small;

typedef struct 		s_zone_large
{
	void			*zone_adr;
	size_t			size;
	struct s_large	*next;
}					t_large;

typedef struct		s_mapping
{
	struct s_tiny	*tiny;
	struct s_tiny	*small;
	struct s_tiny	*large;
}					t_mapping;

extern				*g_mapping;

/*
**		MALLOC.C
*/
void				*ft_malloc(size_t size);
//t_alloc				*make_new_alloc(size_t size, t_zone *current_zone);
//int					get_zone_type(size_t size);
/*
**		GET_ADRESSES.C
*/
//void				*get_ptr_from_alloc(t_alloc	*alloc);
//t_alloc				*get_new_alloc_from_last(t_alloc *last);
//void				*get_max_zone_adresse(t_zone	*zone,size_t size);

/*
**		REALLOC.C
*/
void    			*ft_realloc(void *ptr, size_t size);
/*
** 		ZONING.C
*/
//t_zone				*create_zone(int zone_size, size_t size);
//t_zone				*get_current_zone(int z_size, int req_size,
//												t_zone *current_zone);
//int 				has_enough_place(t_zone *zone, size_t req_size,
//												int to_create);
//size_t				get_mult(int zone_size, size_t size);

/*
**		ALLOCATIONS.C
*/
//t_alloc				*make_new_alloc(size_t size, t_zone *current_zone);
//void				retrieve_alloc_from_ptr(t_info *info);

/*
**		SHOw_ALLOC_MEM.C
*/
//void				show_alloc_mem();
void				print_adress(void *adrr);
/*
**		SHOw_ALLOC_MEM_EX.C
*/
void				show_alloc_mem_ex(void *zone, size_t size);
/*
**		FREE.C
*/
//void    			ft_free(void *ptr);
//void				delete_alloc(t_info *info);

#endif
