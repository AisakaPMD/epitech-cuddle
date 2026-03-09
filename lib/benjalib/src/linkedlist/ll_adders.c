/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Functions adding resources to a linked list
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include <stdlib.h>

#include "benjalib.h"

int ll_push(list_t **list, void *data)
{
    int index = 0;

    if (!list)
        return -1;
    for (; *list; index++) {
        list = &(*list)->next;
    }
    *list = malloc(sizeof(list_t));
    if (!*list)
        return -1;
    (*list)->data = data;
    (*list)->next = NULL;
    return index;
}

int ll_unshift(list_t **list, void *data)
{
    list_t *new_list;

    if (!list)
        return -1;
    new_list = *list;
    *list = malloc(sizeof(list_t));
    if (!*list)
        return -1;
    (*list)->data = data;
    (*list)->next = new_list;
    return 0;
}

void ll_insert(list_t **list, int index, void *data)
{
    if (!list || index < 0)
        return;
    while (index > 0) {
        index--;
        if (!*list)
            return;
        list = &(*list)->next;
    }
    ll_unshift(list, data);
}
