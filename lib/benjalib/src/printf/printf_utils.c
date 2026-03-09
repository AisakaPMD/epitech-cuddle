/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Other utils for my printf
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include <math.h>

#include "printf_internals.h"

unsigned long long printf_get_sized_uint(va_list arg, int flagValue)
{
    switch (flagValue) {
        case 8:
            return (unsigned long long) va_arg(arg, long long int);
        default:
        case 4:
            return (unsigned int) va_arg(arg, int);
        case 2:
            return (unsigned short int) va_arg(arg, int) & 0xFFFF;
        case 1:
            return (unsigned char) va_arg(arg, int) & 0xFF;
        case 10:
            return va_arg(arg, intmax_t);
        case 11:
            return va_arg(arg, ssize_t);
        case 12:
            return va_arg(arg, ptrdiff_t);
    }
}

long long printf_get_sized_int(va_list arg, int flagValue)
{
    switch (flagValue) {
        case 8:
            return va_arg(arg, long long int);
        default:
        case 4:
            return va_arg(arg, int);
        case 2:
            return va_arg(arg, int) & 0xFFFF;
        case 1:
            return va_arg(arg, int) & 0xFF;
        case 10:
            return va_arg(arg, intmax_t);
        case 11:
            return va_arg(arg, ssize_t);
        case 12:
            return va_arg(arg, ptrdiff_t);
    }
}

ssize_t printf_my_putchar(int c, printf_context_t *ctx)
{
    if (!ctx->outputs)
        return 1;
    if (ctx->fd < 1 && ctx->buffer != NULL) {
        if (printf_my_strbuf_len(ctx->buffer) < (ctx->limit - 1)
            || ctx->limit < 0)
            return printf_printf_my_strbuf_write(ctx->buffer, c);
        return 0;
    }
    if (ctx->fd > 0 && ctx->buffer == NULL) {
        return write(ctx->fd, &c, 1);
    }
    return 0;
}
