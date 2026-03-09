/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** String Utils
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include "benjalib.h"

static char my_lower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    return c;
}

static char my_upper(char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
    return c;
}

static char my_is_word(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
        || (c >= '0' && c <= '9'));
}

int my_strlen(char const *str)
{
    int i = 0;

    if (!str)
        return 0;
    for (; str[i] != 0; i++);
    return i;
}

char *my_strcapitalize(char *str)
{
    char last_is_sep = 1;

    if (!str)
        return NULL;
    for (int i = 0; str[i] != 0; i++) {
        if (last_is_sep) {
            str[i] = my_upper(str[i]);
        } else {
            str[i] = my_lower(str[i]);
        }
        last_is_sep = !my_is_word(str[i]);
    }
    return str;
}

static char assert_str_eq(char const *str, char const *other)
{
    int i = 0;

    for (; str[i] == other[i] && str[i] != 0; i++);
    return other[i] == 0 || str[i] == other[i];
}

char *my_strstr(char *str, char const *to_find)
{
    if (!to_find || !str)
        return NULL;
    if (*to_find == 0)
        return str;
    for (int i = 0; str[i] != 0; i++){
        if (assert_str_eq(str + i, to_find))
            return str + i;
    }
    return NULL;
}

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    if (!s1)
        return -1;
    if (!s2)
        return 1;
    for (; s1[i] != 0 && s2[i] != 0 && s2[i] == s1[i]; i++);
    return s1[i] - s2[i];
}

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    if (!s1)
        return -1;
    if (!s2)
        return 1;
    for (; s1[i] && s2[i] && s2[i] == s1[i]; i++)
        if (n >= 0 && i >= n)
            break;
    return s1[i] - s2[i];
}
