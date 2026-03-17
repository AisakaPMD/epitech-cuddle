/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** MyLib Str To Word Array
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dataframe.h"

static int is_word(char c, char const *separator)
{
    for (; separator[0]; separator++)
        if (separator[0] == c)
            return 0;
    return 1;
}

static int wordlen(char const *begin, char const *separator)
{
    int len = 0;

    for (; begin[len] && is_word(begin[len], separator); len++);
    return len;
}

static int count_words(char const *str, char const *separator)
{
    int nb_words = strlen(str) > 0;

    for (int i = 0; str[i]; i++) {
        nb_words += !is_word(str[i], separator);
    }
    return nb_words;
}

char **my_explode(char const *str, char const *separator)
{
    int word_len = 0;
    int cur_word = 0;
    int words = count_words(str, separator);
    char **array = malloc(sizeof(char *) * (words + 1));

    for (int i = 0; str[i]; i++) {
        if (is_word(str[i], separator)) {
            word_len = wordlen(str + i, separator);
            array[cur_word] = strndup(str + i, word_len);
            cur_word++;
            i += word_len - 1;
        }
    }
    if (!is_word(str[strlen(str) - 1], separator))
        array[words - 1] = strdup("");
    array[words] = NULL;
    return array;
}

void free_str_arr(char **str_arr)
{
    for (int i = 0; str_arr[i]; i++) {
        free(str_arr[i]);
    }
    free(str_arr);
}

void print_str_arr(char **str_arr)
{
    printf("=== BEGIN STR ARR DUMP ===\n");
    for (int i = 0; str_arr[i]; i++) {
        printf("%s\n", str_arr[i]);
    }
    printf("=== END STR ARR DUMP ===\n");
}
