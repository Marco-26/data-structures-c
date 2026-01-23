// IMPLEMENTING A SIMPLE HASH TABLE IN C, string to string MAPPING
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>
#include <stdlib.h>

typedef struct Entry
{
  char *key;
  char *value;
  struct Entry *next;
} Entry;

typedef struct
{
  Entry **buckets;
  size_t size;
  size_t capacity;
} HashTable;

HashTable *hashTableInit();
int hashTablePut(HashTable *hashTable, const char *k, const char *v);
const char *hashTableGet(HashTable *hashTable, const char *k);
int hashTableRemove(HashTable *hashTable, const char *k);
void hashTableDestroy(HashTable *hashTable);

#endif