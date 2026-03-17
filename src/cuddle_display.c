/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** Project's entry point
** Auto-Generated with Episetup by Amélie
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include <stdio.h>

#include "dataframe.h"

static void df_print_column(dataframe_t *frame, int j, int i)
{
    switch (frame->column_types[i]) {
        case INT:
            printf("%10d |", DF_GET(frame, j, i, int));
            break;
        case UINT:
            printf("%10u |", DF_GET(frame, j, i, unsigned int));
            break;
        case FLOAT:
            printf("%10.3f |", DF_GET(frame, j, i, float));
            break;
        case BOOL:
            printf("%10d |", DF_GET(frame, j, i, char));
            break;
        case STRING:
        default:
            printf("%10s |", (char *) frame->data[j][i]);
    }
}

void df_disp(dataframe_t *frame)
{
    for (int i = 0; i < frame->nb_columns; i++)
        printf("%10s |", frame->column_names[i]);
    printf("\n\n");
    for (int j = 0; j < frame->nb_rows; j++) {
        for (int i = 0; i < frame->nb_columns; i++) {
            df_print_column(frame, j, i);
        }
        printf("\n");
    }
}
