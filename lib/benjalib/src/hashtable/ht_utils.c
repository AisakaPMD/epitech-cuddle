/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Project's misc utils and
** hashing function
** Authors:
** Amélie Ambleton--Guth and Corentin Bruneau
** Feb 2026
*/

#include "benjalib.h"

int hash(char *key, int len)
{
    uint32_t hash_value = 2166136261u;

    if (!key)
        return -1;
    for (int i = 0; key[i] != '\0' && i < len; i++) {
        hash_value = ((hash_value << 5) + hash_value) + (uint8_t)key[i];
        hash_value ^= (hash_value >> 13);
        hash_value ^= (hash_value << 7);
        hash_value *= PREMFNV;
        if (i != 0)
            hash_value ^= (key[i] << i);
    }
    hash_value ^= hash_value >> 16;
    hash_value *= 0x85ebca6b;
    hash_value ^= hash_value >> 13;
    hash_value *= PREMFNV;
    return (int)(hash_value & 0x7FFFFFFF);
}

int mt_validate_hash(hashtable_t *ht, char *key)
{
    int hash;

    if (!ht || !ht->hash || !key)
        return -1;
    hash = ht->hash(key, ht->len);
    if (hash >= 0)
        return hash;
    my_dprintf(2, "ERR: key %s has hash %d\n", key, hash);
    return -1;
}

hashtable_pair_t *ht_get_pair(hashtable_t *ht, char *key)
{
    hashtable_pair_t *pair;
    list_t *elt;
    int hash = mt_validate_hash(ht, key);

    if (!ht || hash < 0)
        return NULL;
    elt = ht->buckets[hash % ht->len];
    while (elt) {
        pair = elt->data;
        elt = elt->next;
        if (hash == pair->key)
            return pair;
    }
    return NULL;
}
