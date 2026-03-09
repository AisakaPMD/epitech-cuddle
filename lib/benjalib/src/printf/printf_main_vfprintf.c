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

#ifndef EPITECH_RESTRICTED

// NOT SUPPORTED ON LITE VERSION (Banned functions)
int my_vfprintf(FILE *stream, char const *format, va_list arg)
{
    return my_vdprintf(fileno(stream), format, arg);
}

#endif
