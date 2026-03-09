/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** MyLib Miscelleanous Utils
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include "benjalib.h"
#include <unistd.h>
#include <limits.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

static int print_that(int n)
{
    if (n >= 10) {
        print_that(n / 10);
    }
    my_putchar('0' + n % 10);
    return 0;
}

int my_put_nbr(int n)
{
    if (n < 0) {
        my_putchar('-');
        if (n == -2147483648) {
            my_putchar('2');
            n = -147483648;
        }
        print_that(-n);
    } else {
        print_that(n);
    }
    return 0;
}

int my_putstr(char const *str)
{
    int i;

    if (!str)
        return 0;
    for (i = 0; str[i]; i++) {
        my_putchar(str[i]);
    }
    return i;
}

static char is_sign(char c)
{
    return c == '-' || c == '+';
}

static int parse(char const *str, char neg)
{
    long int val = 0;

    if (!str)
        return 0;
    for (int i = 0; str[i] != 0 && my_isnum(str[i]); i++) {
        val *= 10;
        val += str[i] - '0';
        if (val - 1 > INT_MAX)
            return 0;
    }
    val = neg ? -val : val;
    if (val > INT_MAX || val < INT_MIN)
        return 0;
    return val;
}

int my_getnbr(char const *str)
{
    int i;
    char isneg = 0;

    if (!str)
        return 0;
    for (i = 0; str[i] != 0 && is_sign(str[i]); i++) {
        if (str[i] == '-')
            isneg ^= 1;
    }
    return parse(str + i, isneg);
}
