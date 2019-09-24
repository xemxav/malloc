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
# define TINY_TAB_SIZE (getpagesize() / TINY)
# define SMALL_TAB_SIZE ((SMALL * 100) / getpagesize())

typedef struct			s_tiny
{
	void				*zone_adr;
	int					**tab;
	int					nb_alloc;
	struct s_tiny		*next;
}						t_tiny;

typedef struct			s_small
{
	void				*zone_adr;
	int					**tab;
	int					nb_alloc;
	struct s_small		*next;
}						t_small;

typedef struct			s_large
{
	void				*zone_adr;
	size_t				size;
	struct s_large		*next;
}						t_large;

typedef struct			s_mapping
{
	struct s_tiny		*tiny;
	struct s_small		*small;
	struct s_large		*large;
	unsigned long long	nb_allocated;
}						t_mapping;

extern t_mapping		*g_mapping;

typedef struct			s_info
{
	struct s_tiny		*tiny;
	struct s_small		*small;
	struct s_large		*large;
	void				*ptr;
	int 				index;
}						t_info;

/*
**		MALLOC.C
*/
void					*malloc(size_t size);

/*
**		TINY.C
*/
void					*get_tiny_ptr(t_tiny *tiny, size_t size);
void					*get_tiny_zone(size_t size);
int						find_in_tiny(t_info *info);
/*
**		SMALL.C
*/
void					*get_small_ptr(t_small *small, size_t size);
void					*get_small_zone(size_t size);
int						find_in_small(t_info *info);
/*
**		REALLOC.C
*/
void    				*realloc(void *ptr, size_t size);
/*
** 		ZONING.C
*/
t_mapping				*init_mapping(void);
t_large					*init_large(size_t size);
t_small					*init_small(void);
t_tiny					*init_tiny(void);
/*
**		SHOw_ALLOC_MEM.C
*/
void					show_alloc_mem(void);
/*
**		PRINT_ADRESS.C
*/
void					print_adress(void *adrr);
/*
**		SHOw_ALLOC_MEM_EX.C
*/
void					show_alloc_mem_ex(void *zone, size_t size);
/*
**		FREE.C
*/
void					free(void *ptr);
int 					find_in_large(t_info *info);
/*
**		DELETING.C
*/
void					delete_tiny_zone(t_info	*info);
void					delete_small_zone(t_info *info);
void					delete_large_zone(t_info *info);
void					delete_ptr(t_info *info);

#endif
