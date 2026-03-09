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
#include <string.h>

#include "dataframe.h"

static void *df_err(char *msg, ...)
{
    va_list ap;

    va_start(ap, msg);
    fprintf(stderr, "cuddle: ");
    vfprintf(stderr, msg, ap);
    fprintf(stderr, "\n");
    return NULL;
}

static int df_interr(char *msg, ...)
{
    va_list ap;

    va_start(ap, msg);
    fprintf(stderr, "cuddle: ");
    vfprintf(stderr, msg, ap);
    fprintf(stderr, "\n");
    return 84;
}

static int df_isnum(char *str)
{
    int dot_count = 0;

    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i]) && str[i] != '-' && str[i] != '.')
            return 0;
        if (str[i] == '.')
            dot_count++;
        if (dot_count > 1)
            return 0;
        if (str[i] == '-' && i > 0)
            return 0;
    }
    return 1;
}

static int df_isint(char *str)
{
    return strchr(str, '.') == NULL;
}

static int df_readline(dataframe_t *df, char *line, char const *separator)
{
    char **fields = my_explode(line, separator);
    int fields_count = 0;
    void ***data = NULL;

    if (!fields)
        return df_interr("Could not explode line: [%s]\n", line);
    for (; fields[fields_count]; fields_count++);
    if (df->nb_rows == -1) {
        df->nb_rows++;
        // Header row
        df->nb_columns = fields_count;
        df->column_names = my_calloc(df->nb_columns, sizeof(char *));
        df->column_types = my_calloc(df->nb_columns, sizeof(column_type_t *));
        if (!df->column_names || !df->column_types)
            return df_interr("Could not allocate memory for column names or types\n");
        for (size_t i = 0; i < df->nb_columns; i++) {
            df->column_names[i] = strdup(fields[i]);
            df->column_types[i] = UNDEFINED;
        }
        return 0;
    }
    if (df->nb_columns != fields_count)
        return df_interr("Number of columns does not match header row: expected %d, got %d\n", df->nb_columns, fields_count);
    df->nb_rows++;
    data = realloc(df->data, df->nb_rows * sizeof(void **));
    if (!data)
        return df_interr("Could not allocate memory for data\n");
    df->data = data;
    data[df->nb_rows - 1] = my_calloc(df->nb_columns, sizeof(void *));
    if (!data[df->nb_rows - 1])
        return df_interr("Could not allocate memory for row\n");
    for (size_t i = 0; i < df->nb_columns; i++) {
        df->data[df->nb_rows - 1][i] = strdup(fields[i]);
        if (df->column_types[i] == UNDEFINED && strlen(fields[i]))
            df->column_types[i] = BOOL;
        if (df->column_types[i] == BOOL && !df_isnum(fields[i]) &&
            strcmp(fields[i], DF_TRUE) && strcmp(fields[i], DF_FALSE)) {
            df->column_types[i] = STRING;
        }
        if (df->column_types[i] == BOOL && df_isnum(fields[i])) {
            df->column_types[i] = UINT;
        }
        if ((df->column_types[i] == UINT || df->column_types[i] == INT || df->column_types[i] == FLOAT) && !df_isnum(fields[i])) {
            df->column_types[i] = STRING;
        }
        if (df->column_types[i] == UINT || df->column_types[i] == INT) {
            if (df_isint(fields[i])) {
                long val = strtol(fields[i], NULL, 10);
                if (val < 0)
                    df->column_types[i] = INT;
                if ((val < INT_MIN || val > INT_MAX) && df->column_types[i] == INT)
                    df->column_types[i] = STRING;
                else if ((val < INT_MIN || val > INT_MAX) && df->column_types[i] == INT)
                    df->column_types[i] = STRING;
            } else
                df->column_types[i] = FLOAT;
        }
    }
    free_str_arr(fields);
    return 0;
}

