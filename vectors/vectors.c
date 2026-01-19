// build a std::vector from CPP in C

// insert(value, position) -> Add a given value at a specified position
// erase(position) -> Erase an element based on an index
// size() -> returns the size of the vector

#include "vectors.h"

int push_back(Vector *vector, int value)
{
  if (vector->size == vector->capacity)
  {
    // increase capacity as we go
    int *newAlloc = realloc(vector->data, (vector->capacity * 2) * sizeof(int));

    if (newAlloc == NULL)
      return -1;

    vector->capacity *= 2;
    vector->data = newAlloc;
  }
  vector->data[vector->size] = value;
  vector->size++;
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

int main()
{
  Vector *vector = init();
  if (vector == NULL || vector->data == NULL)
  {
    return 1;
  }

  for (int i = 0; i < 100; i++)
  {
    int res = push_back(vector, i);
    if (res == -1)
    {
      printf("Memory allocation failed");
      break;
    }
    printf("Value: %d, Size: %zu, Capacity: %zu\n", vector->data[i], vector->size, vector->capacity);
  }

  delete(vector);
}