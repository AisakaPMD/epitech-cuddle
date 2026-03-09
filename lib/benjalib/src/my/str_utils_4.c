/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** MyLib String Utils 3
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include "benjalib.h"

int my_show_word_array(char *const *tab)
{
    if (!tab)
        return 0;
    for (int i = 0; tab[i] != NULL; i++) {
        my_putstr(tab[i]);
        my_putchar('\n');
    }
    return 0;
}

char *my_strdup(char const *src)
{
    return my_strndup(src, -1);
}

char *my_strndup(char const *src, int nb)
{
    int buf_length;
    char *result;

    if (!src)
        return NULL;
    buf_length = my_strlen(src);
    if (nb >= 0 && nb < buf_length)
        buf_length = nb;
    result = malloc(sizeof(char) * (buf_length + 1));
    if (!result)
        return NULL;
    return my_strncpy(result, src, buf_length);
}

int my_fputs(int fd, char const *str)
{
    if (!str)
        return -1;
    return write(fd, str, my_strlen(str));
}
