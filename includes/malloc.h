//
// Created by Xavier-emmanuel Moreau on 2019-09-03.
//

#ifndef MALLOC_H
#define MALLOC_H

#include "../libft/libft.h"
#include <unistd.h>
#include <sys/mman.h>
#include <sys/resource.h>


#define TINY 16
#define SMALL 64
#define LARGE 256

#typedef struct		s_zone
{
	void			*adr;
	int 			size;
	struct s_zone	*next;
}					t_zone;

#typedef struct 	s_postal
{
	void			*addr;
	int 			size;
	int				type_size;
	t_zone			*zoning;
	struct s_postal	*next;

}					t_postal;

extern t_postal		g_postal = NULL;

void    			*ft_malloc(size_t size);
void    			ft_free(void *ptr);
void    			*ft_realloc(void *ptr, size_t size);

#endif
