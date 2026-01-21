#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int *data;
  size_t size;
  size_t capacity;
} Vector;

typedef enum
{
  VECTOR_OK = 0,
  VECTOR_ERR_ALLOC = 1,
  VECTOR_ERR_OUT_OF_BOUNDS = 2,
} VectorError;

Vector *
init();
VectorError vectorPushBack(Vector *, int);
VectorError vectorInsert(Vector *, int, int);
VectorError vectorErase(Vector *, int);
VectorError vectorGrow(Vector *);
void vectorDestroy(Vector *);
