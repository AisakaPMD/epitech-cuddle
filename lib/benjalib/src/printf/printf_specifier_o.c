/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Translation unit for o conversion specifier
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"

int printf_octal(printf_render_params_t *params,
    printf_context_t *ctx)
{
    int written = 0;
    int nbrlen = 1;
    unsigned long long nbr = printf_get_sized_uint(ctx->args,
        params->length_modifier);

    for (unsigned long long ll = nbr; ll > 0; ll /= 10)
        nbrlen++;
    if (params->flags & RF_ALTERNATE_FORM &&
        (nbrlen > params->precision || params->precision < 0)) {
        printf_my_putstr("0", ctx);
        written += 1;
    }
    return printf_print_unsigned(nbr,
        ctx, "01234567", params->precision) + written;
}
