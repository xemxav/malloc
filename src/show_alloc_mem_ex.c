/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   show_alloc_mem_ex.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 13:51:36 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 13:51:36 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void			print_hexa(unsigned char tmp)
{
	char			*ref;
	char			str[3];
	int				i;

	i = 1;
	ref = "0123456789abcdef\0";
	str[2] = '\0';
	while (i >= 0)
	{
		str[i] = ref[tmp % 16];
		tmp /= 16;
		i--;
	}
	ft_putstr(str);
}

void				show_alloc_mem_ex(void *zone, size_t size)
{
	size_t			i;
	int				y;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char *)zone;
	while (i < size)
	{
		y = 0;
		print_adress(zone);
		ft_putchar(' ');
		while (y < 16)
		{
			print_hexa(tmp[i]);
			i++;
			y++;
			zone++;
			if (y < 16)
				ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}
