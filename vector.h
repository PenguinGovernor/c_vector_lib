#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

// Type exportion
// {{{
typedef struct vector_obj vector_t;
// }}}

// Constructor & Destructor
// {{{

/**
 * Returns a newly initializd vector pointer
 * @param  initialSize The intial capacity for this vector
 * @return             A new vector pointer
 */
vector_t* newVector(size_t initialSize);

/**
 * Frees the memory used by the vector structure pointer
 *
 * @NOTE:
 * This does NOT free the items within the vector that is left up to the user
 * to free using vector_get
 *
 * @param pVec [description]
 */
void freeVector(vector_t** pVec);

// }}}

// Access Functions
// {{{

/**
 * Returns a pointer to an item at index i of a vector
 * @param pVec  The vector from which to get the item
 * @param index The index of where the item is located at
 * @return      A pointer to the actaul item, may need a cast
 */
void* vectorGet(vector_t *pVec, size_t index);

/**
 * Returns the length of this vector
 * @param  pVec The vector of which to check the length
 * @return      The length of this vector
 */
size_t vectorLength(vector_t *pVec);

// }}}


// Manipulation Functions
// {{{

/**
 * Appeds an item to a vector
 * @param pVec  The vector of which to append to
 * @param pItem The item to append
 */
void vectorAdd(vector_t *pVec, void *pItem);

/**
 * Inserts an item in a vector at a certain index
 * @param pVec  The vector to insert to
 * @param pItem The item to Insert
 * @param index The index of where the item to insert
 * @NOTE:
 * If an index is occuped all entries after the insertion will be shifted to
 * the right
 */
void vectorInsertAt(vector_t **pVec, void *pItem, size_t index);

/**
 * Removes an item at a certain index of this vector
 * @param pVec  The vector of which to remove an item from
 * @param index The index of the item of which to remove
 * @NOTE:
 * This does not free the memory of the assocated removed item, that is left
 * up to the user
 */
void vectorRemoveAt(vector_t **pVec, size_t index);

/**
 * Returns a newly allocated vector that is the joint set of two vectors
 * @param  pVecA The first vector to join
 * @param  pVecB The second vector to join
 * @return       returns a vector that contains the items of A, then the items of B
 */
vector_t* vectorJoin(vector_t *pVecA, vector_t* pVecB);

// }}}



#endif
