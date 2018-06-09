#include "vector.h"
#include <assert.h>

// Type definition
// {{{
struct vector_obj {
  void **array;
  size_t current_lenth;
  size_t capacity;
};
// }}}

// Constructor & Destructor
// {{{
vector_t *newVector(size_t initialSize) {
  // Init capacity can't be less than 0
  assert(initialSize > 0);

  // Allocate the struct
  vector_t *vec = malloc(sizeof(vector_t));
  assert(vec != NULL);

  // Set the initial capacity
  vec->capacity = initialSize;

  // Allocate spcae for the array
  vec->array = calloc(initialSize, sizeof(void *));
  assert(vec->array != NULL);

  // Set the size to 0
  vec->current_lenth = 0;

  // And we're done here
  return vec;
}

void freeVector(vector_t **pVec) {
  assert(pVec != NULL && *pVec != NULL);

  // Free the array
  free((*pVec)->array);
  (*pVec)->array = NULL;

  // Free the struct
  free(*pVec);
  *pVec = NULL;
}
//}}}

// Access Functions
// {{{
void *vectorGet(vector_t *pVec, size_t index) {
  assert(pVec != NULL);
  assert(index < vectorLength(pVec));
  return pVec->array[index];
}
size_t vectorLength(vector_t *pVec) {
  assert(pVec != NULL);
  return pVec->current_lenth;
}
// }}}

// Manipulation Functions
// {{{
void vectorAdd(vector_t *pVec, void *pItem) {
  assert(pVec != NULL);

  // If we need to reallocate
  if (pVec->current_lenth >= pVec->capacity) {
    // Double the capacity
    pVec->capacity *= 2;
    // Reallocate the array
    pVec->array = realloc(pVec->array, sizeof(void *) * pVec->capacity);
    assert(pVec->array != NULL);
  }

  // We have room, go ahead and insert
  pVec->array[pVec->current_lenth] = pItem;
  // Add 1 to current length
  pVec->current_lenth += 1;
}

void vectorInsertAt(vector_t **pVec, void *pItem, size_t index) {

  assert(pVec != NULL && *pVec != NULL);
  assert(index < vectorLength(*pVec));

  // Copy all the following items into a temp vector
  vector_t *sliceA = newVector(vectorLength(*pVec) + 1);
  for (size_t i = 0; i < index; i += 1) {
    vectorAdd(sliceA, vectorGet(*pVec, i));
  }

  // Add the new item to slice A
  vectorAdd(sliceA, pItem);

  // Add the remaining items
  for (size_t i = index; i < vectorLength(*pVec); i += 1) {
    vectorAdd(sliceA, vectorGet(*pVec, i));
  }

  // Delete the input
  freeVector(pVec);
  // Reassign it
  *pVec = sliceA;
}

void vectorRemoveAt(vector_t **pVec, size_t index) {
  // Same as insert, just with an extra [ + 1 ] in the 2nd loop
  // to skip over the omitted item, also obviously doesn't
  // insert item
  assert(pVec != NULL && *pVec != NULL);

  // Copy all the following items into a temp vector
  vector_t *sliceA = newVector(index + 1);
  for (size_t i = 0; i < index; i += 1) {
    vectorAdd(sliceA, vectorGet(*pVec, i));
  }

  // Add the remaining items
  for (size_t i = index + 1; i < vectorLength(*pVec); i += 1) {
    vectorAdd(sliceA, vectorGet(*pVec, i));
  }

  // Delete the input
  freeVector(pVec);
  // Reassign it
  *pVec = sliceA;
}

vector_t *vectorJoin(vector_t *pVecA, vector_t *pVecB) {
  assert(pVecA != NULL && pVecB != NULL);

  // Make a new vector
  vector_t *joinedVector = newVector(vectorLength(pVecA) + vectorLength(pVecB));

  // Add A to the joined vector
  for (size_t i = 0; i < vectorLength(pVecA); i += 1) {
    vectorAdd(joinedVector, vectorGet(pVecA, i));
  }

  // Add B to the joined vector
  for (size_t i = 0; i < vectorLength(pVecB); i += 1) {
    vectorAdd(joinedVector, vectorGet(pVecB, i));
  }

  // Return the joined vector
  return joinedVector;
}
// }}}

// }}}
