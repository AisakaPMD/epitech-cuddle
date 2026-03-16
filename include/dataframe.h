/*
** EPITECH PROJECT, 2026
** bscuddle
** File description:
** Header
*/

#ifndef BSCUDDLE_H
#define BSCUDDLE_H

#define DF_TRUE "true"
#define DF_FALSE "false"

#define DF_COL_ISNUM(df, col) (df->column_types[col] == INT || \
    df->column_types[col] == UINT || df->column_types[col] == FLOAT)

typedef enum {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED
} column_type_t;

typedef struct {
    int nb_rows; // Number of rows in the dataframe
    int nb_columns; // Number of columns in the dataframe
    char **column_names; // Array of column names
    column_type_t *column_types; // Array of column types
    void ***data; // 2D array of data values
} dataframe_t;

typedef struct {
    int nb_columns;
    int nb_rows;
} dataframe_shape_t;

dataframe_t *data_dupe(dataframe_t *df);
dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *value));
void *apply_func(void *value);
void *apply_f(void *value);
dataframe_t *df_to_type(dataframe_t *dataframe, const char *column, column_type_t downcast);
void *str_to_nb(void *data, column_type_t before, column_type_t downcast, int *end);
dataframe_t *df_groupby(dataframe_t *dataframe, const char *aggregate_by, const char
    **to_aggregate, void *(*agg_func)(void **values, int nb_values));
void *agg_func(void **values, int nb_values);



#endif
