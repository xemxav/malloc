//
// Created by Xavier-emmanuel Moreau on 2019-09-04.
//


#include "includes/malloc.h"
#include "string.h"
//#include <stdlib.h>
#include "../libft/libft.h"

# define MAX_ALLOC		5000
# define INCR			3
# define SAFE			1

# if SAFE == 1
#  define TEST_NULL(addr) if (addr == NULL) { ft_putstr("null\n"); };
# else
#  define TEST_NULL(addr) ((void)addr)
# endif

void printage(size_t i, void *a)
{
	ft_putstr("segment is corrupted = ");
	ft_putnbr(i);
	ft_putchar('\n');
	ft_putstr("adresse du segment : ");
	print_adress(a);
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

void print(char *s)
{
	write(1, s, strlen(s));
}

int		test_1()
{
	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {

		void	*data = malloc(i);

		TEST_NULL(data);
		test_null(data, i);
		memset(data, 'a', i);

		free(data);
	}
	return 0;
}

int		test_2()
{
	void		*data[MAX_ALLOC];

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		data[i] = malloc(i);

		TEST_NULL(data[i]); test_null(data[i],i);


		memset(data[i], 'a', i);
	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		char	cmp[i];

		memset(cmp, 'a', i);

		if (memcmp(cmp, data[i], i) != 0) {
			printage(i, data[i]);
			return -1;
		}

		free(data[i]);
	}
	return 0;
}

int		test_3()
{
	void		*data[MAX_ALLOC];

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		data[i] = malloc(i);

		TEST_NULL(data[i]); test_null(data[i],i);


	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		memset(data[i], 'a', i);

		free(data[i]);
	}
	return 0;
}

int		test_4()
{
	void		*data[MAX_ALLOC];

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		data[i] = malloc(i);

		TEST_NULL(data[i]); test_null(data[i],i);


	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		memset(data[i], 'a', i);
	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		char		cmp[i];

		memset(cmp, 'a', i);

		if (memcmp(cmp, data[i], i) != 0) {
			printage(i, data[i]);
			return -1;
		}

		free(data[i]);
	}
	return 0;
}

int		test_5()
{
	void		*data[MAX_ALLOC];

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		data[i] = malloc(i);

		TEST_NULL(data[i]); test_null(data[i],i);

		memset(data[i], 'a', i);


	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0) {
			printage(i, data[i]);
			return -1;
		}
	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0) {
			printage(i, data[i]);
			return -1;
		}

		free(data[i]);
	}
	return 0;
}

int test_6()
{
	void *data[MAX_ALLOC];

	for (size_t len = 0; len < MAX_ALLOC; len += INCR)
	{
		char cmp[len];

		memset(cmp, 'a', len);

		for (size_t i = 1; i < MAX_ALLOC; i += INCR)
		{
			data[i] = malloc(len);

			TEST_NULL(data[i]); test_null(data[i],i);

			memset(data[i], 'a', len);

		}

		for (size_t i = 1; i < MAX_ALLOC; i += INCR)
		{
			if (memcmp(cmp, data[i], len) != 0)
			{
				printage(i, data[i]);
				return -1;
			}
		}

		for (size_t i = 1; i < MAX_ALLOC; i += INCR)
		{
			if (memcmp(cmp, data[i], len) != 0)
			{
				printage(i, data[i]);
				return -1;
			}

			free(data[i]);
		}
	}
	return 0;
}

int		test_7()
{
	void		*data[MAX_ALLOC];
	
	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		data[i] = realloc(NULL, i);

		TEST_NULL(data[i]); test_null(data[i],i);

		memset(data[i], 'a', i);


	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0) {
			printage(i, data[i]);
			return -1;
		}
	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0) {
			printage(i, data[i]);
			return -1;
		}

		free(data[i]);
	}
	return 0;
}

int test_8()
{
	void *data[MAX_ALLOC];

	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		data[i] = malloc(i);

		TEST_NULL(data[i]); test_null(data[i],i);

		data[i] = realloc(data[i], i);

		TEST_NULL(data[i]); test_null(data[i],i);

		memset(data[i], 'a', i);


	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0)
		{
			printage(i, data[i]);
			return -1;
		}
	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0)
		{
			printage(i, data[i]);
			return -1;
		}

		free(data[i]);
	}
	return 0;
}