static int df_set_columns_type(dataframe_t *df)
{
    long tmp = 0;
    float tmpf = 0;

    for (int i = 0; i < df->nb_columns; i++) {
        for (int j = 0; j < df->nb_rows; j++) {
            if (df->column_types[i] == INT
                || df->column_types[i] == UINT) {
                tmp = strtol(df->data[j][i], NULL, 10);
                safe_free(&df->data[j][i]);
                df->data[j][i] = calloc(1, sizeof(int));
                if (!df->data[j][i])
                    return df_interr("Could not allocate memory for column %d\n", i);
                if (df->column_types[i] == INT)
                    *(int *)df->data[j][i] = (int) tmp;
                else
                    *(unsigned int *)df->data[j][i] = (unsigned int) tmp;
            }
            if (df->column_types[i] == FLOAT) {
                tmpf = strtof(df->data[j][i], NULL);
                safe_free(&df->data[j][i]);
                df->data[j][i] = calloc(1, sizeof(float));
                if (!df->data[j][i])
                    return df_interr("Could not allocate memory for column %d\n", i);
                *(float *)df->data[j][i] = tmpf;
            }
            if (df->column_types[i] == BOOL) {
                safe_free(&df->data[j][i]);
                df->data[j][i] = calloc(1, sizeof(char));
                if (!df->data[j][i])
                    return df_interr("Could not allocate memory for column %d\n", i);
                if (strcmp(df->data[j][i], DF_TRUE) == 0) {
                    *(char *)df->data[j][i] = 1;
                } else if (strcmp(df->data[j][i], DF_FALSE) == 0) {
                    *(char *)df->data[j][i] = 0;
                }
            }
        }
    }
    return 0;
}

dataframe_t *df_read_csv(const char *filename, const char *separator) {
    FILE *file = fopen(filename, "r");
    char *line_buf = NULL;
    size_t buf_len = 0;
    ssize_t read_len = 0;
    dataframe_t *df;

    if (!separator)
        separator = ",";
    if (!file)
        return df_err("Could not open file %s\n", filename);
    df = calloc(1, sizeof(dataframe_t));
    if (!df) {
        fclose(file);
        return df_err("Could not allocate memory\n");
    }
    df->nb_rows = -1;
    while (1) {
        read_len = getline(&line_buf, &buf_len, file);
        if (read_len < 1)
            break;
        line_buf[read_len - 1] = '\0';
        if (df_readline(df, line_buf, separator)) {
            safe_free(&df);
            fclose(file);
            df_err("Could not read file %s: Error decoding line: [%s]\n", filename, line_buf);
            free(line_buf);
            return NULL;
        }
    }
    fclose(file);
    free(line_buf);
    if (df_set_columns_type(df))
        safe_free(&df);
    return df;
}

char *df_get_column_type_name(column_type_t type)
{
    switch (type) {
        case BOOL:
            return "bool";
        case INT:
            return "int";
        case UINT:
            return "unsigned int";
        case FLOAT:
            return "float";
        case STRING:
            return "string";
        default:
            return "undefined";
    }
}

void df_info(dataframe_t *df) {
    printf("%d columns:\n", df->nb_columns);
    for (int i = 0; i < df->nb_columns; i++) {
        printf("- %s: %s\n", df->column_names[i],
            df_get_column_type_name(df->column_types[i]));
    }
}

dataframe_shape_t *df_shape(dataframe_t *df)
{
    dataframe_shape_t *shape = calloc(1, sizeof(dataframe_shape_t));

    if (!shape)
        return NULL;
    shape->nb_rows = df->nb_rows;
    shape->nb_columns = df->nb_columns;
    return shape;
}

// void df_mean_f(dataframe_t *dataframe, int i)
// {
//
// }

void df_describe(dataframe_t *dataframe)
{
    float mean;

    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (!DF_COL_ISNUM(dataframe, i))
            continue;
        printf("Column: %s\n", dataframe->column_names[i]);
        printf("Count: %d\n", dataframe->nb_rows);
        mean = 0;
        for (int j = 0; j < dataframe->nb_rows; j++) {
            mean += *((float *) dataframe->data[j][i]);
        }
        mean /= (float) dataframe->nb_rows;
        printf("Mean: %f\n", mean);
    }
}

