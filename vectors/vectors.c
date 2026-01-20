// build a std::vector from CPP in C

// erase(position) -> Erase an element based on an index
// size() -> returns the size of the vector

#include "vectors.h"

int grow(Vector *vector)
{
  // increase capacity as we go
  int *newAlloc = realloc(vector->data, (vector->capacity * 2) * sizeof(int));

  if (newAlloc == NULL)
    return 1;

  vector->capacity *= 2;
  vector->data = newAlloc;
  return 0;
}

int push_back(Vector *vector, int value)
{
  if (vector->size == vector->capacity)
  {
    grow(vector);
  }
  vector->data[vector->size] = value;
  vector->size++;
  return 0;
}

int insert(Vector *vector, int value, int position)
{
  if (position >= vector->size)
  {
    return push_back(vector, value);
  }

  if (vector->size == vector->capacity)
  {
    int res = grow(vector);
    if (res == 1)
    {
      return 1;
    }
  }

  int buf = vector->data[position];
  vector->data[position] = value;
  vector->size++;

  for (int i = ++position; i < vector->size; i++)
  {
    int nextBuf = vector->data[i];
    vector->data[i] = buf;
    buf = nextBuf;
  }

  return 0;
}

void delete(Vector *vector)
{
  free(vector->data);
  free(vector);
}

Vector *init()
{
  Vector *vector = (Vector *)malloc(1 * sizeof(Vector));
  if (vector == NULL)
  {
    free(vector);
    return NULL;
  }

  int *data = (int *)malloc(4 * sizeof(int));
  if (data == NULL)
  {
    free(data);
    return NULL;
  }

  vector->data = data;
  vector->capacity = 4;
  vector->size = 0;
  return vector;
}

void printVector(Vector *vector)
{
  for (int i = 0; i < vector->size; i++)
  {
    printf("Value: %d, Size: %zu, Capacity: %zu\n", vector->data[i], vector->size, vector->capacity);
  }
}

int main()
{
  Vector *vector = init();
  if (vector == NULL || vector->data == NULL)
  {
    return 1;
  }

  for (int i = 0; i < 8; i++)
  {
    int res = push_back(vector, i);
    if (res == -1)
    {
      printf("Memory allocation failed");
      break;
    }
    printf("Value: %d, Size: %zu, Capacity: %zu\n", vector->data[i], vector->size, vector->capacity);
  }

  printf("Modifying array...\n");
  int res = insert(vector, 38, 3);
  if (res == 1)
  {
    printf("Error inserting value...");
    return 1;
  }
  printVector(vector);

  delete(vector);
}