#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>

typedef enum VectorError {
	OK_STATUS,
	NULLPTR_ERROR,
	ELEM_SIZE_ERROR,
	INDEX_OUT_OF_BOUND_ERROR
} VectorError;

typedef struct Vector {
	size_t size;
	size_t capacity;
	size_t elem_size;

	void* data;
} Vector;

/* Initializers */
VectorError vectorInit(Vector* V, size_t elem_size, size_t capacity);
VectorError vectorInitAssign(Vector* V, size_t elem_size, size_t count, void* elem);

/* Modifiers */
VectorError vectorAssign(Vector* V, size_t count, void* elem);
VectorError vectorCopy(Vector* V_dest, const Vector* V_src);
VectorError vectorSwap(Vector* V_a, Vector* V_b);

VectorError vectorPushBack(Vector* V, void* elem);
VectorError vectorPushFront(Vector* V, void* elem);
VectorError vectorInsert(Vector* V, size_t elem_index, void* elem);

VectorError vectorPopBack(Vector* V);
VectorError vectorPopFront(Vector* V);
VectorError vectorErase(Vector* V, size_t elem_index);

VectorError vectorResize(Vector* V, size_t new_size);
VectorError vectorClear(Vector* V);

/* Capacity */
bool vectorIsEmpty(const Vector* V);
VectorError vectorShrinkToFit(Vector* V);

/* Element access */
void* vectorAt(Vector* V, size_t elem_index);

#endif