#include "../include/hash-table.h"
#include <stdio.h>
#include <stdlib.h>

HashTable *hashTableInit()
{
  HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
  if (hashTable == NULL)
  {
    return NULL;
  }

  hashTable->capacity = BUCKET_LENGTH;

  Entry **buckets = (Entry **)calloc(hashTable->capacity, sizeof(Entry *));
  if (buckets == NULL)
  {
    free(hashTable);
    return NULL;
  }

  hashTable->buckets = buckets;
  hashTable->size = 0;
  return hashTable;
}