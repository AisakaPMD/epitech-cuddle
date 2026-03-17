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

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dataframe.h"

int main(int argc, char **argv)
{
    dataframe_t *df = df_read_csv("type.csv", NULL);
    dataframe_t *test;

    if (!df) {
        fprintf(stderr, "Error reading file\n");
        return 84;
    }
    df_info(df);
    printf("\n\n");

    // tail = df_head(df, 4);
    // test = df_apply(df, "age", apply_func);
    // if (test == NULL)
    //     return 84;
    dataframe_t *new_dataframe = df_to_type(df, "amount", UINT);
    // tail = data_dupe(df);
    // df_disp(test);
    // printf("\n\n");
    df_disp(new_dataframe);
    printf("\n\n");
    df_disp(df);

    dataframe_shape_t shape = df_shape(df);
    printf("Shape: %d rows, %d columns\n", shape.nb_rows, shape.nb_columns);
    df_info(new_dataframe);
    df_write_csv(df, "data_copy.csv");
    free(df);
    return 0;
}
