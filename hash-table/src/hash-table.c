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

Entry *entryInit(const char *k, const char *v, Entry *child)
{
  if (k == NULL || v == NULL)
  {
    return NULL;
  }

  Entry *newEntry = (Entry *)malloc(sizeof(Entry));
  if (newEntry == NULL)
  {
    return NULL;
  }

  char *key = malloc(strlen(k) + 1);
  char *value = malloc(strlen(v) + 1);

  if (key == NULL || value == NULL)
  {
    if (key != NULL)
    {
      free(key);
    }
    free(newEntry);
    return NULL;
  }

  strcpy(key, k);
  strcpy(value, v);

  newEntry->key = key;
  newEntry->value = value;
  newEntry->next = child;
  return newEntry;
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

int hashTablePut(HashTable *hashTable, const char *k, const char *v)
{
  // 1. compute the hash for key
  // 2. get the index for the hashed value
  uint64_t hashed = FNV_1a(k);
  int index = hashed % hashTable->capacity;

  // 3. If index already has values, create a new head of linked list and add the existing one as "child"
  if (hashTable->buckets[index]->value)
  {
  }
  // 4. If not just create an head
  return 0;
}

int main()
{
  HashTable *hashTable = hashTableInit();
  const char *text = "Test";
  uint64_t hashed = FNV_1a(text);
  int index = hashed % hashTable->capacity;
  printf("Hash: %llu %d\n", hashed, index);
  Entry *entry = entryInit("PATH", "home/downloads/file.c", NULL);
  printf("Entry object:\n key: %s, value: %s\n", entry->key, entry->value);
}
