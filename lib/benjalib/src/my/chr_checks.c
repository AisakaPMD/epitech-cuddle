/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** MyLib Char Checks
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include "benjalib.h"

int my_isalpha(char c)
{
    return my_isupper(c) || my_islower(c);
}

int my_isnum(char c)
{
    return c >= '0' && c <= '9';
}

int my_islower(char c)
{
    return c >= 'a' && c <= 'z';
}

int my_isupper(char c)
{
    return c >= 'A' && c <= 'Z';
}

int my_isprintable(char c)
{
    return (c >= ' ' && c <= '~');
}
