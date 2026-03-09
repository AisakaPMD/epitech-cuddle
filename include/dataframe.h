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

#endif
