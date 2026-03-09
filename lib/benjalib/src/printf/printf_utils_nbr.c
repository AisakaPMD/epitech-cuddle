/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Utils directed toward numbers handling
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"
#include "benjalib/my.h"
#include <limits.h>

static long long abs_mod(long long a, long long b)
{
    long long c = a % b;

    return c < 0 ? -c : c;
}

int printf_my_big_putnbr(long long nbr, printf_context_t *ctx)
{
    int written = 0;

    if (nbr < 0) {
        written += printf_my_putchar('-', ctx);
        written += printf_my_big_putnbr(-(nbr / 10), ctx);
    }
    if (nbr >= 10) {
        written += printf_my_big_putnbr(nbr / 10, ctx);
    }
    written += printf_my_putchar(abs_mod(nbr, 10) + '0', ctx);
    return written;
}

int printf_my_big_putnbr_base(unsigned long long nbr, char const *base,
    printf_context_t *ctx)
{
    int written = 0;
    int base_size = my_strlen(base);

    if (nbr >= base_size) {
        written += printf_my_big_putnbr_base(nbr / base_size, base, ctx);
    }
    written += printf_my_putchar(base[abs_mod(nbr, base_size)], ctx);
    return written;
}

unsigned long long printf_my_unsigned_compute_power_it(
    unsigned long long nb, unsigned int power)
{
    unsigned long long result = 1;

    if (nb == 0)
        return power == 0 ? 1 : 0;
    while (power > 0) {
        if (result > ULLONG_MAX / nb)
            return 0;
        result *= nb;
        power--;
    }
    return result;
}

int printf_print_unsigned(unsigned long long abs, printf_context_t *ctx,
    char const *base, int precision)
{
    size_t written = 0;
    unsigned int power = 0;
    int base_len = my_strlen(base);

    if (precision < 0)
        precision = 1;
    if (precision == 0 && abs == 0)
        return 0;
    for (; printf_my_unsigned_compute_power_it(base_len, power) <= abs;
        power++);
    if (power < precision)
        power = precision;
    for (; power > 0; power--) {
        written += printf_my_putchar(base[
                (int) (abs / printf_my_unsigned_compute_power_it(
                        base_len, power - 1) % base_len)], ctx);
    }
    return (int) written;
}

ssize_t printf_write_sign_prefix(char isneg,
    printf_render_params_t *params, printf_context_t *ctx)
{
    ssize_t written = 0;

    if (isneg || (params->flags & RF_SIGN)) {
        written += printf_my_putchar(isneg ? '-' : '+', ctx);
    } else if (params->flags & RF_SPACE) {
        written += printf_my_putchar(' ', ctx);
    }
    for (int i = 0; i < params->zeroes_padding; i++) {
        written += printf_my_putchar('0', ctx);
    }
    return written;
}
