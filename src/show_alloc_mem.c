/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   show_alloc_mem.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/17 13:49:19 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 13:49:19 by xmoreau     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void				print_start(char *str, void *adr)
{
	ft_putstr(str);
	print_adress(adr);
	ft_putstr("\n");
}

static void				show_large(void)
{
	t_large				*large;

	large = g_mapping.large;
	while (large != NULL)
	{
		ft_putstr("LARGE : ");
		print_adress((void*)large->zone_adr);
		ft_putstr("\n");
		print_adress((void*)large->zone_adr);
		ft_putstr(" - ");
		print_adress((void*)large->zone_adr + large->size);
		ft_putstr(" : ");
		ft_putnbr(large->size);
		ft_putstr(" octets\n");
		large = large->next;
	}
}

static void				show_small(void)
{
	t_small				*small;
	int					i;


	small = g_mapping.small;
	while (small != NULL)
	{
		i = 0;
		print_start("SMALL : ", (void*)small->zone_adr);
		while (i < SMALL_TAB_SIZE)
		{
			if (small->tab[0][i] == 1)
			{
				print_adress((void*)small->zone_adr + (i * SMALL));
				ft_putstr(" - ");
				print_adress((void*)small->zone_adr +
				(i * SMALL) + small->tab[1][i] - 1);
				ft_putstr(" : ");
				ft_putnbr(small->tab[1][i]);
				ft_putstr(" octets\n");
			}
			i++;
		}
		small = small->next;
	}
}

static void				show_tiny(void)
{
	t_tiny				*tiny;
	int					i;


	tiny = g_mapping.tiny;
	while (tiny != NULL)
	{
		print_start("TINY : ", (void*)tiny->zone_adr);
		i = 0;
		while (i < TINY_TAB_SIZE)
		{
			if (tiny->tab[0][i])
			{
				print_adress((void*)tiny->zone_adr + (i * TINY));
				ft_putstr(" - ");
				print_adress((void*)tiny->zone_adr +
				(i * TINY) + tiny->tab[1][i] - 1);
				ft_putstr(" : ");
				ft_putnbr((int)tiny->tab[1][i]);
				ft_putstr(" octets\n");
			}
			i++;
		}
		tiny = tiny->next;
	}
}

void					show_alloc_mem(void)
{
	if (g_mapping.tiny != NULL && g_mapping.small != NULL &&
	g_mapping.large != NULL)
		return ;
	if (g_mapping.tiny != NULL)
		show_tiny();
	if (g_mapping.small != NULL)
		show_small();
	if (g_mapping.large != NULL)
		show_large();
	ft_putstr("Total : ");
	ft_putnbr(g_mapping.nb_allocated);
	ft_putstr(" octets\n");
}
