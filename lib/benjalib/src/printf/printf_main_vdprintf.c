/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Printf Entry Point
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"

int my_vdprintf(int fd, char const *format, va_list arg)
{
    printf_context_t ctx = {0, 1, fd, .buffer = NULL, .written = 0};
    size_t written = 0;
    int skip = 0;

    if (format == NULL)
        return -1;
    va_copy(ctx.args, arg);
    for (int i = 0; format[i]; i++) {
        skip = printf_loop_callback(format + i, &written, &ctx);
        if (skip < 0) {
            va_end(ctx.args);
            return -1;
        }
        i += skip;
    }
    va_end(ctx.args);
    return (int) written;
}
