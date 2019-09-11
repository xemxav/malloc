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


# define TINY 100
# define SMALL 1000
# define LARGE 10000

typedef struct		s_alloc
{

	int 			size;			// taille du malloc
	struct s_zone	*next;			// adresse de la suivante
}					t_alloc; 		// adresse du debut d'un malloc

typedef struct 	s_zone
{

	int 			allocated;		// nb d'octet aloués dans la zone
	int				type_size;  	// type de zone
	t_alloc			*allocs;		//liste chainé des differentes allocs
	struct s_zone	*next;

}					t_zone;

extern t_zone		*g_zone;

void    			*ft_malloc(size_t size);
void    			ft_free(void *ptr);
void    			*ft_realloc(void *ptr, size_t size);

void				init_zoning(size_t size);
void				*get_tiny(size_t size);
//void				*get_small(size_t size);
//void				*get_large(size_t size);

#endif
