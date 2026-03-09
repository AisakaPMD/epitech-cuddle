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

char *my_strcat(char *dest, char const *src)
{
    return my_strncat(dest, src, -1);
}

char *my_strncat(char *dest, char const *src, int nb)
{
    if (!dest || !src)
        return NULL;
    my_strncpy(dest + my_strlen(dest), src, nb);
    return dest;
}

int my_showstr(char const *str)
{
    for (int i = 0; str[i]; i++) {
        if (my_isprintable(str[i]))
            my_putchar(str[i]);
        else {
            my_putchar('\\');
            my_putchar(str[i] / 16 + '0');
            my_putchar(("0123456789abcdef")[str[i] % 16]);
        }
    }
    return 0;
}

static int put_hex(int nbr, int n)
{
    if (n > 1)
        put_hex(nbr / 16, n - 1);
    my_putchar(("0123456789abcdef")[nbr % 16]);
    return 0;
}

static void write_hex(int nbr, int places)
{
    if (nbr < 0)
        return;
    put_hex(nbr, places);
}

static void showmem_line(char const *str, int line, int size)
{
    int remaining = size - line * 16;

    for (int i = 0; i < 16; i++) {
        if (i < remaining)
            write_hex(str[line * 16 + i], 2);
        else
            my_putstr("  ");
        if (i % 2)
            my_putchar(' ');
    }
    for (int i = 0; i < 16; i++) {
        if (i < remaining && my_isprintable(str[line * 16 + i]))
            my_putchar(str[line * 16 + i]);
        else
            my_putchar('.');
    }
    my_putchar('\n');
}

int my_showmem(char const *str, int size)
{
    for (int line = 0; line < (size - 1) / 16 + 1; line++) {
        write_hex(line * 16, 8);
        my_putstr(": ");
        showmem_line(str, line, size);
    }
    return 0;
}
