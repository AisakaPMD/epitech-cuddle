/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Translation unit for f conversion specifier
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"

int printf_float(printf_render_params_t *params,
    printf_context_t *ctx)
{
    double nb = va_arg(ctx->args, double);
    char neg = (char) (*(unsigned long long *) &nb >> 63);
    int precision = params->precision >= 0 ? params->precision : 6;
    double part_entiere;
    int written = 0;

    written += printf_write_sign_prefix(neg, params, ctx);
    if (printf_print_invalid_double(nb, params->is_cap, ctx, &written))
        return written;
    if (neg)
        nb *= -1;
    part_entiere = nb;
    written += printf_my_putdouble(nb, ctx, &part_entiere);
    written += printf_my_putchar('.', ctx);
    for (int i = 0; i < precision; i++) {
        nb = (nb - part_entiere) * 10.00001;
        part_entiere = (int) nb;
        written += printf_my_big_putnbr(part_entiere, ctx);
    }
    return written;
}
