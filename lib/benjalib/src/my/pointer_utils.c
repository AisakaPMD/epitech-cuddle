/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** MyLib Pointer Utils
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include "benjalib.h"

void my_swap(int *a, int *b)
{
    int c;

    if (!a || !b)
        return;
    c = *a;
    *a = *b;
    *b = c;
}

void my_sort_int_array(int *array, int size)
{
    int *lowest = array;

    if (!lowest || size < 2)
        return;
    for (int i = 1; i < size; i++) {
        if (array[i] < *lowest)
            lowest = array + i;
    }
    my_swap(lowest, array);
    my_sort_int_array(array + 1, size - 1);
}
