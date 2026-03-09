/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Hashtable displaying function
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include "benjalib.h"

static void ht_print_bucket(list_t *bucket)
{
    hashtable_pair_t *pair;

    while (bucket) {
        pair = bucket->data;
        bucket = bucket->next;
        my_printf("> %d - %s\n", pair->key, pair->value);
    }
}

void ht_print(hashtable_t *ht)
{
    if (!ht || !ht->buckets)
        return;
    for (int i = 0; i < ht->len; i++) {
        my_printf("[%d]:\n", i);
        ht_print_bucket(ht->buckets[i]);
    }
}
