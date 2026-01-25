#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "../include/hash-table.h"

// forward decls if needed
// HashTable *hashTableInit();
// int hashTablePut(HashTable *hashTable, const char *k, const char *v);
// const char *hashTableGet(HashTable *hashTable, const char *k);
// uint64_t FNV_1a(const char *text);

static int tests_failed = 0;

static void expect_int(const char *label, int got, int expected)
{
  if (got != expected)
  {
    printf("[FAIL] %s: got %d expected %d\n", label, got, expected);
    tests_failed++;
  }
  else
  {
    printf("[ OK ] %s\n", label);
  }
}

static void expect_str(const char *label, const char *got, const char *expected)
{
  if (got == NULL && expected == NULL)
  {
    printf("[ OK ] %s\n", label);
    return;
  }
  if (got == NULL || expected == NULL || strcmp(got, expected) != 0)
  {
    printf("[FAIL] %s: got '%s' expected '%s'\n",
           label,
           got ? got : "(NULL)",
           expected ? expected : "(NULL)");
    tests_failed++;
  }
  else
  {
    printf("[ OK ] %s\n", label);
  }
}

static void print_bucket_for_key(HashTable *ht, const char *k)
{
  uint64_t h = FNV_1a(k);
  size_t idx = (size_t)(h % ht->capacity);
  printf("    key='%s' -> hash=%llu bucket=%zu\n", k, (unsigned long long)h, idx);
}

static void find_collision_pair(HashTable *ht,
                                const char *prefix,
                                char *out1, size_t out1_sz,
                                char *out2, size_t out2_sz)
{
  // Very small brute force: try prefix + number until two keys land in same bucket.
  // Keeps it deterministic and avoids needing external libs.
  size_t seen_bucket = (size_t)-1;
  char first[128] = {0};

  for (int i = 0; i < 100000; i++)
  {
    char key[128];
    snprintf(key, sizeof(key), "%s%d", prefix, i);
    size_t idx = (size_t)(FNV_1a(key) % ht->capacity);

    if (seen_bucket == (size_t)-1)
    {
      seen_bucket = idx;
      strncpy(first, key, sizeof(first) - 1);
      continue;
    }

    if (idx == seen_bucket && strcmp(key, first) != 0)
    {
      strncpy(out1, first, out1_sz - 1);
      strncpy(out2, key, out2_sz - 1);
      return;
    }
  }

  // fallback if none found (should be rare with small capacity)
  strncpy(out1, "COLLIDE_A", out1_sz - 1);
  strncpy(out2, "COLLIDE_B", out2_sz - 1);
}

int main(void)
{
  HashTable *ht = hashTableInit();
  if (!ht)
  {
    printf("Failed to init hash table\n");
    return 1;
  }

  printf("=== Basic put/get ===\n");
  expect_int("put PATH", hashTablePut(ht, "PATH", "/home/downloads/file.c"), 0);
  expect_str("get PATH", hashTableGet(ht, "PATH"), "/home/downloads/file.c");

  printf("\n=== Replace existing key ===\n");
  expect_int("put PATH again (replace)", hashTablePut(ht, "PATH", "another one"), 0);
  expect_str("get PATH after replace", hashTableGet(ht, "PATH"), "another one");

  printf("\n=== Not found behavior ===\n");
  const char *nf = hashTableGet(ht, "DOES_NOT_EXIST");
  // If you decide not-found should be NULL, check that:
  if (nf != NULL)
  {
    printf("[WARN] get DOES_NOT_EXIST returned '%s' (consider returning NULL for not found)\n", nf);
  }
  else
  {
    printf("[ OK ] get DOES_NOT_EXIST returned NULL\n");
  }

  printf("\n=== Collision test (two keys same bucket) ===\n");
  char k1[64] = {0}, k2[64] = {0};
  find_collision_pair(ht, "K", k1, sizeof(k1), k2, sizeof(k2));

  printf("Collision candidates:\n");
  print_bucket_for_key(ht, k1);
  print_bucket_for_key(ht, k2);

  expect_int("put k1", hashTablePut(ht, k1, "v1"), 0);
  expect_int("put k2", hashTablePut(ht, k2, "v2"), 0);
  expect_str("get k1", hashTableGet(ht, k1), "v1");
  expect_str("get k2", hashTableGet(ht, k2), "v2");

  printf("\n=== Size sanity (if you track it) ===\n");
  // Expected: PATH + k1 + k2 (and maybe SYS if you add it) => 3 total unique keys so far
  printf("Reported size: %zu\n", ht->size);
  printf("Note: size should count unique keys only (replace shouldn't increment).\n");

  printf("\n=== Summary ===\n");
  if (tests_failed == 0)
  {
    printf("All checks passed ✅\n");
  }
  else
  {
    printf("%d checks failed ❌\n", tests_failed);
  }

  // Don't call hashTableDestroy until you implement it correctly.
  hashTableDestroy(ht);

  return tests_failed ? 1 : 0;
}