int test_9()
{
	void *data[MAX_ALLOC];

	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		data[i] = malloc(i);
		TEST_NULL(data[i]); test_null(data[i],i);

		memset(data[i], 'a', i);
	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		data[i] = realloc(data[i], i);
		TEST_NULL(data[i]); test_null(data[i],i);

		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0)
		{
			printage(i, data[i]);
			return -1;
		}
	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0)
		{
			printage(i, data[i]);
			return -1;
		}
	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0)
		{
			printage(i, data[i]);
			return -1;
		}

		free(data[i]);
	}
	return 0;
}

int test_10()
{
	void *data[MAX_ALLOC];

	for (size_t i = 2; i < MAX_ALLOC; i += INCR)
	{
		data[i] = malloc(i);
		TEST_NULL(data[i]); test_null(data[i],i);

		memset(data[i], 'a', i);
	}

	for (size_t i = 2; i < MAX_ALLOC; i += INCR)
	{
		data[i] = realloc(data[i], i / 2);
		TEST_NULL(data[i]); test_null(data[i],i);

		char cmp[i / 2];

		memset(cmp, 'a', i / 2);
		if (memcmp(cmp, data[i], i / 2) != 0)
		{
			printage(i, data[i]);
			return -1;
		}
	}

	for (size_t i = 2; i < MAX_ALLOC; i += INCR)
	{
		char cmp[i / 2];

		memset(cmp, 'a', i / 2);
		if (memcmp(cmp, data[i], i / 2) != 0)
		{
			printage(i, data[i]);
			return -1;
		}
	}

	for (size_t i = 2; i < MAX_ALLOC; i += INCR)
	{
		char cmp[i];

		memset(cmp, 'a', i / 2);
		if (memcmp(cmp, data[i], i / 2) != 0)
		{
			printage(i, data[i]);
			return -1;
		}

		free(data[i]);
	}
	return 0;
}

int test_11()
{
	void *data[MAX_ALLOC];

	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		data[i] = malloc(i);

		TEST_NULL(data[i]); test_null(data[i],i);

		memset(data[i], 'a', i);
	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		data[i] = realloc(data[i], i * 2);
		TEST_NULL(data[i]); test_null(data[i],i);
		
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0)
		{
			printage(i, data[i]);
			return -1;
		}
	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0)
		{
			printage(i, data[i]);
			return -1;
		}
	}

	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0)
		{
			printage(i, data[i]);
			return -1;
		}

		free(data[i]);
	}
	return 0;
}

int test_12()
{
	void *data[MAX_ALLOC];
	ssize_t i;

	for (i = 1; i < MAX_ALLOC; i += INCR)
	{
		data[i] = malloc(i);
		TEST_NULL(data[i]); test_null(data[i],i);

		memset(data[i], 'a', i);
	}

	for (i = 1; i < MAX_ALLOC; i += INCR)
	{
		data[i] = realloc(data[i], i * 2);
		TEST_NULL(data[i]); test_null(data[i],i);
		
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0)
		{
			printage(i, data[i]);
			return -1;
		}
	}

	for (i = 1; i < MAX_ALLOC; i += INCR)
	{
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0)
		{
			printage(i, data[i]);
			return -1;
		}
	}

	for (i = i - INCR; i > 0; i -= INCR)
	{
		char cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, data[i], i) != 0)
		{
			printage(i, data[i]);
			return -1;
		}
		free(data[i]);
	}
	return 0;
}

int main() {
	test_1();
	print("test 1 ok\n");
//	show_alloc_mem();
	test_2();
	print("test 2 ok\n");
	test_3();
	print("test 3 ok\n");
	test_4();
	print("test 4 ok\n");
	test_5();
	print("test 5 ok\n");
	test_6();
	print("test 6 ok\n");
//	test_7();
//	print("test 7 ok\n");
//	test_8();
//	print("test 8 ok\n");
//	test_9();
//	print("test 9 ok\n");
//	test_10();
//	print("test 10 ok\n");
//	test_11();
//	print("test 11 ok\n");
//	test_12();
//	print("test 12 ok\n");
	return (0);
}
