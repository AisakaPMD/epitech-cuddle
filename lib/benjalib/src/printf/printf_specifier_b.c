/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Translation unit for b conversion specifier
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"

int printf_bin(printf_render_params_t *params, printf_context_t *ctx)
{
    int written = 0;

    if (params->flags & RF_ALTERNATE_FORM) {
        if (params->is_cap)
            printf_my_putstr("0B", ctx);
        else
            printf_my_putstr("0b", ctx);
        written += 2;
    }
    return printf_print_unsigned(printf_get_sized_uint(ctx->args,
            params->length_modifier), ctx, "01", params->precision) + written;
}
