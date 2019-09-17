//
// Created by Xavier-emmanuel Moreau on 2019-09-12.
//

#include "../includes/malloc.h"

static size_t	basecount(unsigned long long int n, int base)
{
	size_t		count;

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


void			print_adress(void *adrr)
{
	char		*ref;
	size_t		len_adrr;
	char		str[20];
	unsigned long ul_ad;

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

static void 	print_allocs(t_zone *zone)
{
	t_alloc		*tmp;

	tmp = NULL;
	if (zone->allocs == NULL)
		return;
	tmp = zone->allocs;
	while (tmp != NULL)
	{
		print_adress((void*)(tmp) + sizeof(t_alloc) + 1);
		ft_putstr(" - ");
		print_adress((void*)(tmp) + sizeof(t_alloc) + 1 + tmp->size);
		ft_putstr(" : ");
		ft_putnbr(tmp->size);
		ft_putstr(" octets\n");
		tmp = tmp->next;
	}
}

static void		show_type(int type_size, char *type)
{
	t_zone		*tmp;

	tmp = g_zone;
	while(tmp != NULL)
	{
		if (tmp->type_size == type_size)
		{
			// todo: enlever les print de tests
			ft_putstr(type);
			ft_putchar(' ');
			ft_putnbr(tmp->allocated);
			ft_putchar(' ');
			ft_putnbr(sizeof(t_zone) + 2 * sizeof(t_alloc));
			ft_putstr(" : ");
			print_adress((void*)tmp);
			ft_putchar('\n');
			print_allocs(tmp);
		}
		tmp = tmp->next;
	}

}

static void		print_hexa(unsigned char tmp)
{
	char		*ref;
	char		str[3];
	int			i;

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


void	show_alloc_mem_ex(void *zone, size_t size)
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

void 	show_alloc_mem()
{

	show_type(TINY, "TINY");
//	show_type(SMALL, "SMALL");
//	show_type(LARGE, "LARGE");
}