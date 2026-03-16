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

#include <benjalib.h>
#include <ctype.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "dataframe.h"
#include "../include/dataframe.h"


void *agg_func(void **values, int nb_values)
{
    int *sum = malloc(sizeof(int));
    *sum = 0;
    for (int i = 0; i < nb_values; i++) {
        *sum += *(int *)values[i];
    }
    return sum;
}

dataframe_t *df_groupby(dataframe_t *dataframe, const char *aggregate_by, const char
    **to_aggregate, void *(*agg_func)(void **values, int nb_values))
{
    dataframe_t *df = data_dupe(dataframe);
    int column_place = 0;
    int a = 0;
    int count = 0;

    for (; to_aggregate[a]; a++);
    int *aggre_place = malloc(sizeof(int) * (a + 1));
    void **inf = malloc(sizeof(void *) * a);
    for (int i = 0; i < a; i++) {
        *inf = malloc(sizeof(void *) * df->nb_rows);
    }
    aggre_place[a] = -1;
    for (int i = 0; df->column_names[i]; i++) {
        if (!my_strcmp(df->column_names[i], aggregate_by ))
            column_place = i;
        for (int j = 0; j < a; j++) {
            if (!my_strcmp(df->column_names[i], to_aggregate[j])) {
                aggre_place[count] = i;
                count++;
            }
        }
    }
    for (int i = 0; df->data[i][column_place]; i++) {

        // agg_func();
    }
}