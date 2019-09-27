//
// Created by Xavier-emmanuel Moreau on 2019-09-04.
//


#include "includes/malloc.h"
#include "string.h"

# define MAX_ALLOC		5000
# define INCR			3
# define SAFE			1

# if SAFE == 1
#  define TEST_NULL(addr) if (addr == NULL) { ft_putstr("null\n"); };
# else
#  define TEST_NULL(addr) ((void)addr)
# endif

void printage(size_t i)
{
	ft_putstr("segment is corrupted = ");
	ft_putnbr(i);
	ft_putchar('\n');
}

void test_null(void *a, size_t i)
{
	if (a == NULL)
	{
		ft_putstr("malloc null : ");
		ft_putnbr(i);
		ft_putchar('\n');
	}
}

int main()
{
	void *data[MAX_ALLOC];
	ssize_t i;
	ft_putstr("page size : ");
	ft_putnbr(getpagesize());
	ft_putchar('\n');
	for (i = 1; i < MAX_ALLOC; i += INCR)
	{
		data[i] = malloc(i);
		TEST_NULL(data[i]);
		test_null(data[i], i);
		memset(data[i], 'a', i);
		if (i == 1024)
		{
			ft_putstr("adresse de malloc pour i = 1024 : ");
			print_adress(data[i]);
			ft_putchar('\n');
		}
	}
	ft_putstr("passe premier for malloc\n");
	show_alloc_mem();
	for (i = 1; i < MAX_ALLOC; i += INCR)
	{
		data[i] = realloc(data[i], i * 2);
		TEST_NULL(data[i]);
		test_null(data[i], i);
		if (i == 1024)
		{
			ft_putstr("adresse de realloc pour i = 1024 : ");
			print_adress(data[i]);
			ft_putchar('\n');
			ft_putstr("SIZE de realloc pour i = 1024 : ");
			ft_putnbr((int)i*2);
			ft_putchar('\n');
		}

		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0)
		{
			printage(i);
			return -1;
		}
	}
	ft_putstr("passe 2 for\n");
	show_alloc_mem();
	for (i = 1; i < MAX_ALLOC; i += INCR)
	{
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0)
		{
			printage(i);
			return -1;
		}
	}
	ft_putstr("passe 3 for\n");
	ft_putstr("i avant boucle de free : ");
	ft_putnbr(i);
	ft_putchar('\n');
//	show_alloc_mem();
	for (i = i - INCR; i > 0; i -= INCR)
	{
		ft_putstr("commence boucle de free for pour i = ");
		ft_putnbr(i);
		ft_putchar('\n');
		ft_putstr("adresse de data[i] = ");
		print_adress(data[i]);
		ft_putchar('\n');
		char cmp[i];
		ft_putstr("passse aloc de cmp\n");
		memset(cmp, 'a', i);
		ft_putstr("passse memset\n");
		if (i == 1024)
			show_alloc_mem();
//		ssize_t b = 0;
		test_null(data[i], i);
//		while (b < i)
//		{
//			ft_putchar(cmp[b]);
//			b++;
//		}
//		ft_putchar('\n');
//		b = 0;
//		char *ddata = (char*)data[i];
//		while (b < i)
//		{
//			ft_putchar(ddata[b]);
//			b++;
//		}
//		ft_putchar('\n');
		if (memcmp(cmp, data[i], i) != 0)
		{
			printage(i);
			return -1;
		}
		ft_putstr("passse memcmpt\n");
//		ft_putnbr(i);
//		ft_putchar(' ');
//		print_adress(data[i]);
//		ft_putchar('\n');
		free(data[i]);
		ft_putstr("passe free\n\n");

	}
	ft_putstr("passe 4 for\n");
	show_alloc_mem();
	return 0;
}
