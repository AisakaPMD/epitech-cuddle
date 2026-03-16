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

void *apply_f(void *value)
{
    return value;
}

void *nb_to_str(void *data, column_type_t before,
    column_type_t downcast, int *end)
{
    char buf[1024];

    if (before != STRING && downcast == STRING) {
        switch (before) {
            case INT:
            case UINT:
                snprintf(buf, 1024, "%d", *(int *)data);
                break;
            case FLOAT:
                snprintf(buf, 1024, "%f", *(float *)data);
                break;
            case BOOL:
                snprintf(buf, 1024, "%d", *(bool *)data);
                break;
        }
        data = malloc(sizeof(char *) * strlen(buf));
        strcpy(data, buf);
        *end = 1;
    }
    return data;
}

static char *switch_nb(void *data, column_type_t downcast)
{
    void *temp;

    switch (downcast) {
        case INT:
            temp = calloc(1, sizeof(int));
            *(int *)temp = my_getnbr(data);
            break;
        case UINT:
            temp = calloc(1, sizeof(int));
            *(unsigned int *)temp = my_getnbr(data);
            break;
        case FLOAT:
            temp = calloc(1, sizeof(float));
            *(float *)temp = atof(data);
            break;
        case BOOL:
            temp = calloc(1, sizeof(bool));
            *(bool *)temp = my_getnbr(data);
    }
    return temp;
}

static void *put_inf(void *data, void *temp, char *buf, column_type_t downcast)
{
    data = my_strdup(buf);
    temp = switch_nb(data, downcast);
    free(data);
    data = temp;
    return data;
}

static void *nb_to_nb(void *data, column_type_t before, column_type_t downcast)
{
    char buf[1024];
    void *temp = NULL;

    if (before != STRING && downcast != STRING) {
        switch (before) {
            case INT:
            case UINT:
                snprintf(buf, 1024, "%d", *(int *)data);
                break;
            case FLOAT:
                snprintf(buf, 1024, "%f", *(float *)data);
                break;
            case BOOL:
                snprintf(buf, 1024, "%d", *(bool *)data);
                break;
        }
        data = put_inf(data, temp, buf, downcast);
        return data;
    }
    return data;
}

static int change_type(const char *column, dataframe_t *df,
    column_type_t downcast)
{
    int column_place = 0;

    for (; column_place < df->nb_columns; column_place++)
        if (my_strcmp(df->column_names[column_place], column) == 0) {
            df->column_types[column_place] = downcast;
            break;
        }
    return column_place;
}

dataframe_t *df_to_type(dataframe_t *dataframe,
    const char *column, column_type_t downcast)
{
    dataframe_t *df = data_dupe(dataframe);
    int column_place = change_type(column, df, downcast);
    int end = 0;

    for (int i = 0; i < df->nb_rows; i++) {
        end = 0;
        df->data[i][column_place] = str_to_nb(df->data[i][column_place],
            dataframe->column_types[column_place], downcast, &end);
        if (end == 1)
            continue;
        df->data[i][column_place] = nb_to_str(df->data[i][column_place],
            dataframe->column_types[column_place], downcast, &end);
        if (end == 1)
            continue;
        df->data[i][column_place] = nb_to_nb(df->data[i][column_place],
            dataframe->column_types[column_place], downcast);
    }
    return df;
}

void *apply_func(void *value)
{
    int *new_value = malloc(sizeof(int));

    *new_value = *(int *)value * 2;
    printf("age: %d\n", *new_value);
    return new_value;
}

dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *value))
{
    dataframe_t *df = data_dupe(dataframe);
    int column_place = 0;

    for (; column_place < df->nb_columns; column_place++)
        if (my_strcmp(df->column_names[column_place], column) == 0)
            break;
    for (int i = 0; i < df->nb_rows; i++)
        df->data[i][column_place] =
            apply_func(dataframe->data[i][column_place]);
    return df;
}
