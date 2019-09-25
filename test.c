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

int main()
{
	void		*data[MAX_ALLOC];

	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		data[i] = malloc(i);
		TEST_NULL(data[i]);

		memset(data[i], 'a', i);
	}
	show_alloc_mem();
	for (size_t i = 1; i < MAX_ALLOC; i += INCR) {
		char	cmp[i];
		char	zzzz[i+1];

		memset(cmp, 'a', i);

		if (memcmp(cmp, data[i], i) != 0) {
			memcpy(zzzz, data[i], i);
			zzzz[i] = 0;
			return -1;
		}

		free(data[i]);
	}
	show_alloc_mem();
    return 0;
}
