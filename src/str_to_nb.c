/*
** EPITECH PROJECT, 2026
** bscuddle
** File description:
** Project's entry point
** Auto-Generated with Episetup by Amélie
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include <ctype.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "dataframe.h"

static void *which_bool(void *temp, void *data)
{
    temp = calloc(1, sizeof(bool));
    if (!strcmp(data, "true"))
        *(int *)temp = 1;
    else
        *(int *)temp = 0;
    return temp;
}

static void *find_nb(void *data, column_type_t downcast)
{
    void *temp = NULL;

    switch (downcast) {
        case INT:
            temp = calloc(1, sizeof(int));
            *(int *)temp = atoi(data);
            break;
        case FLOAT:
            temp = calloc(1, sizeof(float));
            *(float *)temp = atof(data);
            break;
        case UINT:
            temp = calloc(1, sizeof(int));
            *(unsigned int *)temp = atoi(data);
            break;
        case BOOL:
            temp = which_bool(temp, data);
    }
    return temp;
}

void *str_to_nb(void *data, column_type_t before,
    column_type_t downcast, int *end)
{
    void *temp = NULL;

    if (before == STRING && downcast != STRING) {
        temp = find_nb(data, downcast);
        free(data);
        data = temp;
        *end = 1;
    }
    return data;
}
