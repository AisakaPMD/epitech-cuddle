/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** functions to add data to array lists
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include <stdlib.h>

#include "benjalib.h"

int al_push(alist_t *list, void *data)
{
    if (list->array_top == list->array_size) {
        if (al_extend(list))
            return 1;
    }
    list->array[list->array_top] = data;
    list->array_top++;
    return 0;
}

void al_insert(alist_t *list, int index, void *data)
{
    if (!list || index < 0)
        return;
    if (list->array_top == list->array_size && al_extend(list))
        return;
    if (index >= list->array_top) {
        al_push(list, data);
        return;
    }
    for (size_t i = list->array_top; i > index; i--) {
        list->array[i] = list->array[i - 1];
    }
    list->array[index] = data;
    list->array_top++;
}
