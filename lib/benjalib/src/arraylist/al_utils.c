/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Utilities for array lists
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include "benjalib.h"
#include <stdlib.h>

void al_free(alist_t *list)
{
    free(list->array);
    free(list);
}

int al_extend(alist_t *list)
{
    void **temp_buffer = NULL;
    size_t new_size = (list->array_size + 2) * 3 / 2;

    temp_buffer = malloc(new_size * sizeof(void *));
    if (!temp_buffer)
        return 1;
    for (size_t i = 0; i < list->array_size; i++)
        temp_buffer[i] = list->array[i];
    free(list->array);
    list->array_size = new_size;
    list->array = temp_buffer;
    return 0;
}

void al_reverse(alist_t *list)
{
}

void al_foreach(alist_t *list, void (*f)(void *))
{
    for (int i = 0; i < list->array_top; i++) {
        f(list->array[i]);
    }
}

void al_map(alist_t *list, void *(*f)(void *))
{
    for (int i = 0; i < list->array_top; i++) {
        list->array[i] = f(list->array[i]);
    }
}
