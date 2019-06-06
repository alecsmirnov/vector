#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Vector {
	size_t size;
	size_t capacity;
	size_t elem_size;

	void* data;
} Vector;

typedef enum ERROR {
	ERROR_OK_STATUS,
	ERROR_NULLPTR,
	ERROR_ELEM_SIZE,
	ERROR_INDEX_OUT_OF_BOUND
} ERROR;

/* Initializers */
ERROR vectorInit(Vector* V, size_t elem_size, size_t capacity);
ERROR vectorInitAssign(Vector* V, size_t elem_size, size_t count, void* elem);

/* Modifiers */
ERROR vectorAssign(Vector* V, size_t count, void* elem);
ERROR vectorCopy(Vector* V_dest, const Vector* V_src);
ERROR vectorSwap(Vector* V_a, Vector* V_b);

ERROR vectorPushBack(Vector* V, void* elem);
ERROR vectorPushFront(Vector* V, void* elem);
ERROR vectorInsert(Vector* V, size_t elem_index, void* elem);

ERROR vectorPopBack(Vector* V);
ERROR vectorPopFront(Vector* V);
ERROR vectorErase(Vector* V, size_t elem_index);

ERROR vectorResize(Vector* V, size_t new_size);
ERROR vectorClear(Vector* V);

/* Capacity */
bool vectorIsEmpty(const Vector* V);
ERROR vectorShrinkToFit(Vector* V);

/* Element access */
void* vectorAt(Vector* V, size_t elem_index);

#endif