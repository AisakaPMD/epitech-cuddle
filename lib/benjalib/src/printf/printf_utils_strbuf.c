/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** String buffer utils for sprintf and snprintf
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"

printf_string_buffer_t *printf_my_strbuf_init(void)
{
    printf_string_buffer_t *buf = malloc(sizeof(printf_string_buffer_t));

    buf->pos = 0;
    buf->next = NULL;
    return buf;
}

ssize_t printf_printf_my_strbuf_write(printf_string_buffer_t *buf, int c)
{
    if (buf->pos < STRBUF_SIZE) {
        buf->str[buf->pos] = c;
        buf->pos++;
        return 1;
    }
    buf->next = printf_my_strbuf_init();
    if (buf->next == NULL)
        return 0;
    return printf_printf_my_strbuf_write(buf->next, c);
}

void printf_my_strbuf_free(printf_string_buffer_t *buf)
{
    if (buf->next != NULL)
        printf_my_strbuf_free(buf->next);
    free(buf);
}

size_t printf_my_strbuf_len(printf_string_buffer_t *buf)
{
    if (buf->next != NULL)
        return printf_my_strbuf_len(buf->next) + buf->pos;
    return buf->pos;
}

static void my_strbuf_read(char *dst, printf_string_buffer_t *strbuf,
    size_t pos)
{
    for (size_t i = 0; i < strbuf->pos; i++) {
        dst[i + pos] = strbuf->str[i];
    }
    if (strbuf->next != NULL)
        my_strbuf_read(dst, strbuf->next, pos + strbuf->pos);
    else
        dst[pos + strbuf->pos] = 0;
}

void printf_my_strbuf_get(char *dst, printf_string_buffer_t *strbuf)
{
    my_strbuf_read(dst, strbuf, 0);
}
