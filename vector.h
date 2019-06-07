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

/* Initializers */
void vectorInit(Vector* V, size_t elem_size, size_t capacity);
void vectorInitAssign(Vector* V, size_t elem_size, size_t capacity, void* elem);

/* Modifiers */
void vectorAssign(Vector* V, size_t capacity, void* elem);
void vectorCopy(Vector* V_dest, const Vector* V_src);
void vectorSwap(Vector* V_a, Vector* V_b);

void vectorPushBack(Vector* V, void* elem);
void vectorPushFront(Vector* V, void* elem);
void vectorInsert(Vector* V, size_t elem_index, void* elem);

void vectorPopBack(Vector* V);
void vectorPopFront(Vector* V);
void vectorErase(Vector* V, size_t elem_index);

void vectorResize(Vector* V, size_t new_size);
void vectorClear(Vector* V);

/* Capacity */
bool vectorIsEmpty(const Vector* V);
void vectorShrinkToFit(Vector* V);

/* Element access */
void* vectorAt(Vector* V, size_t elem_index);

#endif /* VECTOR_H */