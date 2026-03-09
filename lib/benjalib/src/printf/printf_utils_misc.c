/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Misc utils
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"
#include "benjalib/my.h"
#include <unistd.h>
#include <limits.h>

int printf_my_putstr(char const *str, printf_context_t *ctx)
{
    int i;

    for (i = 0; str[i]; i++) {
        printf_my_putchar(str[i], ctx);
    }
    return i;
}

static int parse(char const *str, char neg)
{
    long int val = 0;

    for (int i = 0; str[i] != 0 && my_isnum(str[i]); i++) {
        if (val > (INT_MAX / 10 - (str[i] - '0')))
            return 0;
        val *= 10;
        val += str[i] - '0';
    }
    return neg ? (int) (-val) : (int) val;
}

int printf_my_getnbr(char const *str)
{
    int i;
    char isneg = 0;

    for (i = 0; str[i] != 0 && (str[i] == '-' || str[i] == '+'); i++) {
        if (str[i] == '-')
            isneg ^= 1;
    }
    return parse(str + i, isneg);
}

long int printf_my_get_unsigned_nbr(char const *str, int *skip, char allowZero)
{
    int i;
    char is_found = 0;
    unsigned int val = 0;

    for (i = 0; str[i] && my_isnum(str[i]) &&
        (allowZero || val > 0 || str[i] != '0'); i++) {
        is_found = 1;
        if (val > (UINT_MAX / 10 - (str[i] - '0')))
            return -42;
        val = val * 10 + (str[i] - '0');
    }
    *skip = i;
    if (is_found)
        return val;
    return -1;
}

static int my_putnbr_rec(long long nbr,
    char const *base, int baselen, printf_context_t *ctx)
{
    int written = 0;

    if (nbr >= baselen)
        written += my_putnbr_rec(nbr / baselen, base, baselen, ctx);
    written += printf_my_putchar(base[nbr % baselen], ctx);
    return written;
}

int printf_my_putnbr_base(long long nbr, char const *base,
    printf_context_t *ctx)
{
    int baselen = my_strlen(base);
    long long abs = nbr < 0 ? -nbr : nbr;
    int written = 0;

    if (baselen < 2)
        return 0;
    if (nbr < 0)
        written += printf_my_putchar('-', ctx);
    return my_putnbr_rec(abs, base, baselen, ctx) + written;
}

int printf_my_put_nbr(long long n, printf_context_t *ctx)
{
    return printf_my_putnbr_base(n, "0123456789", ctx);
}
