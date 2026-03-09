/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** MyLib memory utils
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/


#include <stdlib.h>

#include "benjalib.h"

void my_memset(void *elt, int c, size_t n)
{
    char *arr = elt;

    if (!arr)
        return;
    for (size_t i = 0; i < n; i++)
        arr[i] = c;
}

void *my_calloc(size_t nmemb, size_t size)
{
    void *ptr = malloc(nmemb * size);

    if (!ptr)
        return NULL;
    my_memset(ptr, 0, nmemb * size);
    return ptr;
}

void safe_free(void *ptr)
{
    void **full_ptr = ptr;

    if (!full_ptr)
        return;
    if (*full_ptr)
        free(*full_ptr);
    *full_ptr = NULL;
}
