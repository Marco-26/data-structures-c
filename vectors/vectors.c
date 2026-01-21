// build a std::vector from CPP in C

// TODO: USE ENUM FOR ERROR CODES MAYBE
// TODO: TESTS TO VALIDATE THIS CODE

#include "vectors.h"

VectorError vectorGrow(Vector *vector)
{
  // increase capacity as we go
  int *newAlloc = realloc(vector->data, (vector->capacity * 2) * sizeof(int));

  if (newAlloc == NULL)
    return VECTOR_ERR_ALLOC;

  vector->capacity *= 2;
  vector->data = newAlloc;
  return VECTOR_OK;
}

VectorError vectorPushBack(Vector *vector, int value)
{
  if (vector->size == vector->capacity)
  {
    const int res = vectorGrow(vector);
    if (res == VECTOR_ERR_ALLOC)
    {
      return VECTOR_ERR_ALLOC;
    }
  }
  vector->data[vector->size] = value;
  vector->size++;
  return VECTOR_OK;
}

VectorError vectorInsert(Vector *vector, int value, int position)
{
  if (position >= vector->size)
  {
    const int res = vectorPushBack(vector, value);
    if (res == VECTOR_ERR_ALLOC)
    {
      return VECTOR_ERR_ALLOC;
    }
  }

  if (vector->size == vector->capacity)
  {
    const int res = vectorGrow(vector);
    if (res == VECTOR_ERR_ALLOC)
    {
      return VECTOR_ERR_ALLOC;
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

  return VECTOR_OK;
}

VectorError vectorErase(Vector *vector, int position)
{
  if (position > vector->size)
  {
    return VECTOR_ERR_OUT_OF_BOUNDS;
  }

  if (position == vector->size)
  {
    vector->size--;
    return VECTOR_OK;
  }

  for (int i = position; i < vector->size; i++)
  {
    int nextElem = vector->data[i + 1];
    vector->data[i] = nextElem;
  }
  vector->size--;

  return VECTOR_OK;
}

void vectorDestroy(Vector *vector)
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

void printVector(const Vector *vector)
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
    int res = vectorPushBack(vector, i);
    if (res == VECTOR_ERR_ALLOC)
    {
      printf("Memory allocation failed");
      break;
    }
    printf("Value: %d, Size: %zu, Capacity: %zu\n", vector->data[i], vector->size, vector->capacity);
  }

  printf("Modifying array...\n");
  int res = vectorInsert(vector, 38, 3);
  if (res == VECTOR_ERR_ALLOC)
  {
    printf("Error inserting value...");
    return VECTOR_ERR_ALLOC;
  }
  printVector(vector);

  res = vectorErase(vector, 4);
  if (res == VECTOR_ERR_OUT_OF_BOUNDS)
  {
    printf("Error erasing, position out of bonds...");
    return VECTOR_ERR_OUT_OF_BOUNDS;
  }
  printf("Erasing a position...\n");
  printVector(vector);

  vectorDestroy(vector);
}