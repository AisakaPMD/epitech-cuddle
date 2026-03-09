/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Include file for array list functions
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#ifndef ARRAY_LIST_H
    #define ARRAY_LIST_H

    #include "system_includes.h"

typedef struct array_list_s array_list_t;
typedef struct array_list_s alist_t; // Alternative name

typedef struct array_list_s {
    void **array;
    size_t array_size;
    size_t array_top;
} array_list_t;

alist_t *al_create(void);
void al_destroy(alist_t *list);

int al_push(alist_t *list, void *data);
void al_insert(alist_t *list, int index, void *data);

void *al_pop(alist_t *list);
void *al_remove(alist_t *list, int index);

int al_extend(alist_t *list);
void al_free(alist_t *list);
void al_reverse(alist_t *list);
void al_foreach(alist_t *list, void (*f)(void *));
void al_map(alist_t *list, void *(*f)(void *));

#endif // ARRAY_LIST_H
