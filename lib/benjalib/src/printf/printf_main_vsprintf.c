/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Translation unit containing vsprintf logic
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"

int my_vsprintf(char *buf, char const *format, va_list arg)
{
    printf_context_t ctx = {.outputs = 1, .fd = -1, .limit = -1};
    size_t written = 0;
    int skip = 0;

    if (format == NULL || buf == NULL)
        return -1;
    ctx.buffer = printf_my_strbuf_init();
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
    printf_my_strbuf_get(buf, ctx.buffer);
    printf_my_strbuf_free(ctx.buffer);
    return (int) written;
}
