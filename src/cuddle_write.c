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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#include "dataframe.h"

static char *my_join(char *separator, char **strings, int nb_strings)
{
    size_t len = 0;
    char *dest = NULL;

    for (int i = 0; i < nb_strings; i++) {
        len += strlen(strings[i]);
    }
    dest = calloc(len + strlen(separator) * nb_strings, sizeof(char));
    if (!dest)
        return NULL;
    for (int i = 0; i < nb_strings; i++) {
        strcat(dest, strings[i]);
        if (i < nb_strings - 1)
            strcat(dest, separator);
    }
    return dest;
}

static char *df_get_as_string(dataframe_t *dataframe, int row, int col)
{
    char *tmp = NULL;

    if (DF_COL_ISNUM(dataframe, col)) {
        tmp = calloc(16, sizeof(char));
        if (!tmp)
            return NULL;
    }
    if (dataframe->column_types[col] == INT)
        sprintf(tmp, "%d", DF_GET(dataframe, row, col, int));
    if (dataframe->column_types[col] == UINT)
        sprintf(tmp, "%u", DF_GET(dataframe, row, col, unsigned int));
    if (dataframe->column_types[col] == FLOAT)
        sprintf(tmp, "%f", DF_GET(dataframe, row, col, float));
    if (DF_COL_ISNUM(dataframe, col))
        return tmp;
    if (dataframe->column_types[col] == BOOL)
        return strdup(DF_GET(dataframe, row, col, char) ? DF_TRUE : DF_FALSE);
    return strdup(dataframe->data[row][col]);
}

static char **df_line_to_string_array(dataframe_t *dataframe, int line)
{
    char **strings = my_calloc(dataframe->nb_columns + 1, sizeof(char *));

    if (!strings)
        return NULL;
    for (int i = 0; i < dataframe->nb_columns; i++) {
        strings[i] = df_get_as_string(dataframe, line, i);
    }
    strings[dataframe->nb_columns] = NULL;
    return strings;
}

static char *my_df_join(char *separator, dataframe_t *df, int line)
{
    char **strings = df_line_to_string_array(df, line);
    char *res = NULL;

    if (!strings)
        return NULL;
    res = my_join(separator, strings, df->nb_columns);
    free_str_arr(strings);
    return res;
}

static int write_data(dataframe_t *dataframe, FILE *file)
{
    char *line;

    if (!file)
        return 84;
    for (int i = 0; i < dataframe->nb_rows; i++) {
        line = my_df_join(",", dataframe, i);
        if (!line)
            return 84;
        fprintf(file, "%s\n", line);
        free(line);
    }
    return 0;
}

int df_write_csv(dataframe_t *dataframe, const char *filename)
{
    FILE *file = fopen(filename, "w");
    char *line = NULL;

    if (!file)
        return 84;
    line = my_join(",", dataframe->column_names, dataframe->nb_columns);
    if (!line) {
        fclose(file);
        return 84;
    }
    fprintf(file, "%s\n", line);
    free(line);
    write_data(dataframe, file);
    fclose(file);
    return 0;
}
