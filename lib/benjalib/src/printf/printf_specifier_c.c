/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Translation unit for c conversion specifier
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"

int printf_char(printf_render_params_t *params,
    printf_context_t *ctx)
{
    printf_my_putchar(va_arg(ctx->args, int), ctx);
    return 1;
}
