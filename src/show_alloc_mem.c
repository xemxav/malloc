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

static size_t		basecount(unsigned long long int n, int base)
{
	size_t			count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= base;
		count++;
	}
	return (count);
}

void				print_adress(void *adrr)
{
	char			*ref;
	size_t			len_adrr;
	char			str[20];
	unsigned long	ul_ad;

	ul_ad = (unsigned long)adrr;
	ref = "0123456789abcdef\0";
	len_adrr = basecount(ul_ad, 16) - 1;
	ft_putstr("0x");
	str[len_adrr + 1] = '\0';
	while ((int)len_adrr >= 0)
	{
		str[(int)len_adrr] = ref[ul_ad % 16];
		ul_ad = ul_ad / 16;
		len_adrr--;
	}
	ft_putstr(str);
}

static void				show_large()
{
	t_large			*large;
	int				i;

	i = 0;
	if (g_mapping == NULL || g_mapping->large == NULL)
		return ;
	large = g_mapping->large;
	while(large != NULL)
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

static void				show_small()
{
	t_small			*small;
	int				i;

	i = 0;
	if (g_mapping == NULL || g_mapping->small == NULL)
		return ;
	small = g_mapping->small;
	while (small != NULL)
	{
		ft_putstr("SMALL : ");
		print_adress((void*)small->zone_adr);
		ft_putstr("\n");
		while (i < TINY_TAB_SIZE)
		{
			if (small->tab[0][i] == 1)
			{
				print_adress((void*)small->zone_adr + (i * SMALL));
				ft_putstr(" - ");
				print_adress((void*)small->zone_adr + (i * SMALL) + small->tab[1][i] - 1);
				ft_putstr(" : ");
				ft_putnbr(small->tab[1][i]);
				ft_putstr(" octets\n");
			}
			i++;
		}
		small = small->next;
	}
}

static void				show_tiny()
{
	t_tiny			*tiny;
	int				i;

	i = 0;
	if (g_mapping == NULL || g_mapping->tiny == NULL)
		return ;
	tiny = g_mapping->tiny;
	while (tiny != NULL)
	{
		ft_putstr("TINY : ");
		print_adress((void*)tiny->zone_adr);
		ft_putstr("\n");
		while (i < TINY_TAB_SIZE)
		{
			if (tiny->tab[0][i])
			{
				print_adress((void*)tiny->zone_adr + (i * TINY));
				ft_putstr(" - ");
				print_adress((void*)tiny->zone_adr + (i * TINY) + tiny->tab[1][i] - 1);
				ft_putstr(" : ");
				ft_putnbr((int)tiny->tab[1][i]);
				ft_putstr(" octets\n");
			}
			i++;
		}
		tiny = tiny->next;
	}
}
void				show_alloc_mem()
{
	show_tiny();
	show_small();
	show_large();
}
