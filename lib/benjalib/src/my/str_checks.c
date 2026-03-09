/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** MyLib String Checks
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include "benjalib.h"

int my_str_isalpha(char const *str)
{
    if (!str)
        return 0;
    for (int i = 0; str[i] != 0; i++) {
        if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' &&
                    str[i] <= 'z')))
            return 0;
    }
    return 1;
}

int my_str_isnum(char const *str)
{
    if (!str)
        return 0;
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int my_str_islower(char const *str)
{
    if (!str)
        return 0;
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] < 'a' || str[i] > 'z')
            return 0;
    }
    return 1;
}

int my_str_isupper(char const *str)
{
    if (!str)
        return 0;
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] < 'A' || str[i] > 'Z')
            return 0;
    }
    return 1;
}

int my_str_isprintable(char const *str)
{
    if (!str)
        return 0;
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] < ' ' || str[i] > '~')
            return 0;
    }
    return 1;
}
