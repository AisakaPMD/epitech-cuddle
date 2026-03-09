/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Translation unit containing vprintf logic
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"

int my_vprintf(char const *format, va_list arg)
{
    return my_vdprintf(1, format, arg);
}
