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
    char *tmp_str = NULL;

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
                tmp_str = df->data[j][i];
                df->data[j][i] = calloc(1, sizeof(char));
                if (!df->data[j][i])
                    return df_interr("Could not allocate memory for column %d\n", i);
                if (strcmp(tmp_str, DF_TRUE) == 0) {
                    *(char *)df->data[j][i] = 1;
                } else if (strcmp(tmp_str, DF_FALSE) == 0) {
                    *(char *)df->data[j][i] = 0;
                }
                free(tmp_str);
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

float df_getfloat(dataframe_t *dataframe, int row, int col)
{
    return *((float *) dataframe->data[row][col]);
}

int df_getint(dataframe_t *dataframe, int row, int col)
{
    return *((int *) dataframe->data[row][col]);
}

unsigned int df_getuint(dataframe_t *dataframe, int row, int col)
{
    return *((unsigned int *) dataframe->data[row][col]);
}

float df_mean_f(dataframe_t *dataframe, int col)
{
    float sum = 0;

    for (int i = 0; i < dataframe->nb_rows; i++) {
        sum += df_getfloat(dataframe, i, col);
    }
    return sum / (float) dataframe->nb_rows;
}

float df_mean_i(dataframe_t *dataframe, int col)
{
    float sum = 0;

    for (int i = 0; i < dataframe->nb_rows; i++) {
        sum += (float) df_getint(dataframe, i, col);
    }
    return sum / (float) dataframe->nb_rows;
}

float df_mean_u(dataframe_t *dataframe, int col)
{
    float sum = 0;

    for (int i = 0; i < dataframe->nb_rows; i++) {
        sum += (float) df_getuint(dataframe, i, col);
    }
    return sum / (float) dataframe->nb_rows;
}

void df_describe(dataframe_t *dataframe)
{
    float mean;

    for (int i = 0; i < dataframe->nb_columns; i++) {
        if (!DF_COL_ISNUM(dataframe, i))
            continue;
        printf("Column: %s\n", dataframe->column_names[i]);
        printf("Count: %d\n", dataframe->nb_rows);
        mean = 0;
        if (dataframe->column_types[i] == FLOAT)
            mean = df_mean_f(dataframe, i);
        else if (dataframe->column_types[i] == INT)
            mean = df_mean_i(dataframe, i);
        else if (dataframe->column_types[i] == UINT)
            mean = df_mean_u(dataframe, i);
        printf("Mean: %f\n", mean);
    }
}

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
    char *tmp;

    if (dataframe->column_types[col] == BOOL) {
        // printf("]] %d\n", *((char *) dataframe->data[row][col]));
        return strdup(
            *((char *) dataframe->data[row][col]) ? DF_TRUE : DF_FALSE);
    }
    if (dataframe->column_types[col] == INT) {
        tmp = calloc(16, sizeof(char));
        if (!tmp)
            return NULL;
        sprintf(tmp, "%d", df_getint(dataframe, row, col));
        return tmp;
    }
    if (dataframe->column_types[col] == UINT) {
        tmp = calloc(16, sizeof(char));
        if (!tmp)
            return NULL;
        sprintf(tmp, "%u", df_getuint(dataframe, row, col));
        return tmp;
    }
    if (dataframe->column_types[col] == FLOAT) {
        tmp = calloc(16, sizeof(char));
        if (!tmp)
            return NULL;
        sprintf(tmp, "%f", df_getfloat(dataframe, row, col));
        return tmp;
    }
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

int df_write_csv(dataframe_t *dataframe, const char *filename)
{
    FILE *file = fopen(filename, "w");
    char *line = NULL;

    if (!file)
        return 84;
    line = my_join(",", dataframe->column_names, dataframe->nb_columns);
    if (!line)
        return 84;
    fprintf(file, "%s\n", line);
    free(line);
    for (int i = 0; i < dataframe->nb_rows; i++) {
        line = my_df_join(",", dataframe, i);
        if (!line)
            return 84;
        fprintf(file, "%s\n", line);
        free(line);
    }
    return 0;
}

int main(int argc, char **argv)
{
    dataframe_t *df = df_read_csv("data.csv", NULL);

    if (!df) {
        fprintf(stderr, "Error reading file\n");
        return 84;
    }
    df_info(df);
    dataframe_shape_t *shape = df_shape(df);
    if (!shape) {
        free(df);
        return df_interr("Failed to alloc shape");
    }
    printf("Shape: %d rows, %d columns\n", shape->nb_rows, shape->nb_columns);
    df_write_csv(df, "data_copy.csv");
    free(shape);
    free(df);
    return 0;
}
