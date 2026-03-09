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

char *my_strlowcase(char *str)
{
    if (!str)
        return NULL;
    for (int i = 0; str[i] != 0; i++)
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += ('a' - 'A');
    return str;
}

char *my_strupcase(char *str)
{
    if (!str)
        return NULL;
    for (int i = 0; str[i] != 0; i++)
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] += ('A' - 'a');
    return str;
}

char *my_strcpy(char *dest, char const *src)
{
    return my_strncpy(dest, src, -1);
}

char *my_strncpy(char *dest, char const *src, int n)
{
    int j = 0;

    if (!dest || !src)
        return NULL;
    while (src[j]) {
        if (n >= 0 && j >= n)
            break;
        dest[j] = src[j];
        j++;
    }
    dest[j] = '\0';
    return dest;
}

char *my_revstr(char *str)
{
    int strlen = my_strlen(str);
    char buf[strlen];

    for (int i = 0; i < strlen; i++)
        buf[strlen - i - 1] = str[i];
    for (int i = 0; i < strlen; i++)
        str[i] = buf[i];
    str[strlen] = 0;
    return str;
}
