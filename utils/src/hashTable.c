#include "hashTable.h"
#include <stddef.h>
#include <stdlib.h>

#define INITIAL_CAPACITY_BUCKET_FRACTION 2
#define INITIAL_ITEMS_PER_BUCKET 3

typedef struct Bucket {
  size_t length;
  size_t capacity;
  void **items;
} Bucket;

typedef struct HashTable {
  size_t length;
  size_t capacity;
  size_t numBuckets;

  size_t sizeOfKey;
  size_t sizeOfValue;
  size_t (*hash_func)(const void *key);
  int (*compare_func)(const void *key1, const void *key2);

  Bucket buckets[];

} HashTable;

HashTable *newHashTable(size_t capacity, size_t (*hash_func)(const void *key),
                        int (*compare_func)(const void *key1,
                                            const void *key2)) {

  int numBuckets = (capacity / INITIAL_CAPACITY_BUCKET_FRACTION);
  size_t memory = numBuckets * sizeof(Bucket) +
                  INITIAL_ITEMS_PER_BUCKET * numBuckets * sizeof(void *);

  HashTable *hashTable = malloc(sizeof(HashTable) + memory);
  if (!hashTable) {
    return NULL;
  }

  hashTable->length = 0;
  hashTable->capacity = capacity;
  hashTable->numBuckets = numBuckets;
  hashTable->hash_func = hash_func;
  hashTable->compare_func = compare_func;

  return hashTable;
}

int htInsert(HashTable *ht, void *key, void *value) {
  int hash = ht->hash_func(key);

  int bucketIndex = hash % ht->numBuckets;

  int itemIndex = ht->buckets[bucketIndex].length;
  if (itemIndex < ht->buckets[bucketIndex].capacity) {
    ht->buckets[bucketIndex].items[itemIndex] = value;
  } else {
    // Increase memory
    // TODO: implement this
  }
}

void *htGet(HashTable *ht, const void *key) {}

int htRemove(HashTable *ht, const void *key) {}

void htDestroy(HashTable *ht) {}

void htDestroyWithValues(HashTable *ht) {}

// --- Private Function Prototypes ---

int increaseCapacity(HashTable *ht) {
  // TODO: implement this
}
