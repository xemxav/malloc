//
// Created by Xavier-emmanuel Moreau on 2019-09-03.
//

#ifndef MALLOC_H
#define MALLOC_H

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>

# include <stdio.h>


# define TINY 16
# define SMALL 512
# define LARGE 1024

typedef struct		s_alloc
{

	size_t 			size;			// taille du malloc
	struct s_alloc	*next;			// adresse de la suivante
}					t_alloc; 		// adresse du debut d'un malloc

typedef struct 	s_zone
{

	int 			allocated;		// nb d'octet aloués dans la zone
	int				type_size;  	// type de zone
	t_alloc			*allocs;		//liste chainé des differentes allocs
	struct s_zone	*next;

}					t_zone;

extern t_zone		*g_zone;


/*
 *  MALLOC.C
*/

void    			*ft_malloc(size_t size);
void				*get_tiny(size_t size);
//void				*get_small(size_t size);
//void				*get_large(size_t size);


/*
 *  ZONING.C
*/

int					init_zoning(int page_nb);
t_alloc				*make_new_alloc(size_t size, t_zone *current_zone);
t_zone				*get_current_zone(int type_size, int req_size);


/*
 *  SHOw_ALLOC_MEM
*/

void 				show_alloc_mem();
void				print_adress(unsigned long adrr);

//void    			ft_free(void *ptr);
//void    			*ft_realloc(void *ptr, size_t size);

#endif
