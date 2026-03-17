/*
** EPITECH PROJECT, 2026
** cuddle
** File description:
** Project's entry point
** Auto-Generated with Episetup by Amélie
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#include "dataframe.h"

void *df_err(char *msg, ...)
{
    va_list ap;

    va_start(ap, msg);
    fprintf(stderr, "cuddle: ");
    vfprintf(stderr, msg, ap);
    fprintf(stderr, "\n");
    return NULL;
}

int df_interr(char *msg, ...)
{
    va_list ap;

    va_start(ap, msg);
    fprintf(stderr, "cuddle: ");
    vfprintf(stderr, msg, ap);
    fprintf(stderr, "\n");
    return 84;
}
