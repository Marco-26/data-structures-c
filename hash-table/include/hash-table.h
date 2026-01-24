// IMPLEMENTING A SIMPLE HASH TABLE IN C, string to string MAPPING
// FULL OWNERSHIP OF VALUES IN HASHTABLE, so if a user passes a pointer, we must copy it, because the user might free that up and then the hashtable would have a NULL
// Starting of with 128 buckets

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define BUCKET_LENGTH 16

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
Entry *entryInit(const char *k, const char *v, Entry *child);
// Design choice: replace on existing key
int hashTablePut(HashTable *hashTable, const char *k, const char *v);
const char *hashTableGet(HashTable *hashTable, const char *k);
int hashTableRemove(HashTable *hashTable, const char *k);
void hashTableDestroy(HashTable *hashTable);
// our hash function, based on Fowler–Noll–Vo
uint64_t FNV_1a(const char *text);

#endif