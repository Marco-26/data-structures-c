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

uint64_t FNV_1a(const char *text)
{
  uint64_t hash = 14695981039346656037ULL;
  uint64_t prime = 1099511628211ULL;
  size_t size = strlen(text);

  for (size_t i = 0; i < size; i++)
  {
    hash ^= (uint64_t)(unsigned char)*text++;
    hash *= prime;
  }

  return hash;
}

int main()
{
  HashTable *hashTable = hashTableInit();
  const char *text = "Test";
  uint64_t hashed = FNV_1a(text);
  int index = hashed % hashTable->capacity;
  printf("Hash: %llu %d\n", hashed, index);
}
