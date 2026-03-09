/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Math Utils
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include "benjalib.h"

int my_compute_power_rec(int nb, int p)
{
    int res;

    if (p == 0)
        return 1;
    if (nb == 0 || p < 0)
        return 0;
    res = my_compute_power_rec(nb, p - 1);
    if (((long) res * (long) nb) > (long) INT_MAX)
        return 0;
    if (((long) res * (long) nb) < (long) INT_MIN)
        return 0;
    return res * nb;
}

static int get_root(int a, int b)
{
    if (b * b < a)
        return get_root(a, b + 1);
    return b;
}

int my_compute_square_root(int nb)
{
    int sr;

    if (nb < 1)
        return 0;
    sr = get_root(nb, 1);
    if ((sr * sr) != nb)
        return 0;
    return sr;
}

static int isprime(int a, int b)
{
    if ((b * b) > a)
        return 1;
    if (a % b == 0)
        return 0;
    return isprime(a, b + 1);
}

int my_is_prime(int nb)
{
    if (nb < 2)
        return 0;
    return isprime(nb, 2);
}

int my_find_prime_sup(int nb)
{
    if (nb < 2)
        return 2;
    while (!my_is_prime(nb)) {
        nb++;
    }
    return nb;
}

int my_isneg(int n)
{
    my_putchar(n < 0 ? 'N' : 'P');
    my_putchar('\n');
    return 0;
}
