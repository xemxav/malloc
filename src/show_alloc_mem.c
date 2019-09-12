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


void	print_adress(unsigned long adrr)
{
	char	*ref;
	size_t	len_adrr;

	char	str[20];

	ref = "0123456789abcdef\0";
	len_adrr = basecount(adrr, 16) - 1;
	ft_putstr("0x");
	str[len_adrr + 1] = '\0';
	while ((int)len_adrr >= 0) //il faut partir de la fin
	{
		str[(int)len_adrr] = ref[adrr % 16];
		adrr = adrr / 16;
		len_adrr--;
	}
	ft_putstr(str);
}

static void print_allocs(t_zone *zone)
{
	t_alloc	*tmp;

	tmp = NULL;
	if (zone->allocs == NULL)
		return;
	tmp = (t_alloc*)zone->allocs;
	while (tmp != NULL)
	{
		print_adress((unsigned long)tmp);
		ft_putstr(" - ");
		print_adress((unsigned long)tmp + tmp->size);
		ft_putstr(" : ");
		ft_putnbr(tmp->size);
		ft_putstr(" octets\n");
		tmp = tmp->next;
	}
}

static void	show_type(int type_size, char *type)
{
	t_zone	*tmp;

	tmp = g_zone;
	while(tmp != NULL)
	{
		if (tmp->type_size == type_size)
		{
			ft_putstr(type);
			ft_putstr(" : ");
			print_adress((unsigned long)(void*)tmp);
			ft_putchar('\n');
			print_allocs(tmp);
			ft_putchar('\n');
		}
		tmp = tmp->next;
	}

}

void 	show_alloc_mem()
{

	show_type(TINY, "TINY");
//	show_type(SMALL, "SMALL");
//	show_type(LARGE, "LARGE");
}