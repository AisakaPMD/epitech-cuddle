/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Translation unit for n conversion specifier
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"

int printf_written(printf_render_params_t *params,
    printf_context_t *ctx)
{
    void *ptr = va_arg(ctx->args, void *);

    if (params->length_modifier == 8)
        *(long long *) ptr = (long long) params->written;
    if (params->length_modifier == 2)
        *(short *) ptr = (short) params->written;
    if (params->length_modifier == 1)
        *(char *) ptr = (char) params->written;
    if (params->length_modifier == 10)
        *(intmax_t *) ptr = (intmax_t) params->written;
    if (params->length_modifier == 11)
        *(size_t *) ptr = params->written;
    if (params->length_modifier == 12)
        *(ptrdiff_t *) ptr = (ptrdiff_t) params->written;
    if (params->length_modifier == 4 || params->length_modifier < 1
        || params->length_modifier == 10)
        *(int *) ptr = (int) params->written;
    return 0;
}
