/*
** EPITECH PROJECT, 2026
** Benjalib
** File description:
** Include file dedicated to the hashtable part
** of the libhashtable
** Authors:
** Amélie Ambleton--Guth and Corentin Bruneau
** Feb 2026
*/

#ifndef HASHTABLE_H
    #define HASHTABLE_H

    #include "system_includes.h"
    #include "linked_list.h"

/**
 * Represents a hashtable.
 */
typedef struct hashtable_s {
    int (*hash)(char *, int);
    int len;
    list_t **buckets;
} hashtable_t;

/**
 * Represents a key/value pair
 * in a hashtable.
 */
typedef struct hashtable_pair_s {
    int key;
    void *value;
} hashtable_pair_t;

// Hash function
/**
 * Transforms the given <code>key</code> into a
 * pseudo-random, unique, consistent, and imprevisible
 * int representing the value. This function is
 * made such as similar inputs give radically different
 * outputs, but giving the same input twice gives
 * the same output.
 * @param key the value to hash
 * @param len length of the resulting hashtable. Unused.
 * @return the resulting hash, or -1 in case of error
 */
int hash(char *key, int len);

// Create & destroy table
/**
 * Creates a new hashtable of <code>len</code>
 * slots, using the <code>hash</code> hashing function
 * @param hash hashing function to use
 * @param len length of the map
 * @return the new hashmap in case of success, <code>NULL</code>otherwise
 */
hashtable_t *new_hashtable(int (*hash)(char *, int), int len);

/**
 * Deletes the hashtable <code>ht</code>,
 * freeing all of its slots besides the actual
 * stored value.
 * @param ht hashtable to be deleted
 */
void delete_hashtable(hashtable_t *ht);

/**
 * Inserts <code>value</code> into hashtable
 * <code>ht</code> at <code>key</code>.
 * @param ht the hashtable
 * @param key the key associated with the value
 * @param value the value to store
 * @return 0 if success, 84 otherwise
 */
int ht_put(hashtable_t *ht, char *key, void *value);

/**
 * Removes the element from hashtable <code>ht</code>
 * associated with the given <code>key</code>
 * @param ht the hashtable
 * @param key the key to delete
 * @return 0 if success, 84 otherwise
 */
int ht_del(hashtable_t *ht, char *key);

/**
 * Fetches the value associated with the <code>key</code>
 * from the hashtable <code>ht</code>.
 * @param ht the hashtable
 * @param key key to retrieve
 * @return the associated value if found, <code>NULL</code> otherwise
 */
void *ht_get(hashtable_t *ht, char *key);

/**
 * Displays the content of the hashtable <code>ht</code>
 * @param ht the hashtable to print
 */
void ht_print(hashtable_t *ht);

// Hashtable misc utils
int mt_validate_hash(hashtable_t *ht, char *key);
hashtable_pair_t *ht_get_pair(hashtable_t *ht, char *key);

#endif /* HASHTABLE_H */
