/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Fetches an element from the hashtable
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include "benjalib.h"

void *ht_get(hashtable_t *ht, char *key)
{
    hashtable_pair_t *pair = ht_get_pair(ht, key);

    if (pair)
        return pair->value;
    return NULL;
}

char ht_has(hashtable_t *ht, char *key)
{
    return (char) !!ht_get_pair(ht, key);
}
