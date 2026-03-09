/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Project's hashtable creation and destroying functions
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include <stdlib.h>

#include "benjalib.h"

hashtable_t *new_hashtable(int (*hash)(char *, int), int len)
{
    hashtable_t *hashtable;

    if (len <= 0 || !hash)
        return NULL;
    hashtable = malloc(sizeof(hashtable_t));
    if (!hashtable)
        return NULL;
    hashtable->hash = hash;
    hashtable->len = len;
    hashtable->buckets = my_calloc(len, sizeof(list_t *));
    if (hashtable->buckets == NULL) {
        free(hashtable);
        return NULL;
    }
    return hashtable;
}

static void clear_bucket(list_t **bucket)
{
    hashtable_pair_t *tmp;

    while (bucket && *bucket) {
        tmp = ll_shift(bucket);
        if (tmp)
            free(tmp);
    }
}

void delete_hashtable(hashtable_t *ht)
{
    if (!ht)
        return;
    if (ht->buckets) {
        for (int i = 0; i < ht->len; i++) {
            clear_bucket(&ht->buckets[i]);
            ht->buckets[i] = NULL;
        }
        free(ht->buckets);
    }
    free(ht);
}
