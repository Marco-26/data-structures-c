// IMPLEMENTING A SIMPLE HASH TABLE IN C, string to string MAPPING
// FULL OWNERSHIP OF VALUES IN HASHTABLE, so if a user passes a pointer, we must copy it, because the user might free that up and then the hashtable would have a NULL
// Starting of with 128 buckets

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>
#include <stdlib.h>

#define BUCKET_LENGTH 128

typedef struct Entry
{
  char *key;
  char *value;
  struct Entry *next;
} Entry;

typedef struct
{
  Entry **buckets;
  size_t size;     // number of stored entries
  size_t capacity; // number of buckets
} HashTable;

HashTable *hashTableInit();
int hashTablePut(HashTable *hashTable, const char *k, const char *v); // replace on existing value
const char *hashTableGet(HashTable *hashTable, const char *k);
int hashTableRemove(HashTable *hashTable, const char *k);
void hashTableDestroy(HashTable *hashTable);

#endif