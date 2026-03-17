/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** Header
*/

#ifndef BSCUDDLE_H
    #define BSCUDDLE_H

    #define DF_TRUE "true"
    #define DF_FALSE "false"

    #define DF_TYPE_ISNUM(type) (type == INT || type == UINT || type == FLOAT)
    #define DF_COL_ISNUM(df, col) (DF_TYPE_ISNUM(df->column_types[col]))

    #include <stdbool.h>

// One-line macros to avoid heavy function calls when unnecessary
    #define DF_ISINT(x) (strchr(x, '.') == NULL)
    #define DF_GET(frame, y, x, type) (*((type *) frame->data[y][x]))


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
void *apply_func(void *value);
void *apply_f(void *value);
void *agg_func(void **values, int nb_values);
void *str_to_nb(void *data, column_type_t before,
    column_type_t downcast, int *end);



// Logging
void *df_err(char *msg, ...);
int df_interr(char *msg, ...);

// Memory Utils
void my_memset(void *elt, int c, size_t n);
void *my_calloc(size_t nmemb, size_t size);
void safe_free(void *ptr);

// PHP's explode function reimplementation
char **my_explode(char const *str, char const *separator);
void free_str_arr(char **str_arr);
void print_str_arr(char **str_arr);

void df_disp(dataframe_t *frame);

dataframe_t *df_read_csv(const char *filename, const char *separator);
int df_write_csv(dataframe_t *dataframe, const char *filename);
dataframe_t *df_head(dataframe_t *dataframe, int nb_rows);
dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows);
dataframe_shape_t df_shape(dataframe_t *dataframe);
void df_info(dataframe_t *dataframe);
void df_describe(dataframe_t *dataframe);
dataframe_t *df_filter(dataframe_t *dataframe, const char *column,
    bool (*filter_func)(void *value));
dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *value1, void *value2));
dataframe_t *df_groupby(dataframe_t *dataframe, const char *aggregate_by,
    const char **to_aggregate, void *(*agg_func)(void **values, int nb_values));
dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *value));
dataframe_t *df_to_type(dataframe_t *dataframe, const char *column,
    column_type_t downcast);
void *df_get_value(dataframe_t *dataframe, int row, const char *column);
void **df_get_values(dataframe_t *dataframe, const char *column);
void **df_get_unique_values(dataframe_t *dataframe, const char *column);
void df_free(dataframe_t *dataframe);


#endif
