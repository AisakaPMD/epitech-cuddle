/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** function to remove data from array list
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include <stdlib.h>

#include "benjalib.h"

void *al_pop(alist_t *list)
{
    void *tmp;

    if (!list)
        return NULL;
    if (list->array_top == 0)
        return NULL;
    tmp = list->array[list->array_top - 1];
    list->array_top--;
    return tmp;
}

void *al_remove(alist_t *list, int index)
{
    void *tmp;

    if (!list || index < 0)
        return NULL;
    if (index >= list->array_top)
        return NULL;
    tmp = list->array[index];
    for (size_t i = index; i < list->array_top - 1; i++) {
        list->array[i] = list->array[i + 1];
    }
    list->array_top--;
    return tmp;
}