void df_disp(dataframe_t *frame)
{
    for (int j = 0; j < frame->nb_rows; j++) {
        for (int i = 0; i < frame->nb_columns; i++) {
            if (frame->column_types[i] == INT)
                printf("%10d | ", *(int *)frame->data[j][i]);
            if (frame->column_types[i] == UINT)
                printf("%10u | ", *(unsigned int *)frame->data[j][i]);
            // if (frame->column_types[i] == 3)
            //     printf("%10ld | ", (long int)frame->data[j][i]);
            // if (frame->column_types[i] == 4)
            //     printf("%10lu | ", (unsigned long int)frame->data[j][i]);
            if (frame->column_types[i] == FLOAT)
                printf("%10f | ", *(double *)frame->data[j][i]);
            if (frame->column_types[i] == BOOL)
                printf("%10d | ", *(char *)frame->data[j][i]);
            if (frame->column_types[i] == STRING)
                printf("%10s | ", (char *)frame->data[j][i]);
        }
        printf("\n");
    }
}

void copy_data(void **copy, void **df, dataframe_t *dataframe)
{
    switch (dataframe->column_types[0])
    {
        case INT:
        case UINT:
        case FLOAT:
        **(int **)copy = **(int **)df;
        return;
        case BOOL:
        **(char **)copy = **(char **)df;
        return;
        case STRING:
        *(char **)copy = strdup(*(char **)df);
        return;
    }
}

dataframe_t *data_dupe(dataframe_t *df)
{
    dataframe_t *copy = calloc(1, sizeof(dataframe_t));

    printf("rows: %d    columns: %d\n", df->nb_rows, df->nb_columns);
    copy->nb_rows = df->nb_rows;
    copy->nb_columns = df->nb_columns;
    copy->column_names = malloc(sizeof(char *) * df->nb_columns);
    copy->data = malloc(sizeof(void **) * df->nb_rows);

    for (int i = 0; i < df->nb_rows; i++) {
        copy->data[i] = malloc(sizeof(void *) * df->nb_columns);
        for (int j = 0; j < df->nb_columns; j++) {
            if (i == 0)
                copy->column_names[j] = strdup(df->column_names[j]);
            printf("data: %p\n", df->data[i][j]);
            copy_data(&copy->data[i][j], &df->data[i][j], df);
        }
    }
    copy->column_types = malloc(sizeof(column_type_t) * df->nb_columns);
    memcpy(copy->column_types, df->column_types,
           sizeof(column_type_t) * df->nb_columns);

    return copy;
}

dataframe_t *df_tail(dataframe_t *dataframe, int amount)
{
    int nb;
    char *buf[amount];
    dataframe_t *df =data_dupe(dataframe);
    int start = dataframe->nb_rows - amount;


    for (int i = dataframe->nb_rows; i > 0; i--) {
        memmove(df->data, dataframe->data[start],sizeof(char *) * amount);
        if (nb == amount)
            break;
        nb++;
    }
    for (int i = 0; i < dataframe->nb_columns; i++) {
        for (int j = 3; j < dataframe->nb_rows; j++) {
            free(dataframe->data[i][j]);
        }
    }
    return df;
}

int main(int argc, char **argv)
{
    dataframe_t *df = df_read_csv("data.csv", NULL);
    dataframe_t *tail;

    if (!df) {
        fprintf(stderr, "Error reading file\n");
        return 84;
    }
    df_info(df);
    printf("\n\n");
    // tail = df_tail(df, 1);
    tail = data_dupe(df);
    df_disp(tail);
    printf("\n\n");
    df_disp(df);

    dataframe_shape_t *shape = df_shape(df);
    if (!shape) {
        free(df);
        return df_interr("Failed to alloc shape");
    }
    printf("Shape: %d rows, %d columns\n", shape->nb_rows, shape->nb_columns);
    free(shape);
    free(df);
    return 0;
}
