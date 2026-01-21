#include "vectors.h"

void printVector(const Vector *vector)
{
  for (int i = 0; i < vector->size; i++)
  {
    printf("Value: %d, Size: %zu, Capacity: %zu\n", vector->data[i], vector->size, vector->capacity);
  }
}

void displayError(VectorError error)
{
  char *errorMsg;
  switch (error)
  {
  case VECTOR_ERR_ALLOC:
    errorMsg = "Memory allocation failed";
    break;
  case VECTOR_ERR_OUT_OF_BOUNDS:
    errorMsg = "Position exceeds vector size";
    break;
  case VECTOR_OK:
    errorMsg = "";
    break;
  }

  printf("%s", errorMsg);
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
      displayError(VECTOR_ERR_ALLOC);
      break;
    }
    printf("Value: %d, Size: %zu, Capacity: %zu\n", vector->data[i], vector->size, vector->capacity);
  }

  printf("Modifying array...\n");
  int res = vectorInsert(vector, 38, 3);
  if (res == VECTOR_ERR_ALLOC)
  {
    displayError(VECTOR_ERR_ALLOC);
    return VECTOR_ERR_ALLOC;
  }
  printVector(vector);

  res = vectorErase(vector, 4);
  if (res == VECTOR_ERR_OUT_OF_BOUNDS)
  {
    displayError(VECTOR_ERR_OUT_OF_BOUNDS);
    return VECTOR_ERR_OUT_OF_BOUNDS;
  }
  printf("Erasing a position...\n");
  printVector(vector);

  vectorDestroy(vector);
}