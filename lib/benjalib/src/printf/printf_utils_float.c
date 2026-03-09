/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Float utilities file
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include <math.h>

#include "printf_internals.h"

int printf_my_putdouble(double d, printf_context_t *ctx, double *part_entiere)
{
    double exp = 1;
    int written = 0;
    int a;

    for (; exp <= d / 10.0; exp *= 10.0);
    for (double div = exp; div >= 1.0; div /= 10.0) {
        a = (int) (d / div);
        written += printf_my_put_nbr(a, ctx);
        d -= (double) a * div;
    }
    *part_entiere -= d;
    return written;
}

double printf_my_modf(double number, double mod)
{
    double exp = 1;

    for (; exp <= number / mod; exp *= mod);
    for (double div = exp; div > 1.0; div /= mod) {
        number -= (int) (number / div) * div;
    }
    return number;
}

int printf_print_invalid_double
(double d, char cap, printf_context_t *ctx, int *written)
{
    if (d == INFINITY || d == (-INFINITY)) {
        *written += printf_my_putstr(cap ? "INF" : "inf", ctx);
        return 1;
    }
    if (d != d) {
        *written += printf_my_putstr(cap ? "NAN" : "nan", ctx);
        return 1;
    }
    return 0;
}
