#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int *data;
  size_t size;
  size_t capacity;
} Vector;

Vector *init();
int push_back(Vector *, int);
int insert(Vector *, int, int);
int grow(Vector *);
void delete (Vector *);
