/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Remove an element from the hashtable
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include <stdlib.h>

#include "benjalib.h"

int ht_del(hashtable_t *ht, char *key)
{
    hashtable_pair_t *pair;
    list_t **elt;
    int hash = mt_validate_hash(ht, key);
    int clamped_hash;

    if (hash < 0)
        return 84;
    clamped_hash = hash % ht->len;
    elt = &ht->buckets[clamped_hash];
    while (elt && *elt) {
        pair = (*elt)->data;
        if (pair->key == hash) {
            ll_shift(elt);
            free(pair);
            return 0;
        }
        elt = &(*elt)->next;
    }
    return 84;
}
