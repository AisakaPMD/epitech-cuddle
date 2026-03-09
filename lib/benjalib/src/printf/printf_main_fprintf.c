/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Printf Entry Point
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"

int my_fprintf(FILE *stream, char const *format, ...)
{
    va_list arg;
    int written;

    va_start(arg, format);
    written = my_vfprintf(stream, format, arg);
    va_end(arg);
    return written;
}
