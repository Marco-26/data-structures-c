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
    free(key);
    free(value);
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
  if (k == NULL || v == NULL)
  {
    return 1;
  }
  // 1. compute the hash for key
  // 2. get the index for the hashed value
  uint64_t hashed = FNV_1a(k);
  size_t index = hashed % hashTable->capacity;

  // 3. If current bucket is empty, just add the head
  if (hashTable->buckets[index] == NULL)
  {
    Entry *entry = entryInit(k, v, NULL);
    if (entry == NULL)
    {
      return 1;
    }

    hashTable->buckets[index] = entry;
    hashTable->size++;
    return 0;
  }

  Entry *current = hashTable->buckets[index];
  while (current)
  {
    if (strcmp(current->key, k) == 0)
    {
      char *newValue = malloc(strlen(v) + 1);

      if (newValue == NULL)
      {
        return 1;
      }

      free(current->value);
      strcpy(newValue, v);
      current->value = newValue;
      return 0;
    }

    current = current->next;
  }

  // 4. If current bucket is not empty, and no entry equals this, create a new entry with the current entries as child of new entry
  Entry *entry = entryInit(k, v, hashTable->buckets[index]);
  hashTable->buckets[index] = entry;
  hashTable->size++;

  return 0;
}

const char *hashTableGet(HashTable *hashTable, const char *k)
{
  uint64_t hashed = FNV_1a(k);
  int index = hashed % hashTable->capacity;

  Entry *head = hashTable->buckets[index];
  if (head == NULL)
  {
    return "";
  }

  Entry *current = head;
  while (current)
  {
    if (strcmp(current->key, k) == 0)
    {
      return current->value;
    }

    current = current->next;
  }

  return NULL;
}
void hashTableDestroy(HashTable *hashTable)
{
  // FREE EVERY BUCKET
  free(hashTable);
}