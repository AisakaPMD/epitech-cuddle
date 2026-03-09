/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Translation unit for d and i conversion specifier
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"

int printf_decimal(printf_render_params_t *params,
    printf_context_t *ctx)
{
    long long nbr = printf_get_sized_int(ctx->args, params->length_modifier);
    size_t written = 0;
    unsigned long long abs = nbr < 0 ? -nbr : nbr;
    unsigned int power = 0;
    int precision = params->precision < 0 ? 1 : params->precision;

    if (precision == 0 && nbr == 0)
        return 0;
    written += printf_write_sign_prefix(nbr < 0, params, ctx);
    for (; printf_my_unsigned_compute_power_it(10, power) <= abs; power++);
    if (power < precision)
        power = precision;
    for (; power > 0; power--) {
        printf_my_putchar((int) (abs / printf_my_unsigned_compute_power_it(
                    10, power - 1) % 10) + '0', ctx);
        written++;
    }
    return (int) written;
}
