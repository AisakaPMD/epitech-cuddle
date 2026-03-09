/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Functions removing resources from a linked list
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include <stdlib.h>

#include "benjalib.h"

void *ll_pop(list_t **list)
{
    void *tmp;

    if (!list || !*list)
        return NULL;
    while ((*list)->next) {
        list = &(*list)->next;
    }
    tmp = (*list)->data;
    free(*list);
    *list = NULL;
    return tmp;
}

void *ll_shift(list_t **list)
{
    void *tmp;
    list_t *next_tmp;

    if (!list || !*list)
        return NULL;
    next_tmp = (*list)->next;
    tmp = (*list)->data;
    free(*list);
    *list = next_tmp;
    return tmp;
}

void *ll_remove(list_t **list, int index)
{
    if (!list || index < 0)
        return NULL;
    while (index > 0) {
        index--;
        if (!*list)
            return NULL;
        list = &(*list)->next;
    }
    return ll_shift(list);
}
