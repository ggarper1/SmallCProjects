#include <stddef.h>

#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct HashTable {
  size_t length;
  size_t capacity;
} HashTable;

// --- Public Function Prototypes ---

/**
 * Creates a new hash table.
 * @param capacity Initial number of buckets.
 * @param hash_func Function to hash the keys.
 * @param compare_func Function to compare keys.
 * @return A pointer to the new HashTable_t, or NULL on failure.
 */
HashTable *newHashTable(size_t capacity,
                        size_t (*hash_func)(const void *key, size_t capacity),
                        int (*compare_func)(const void *key1,
                                            const void *key2));

/**
 * Inserts or updates a key-value pair in the hash table.
 * Pointers to the key and value are stored (caller manages memory).
 * @param ht The hash table.
 * @param key The key to insert.
 * @param value The value associated with the key.
 * @return 0 on success, -1 on failure.
 */
int htInsert(HashTable *ht, void *key, void *value);

/**
 * Retrieves the value associated with a key.
 * @param ht The hash table.
 * @param key The key to look up.
 * @return The value pointer, or NULL if the key is not found.
 */
void *htGet(HashTable *ht, const void *key);

/**
 * Removes a key-value pair from the hash table.
 * @param ht The hash table.
 * @param key The key to remove.
 * @return 0 on success (item removed), -1 if key not found.
 */
int htRemove(HashTable *ht, const void *key);

/**
 * Destroys the hash table and frees all allocated memory.
 * @param ht The hash table to destroy.
 */
void htDestroy(HashTable *ht);

/**
 * Destroys the hash table and along with all the keys and values in it.
 * @param ht The hash table to destroy.
 */
void htDestroyWithValues(HashTable *ht);

#endif
