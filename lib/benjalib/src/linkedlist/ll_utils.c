/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Utilities for linked lists
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include <stdlib.h>
#include "benjalib.h"

void ll_free(list_t *list)
{
    list_t *tmp;

    while (list) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

int ll_size(list_t *list)
{
    int size = 0;

    for (; list; list = list->next)
        size++;
    return size;
}

void ll_reverse(list_t **list)
{
    list_t *newlst = NULL;

    if (!list)
        return;
    while (*list) {
        ll_unshift(&newlst, ll_shift(list));
    }
    *list = newlst;
}

void ll_foreach(list_t *list, void (*f)(void *))
{
    for (; list; list = list->next)
        f(list->data);
}

void ll_map(list_t *list, void *(*f)(void *))
{
    for (; list; list = list->next)
        list->data = f(list->data);
}
