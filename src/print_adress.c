/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_adress.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xmoreau <xmoreau@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/20 17:28:08 by xmoreau      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/20 17:28:08 by xmoreau     ###    #+. /#+    ###.fr     */
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
	//ft_putstr("0x");
	str[len_adrr + 1] = '\0';
	while ((int)len_adrr >= 0)
	{
		str[(int)len_adrr] = ref[ul_ad % 16];
		ul_ad = ul_ad / 16;
		len_adrr--;
	}
	//ft_putstr(str);
}
