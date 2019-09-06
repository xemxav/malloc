//
// Created by Xavier-emmanuel Moreau on 2019-09-04.
//


#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>
#include <string.h>

int main()
{
    int i;
    int nb;
    char c;
    char *str;
    int ps;
    int limit;
    struct rlimit rlim;
    int errnum;

    nb = 20;
    c = 'c';

    str = (char*)mmap(0, nb + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (str == NULL)
    {
        printf("nulll");
    }
    i = 0;
    while (i < nb)
    {
        str[i] = c;
        i++;
    }
    str[i] = '\0';
    printf("%s\n", str);

    printf("%d\n", getpagesize());
    limit =  getrlimit(RLIMIT_MEMLOCK, &rlim);
    if (limit == -1)
    {
        printf("Value of errno: %d\n", errno);
        perror("rgrgr");
    }
    else
    {
        printf("getrlimit = %d\n", limit);
        printf("%llx\n",rlim.rlim_cur);
        printf("%llx\n",rlim.rlim_max);
    }
    return 0;
}