/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Adding elements to hashtable
** Author:
** Amélie Ambleton--Guth
** Feb 2026
*/

#include "benjalib.h"

int ht_put(hashtable_t *ht, char *key, void *value)
{
    hashtable_pair_t *pair = ht_get_pair(ht, key);
    int hash = mt_validate_hash(ht, key);

    if (hash < 0 || !value)
        return 84;
    if (pair == NULL) {
        pair = my_calloc(1, sizeof(hashtable_pair_t));
        if (!pair)
            return 84;
        pair->key = hash;
        pair->value = value;
        return ll_unshift(&ht->buckets[hash % ht->len], pair);
    }
    pair->value = value;
    return 0;
}
