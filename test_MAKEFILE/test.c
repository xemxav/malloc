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
    char *ptr;

    printf("%p\n", ptr);
    ptr = malloc(5);
    printf("%p\n", ptr);
    free(ptr);
    printf("%p\n", ptr);
    return 0;
}