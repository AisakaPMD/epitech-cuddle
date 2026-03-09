/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Translation unit for m conversion specifier
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include <errno.h>
#include <string.h>

#include "printf_internals.h"

int printf_merror(printf_render_params_t *params,
    printf_context_t *ctx)
{
    return printf_my_putstr(MYPRINTF_ERR_STR, ctx);
}
