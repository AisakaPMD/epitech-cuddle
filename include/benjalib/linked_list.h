/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Include file for linked list functions
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#ifndef LINKED_LIST_H
    #define LINKED_LIST_H

    #include "system_includes.h"

typedef struct list_s {
    void *data;
    struct list_s *next;
} list_t;

int ll_push(list_t **list, void *data);
int ll_unshift(list_t **list, void *data);
void ll_insert(list_t **list, int index, void *data);

void *ll_pop(list_t **list);
void *ll_shift(list_t **list);
void *ll_remove(list_t **list, int index);

int ll_size(list_t *list);
void ll_free(list_t *list);
void ll_reverse(list_t **list);
void ll_foreach(list_t *list, void (*f)(void *));
void ll_map(list_t *list, void *(*f)(void *));

#endif
