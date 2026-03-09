/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Translation unit handling strings and characters
** Authors:
** Amélie Ambleton--Guth and Benjamin Hess
** Feb 2026
*/

#include "printf_internals.h"

/*
int printf_my_strlen(char const *str)
{
    int i = 0;

    for (; str[i] != 0; i++);
    return i;
}

int printf_my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    for (; s1[i] != 0 && s2[i] != 0 && s2[i] == s1[i] && i < n - 1; i++);
    if (i == n)
        return 0;
    return s1[i] - s2[i];
}
*/

int printf_my_putstrn(char const *str, int size, printf_context_t *ctx)
{
    int i = 0;

    if (str == NULL)
        return -1;
    for (i = 0; str[i] && i < size; i++) {
        printf_my_putchar(str[i], ctx);
    }
    return i;
}

/*
int printf_my_char_isupper(char c)
{
    return c >= 'A' && c <= 'Z';
}
*/
