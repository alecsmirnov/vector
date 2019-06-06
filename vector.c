#include "vector.h"

#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <assert.h>

#define GROWTH_FACTOR 1.5

#define CAPACITY_MIN 1

#define VECTOR_BEGIN 0
#define VECTOR_END   V->size

#define EMPTY_VECTOR { 0, 0, 0, NULL };

static void initCapacity(Vector* V) {
	V->capacity = CAPACITY_MIN;
	V->data = malloc(V->capacity * V->elem_size);
}

static void expandCapacity(Vector* V) {
	if (V->size == V->capacity) {
		V->capacity = (size_t)round(V->capacity * GROWTH_FACTOR);

		void* new_data = malloc(V->capacity * V->elem_size);
		memcpy(new_data, V->data, V->capacity * V->elem_size);

		free(V->data);

		V->data = new_data;
	}
}

static void dataExpand(Vector* V) {
	vectorIsEmpty(V) ? initCapacity(V) : expandCapacity(V);
}

static void* dataAccess(Vector* V, size_t elem_index) {
	return (char*)V->data + (V->elem_size * elem_index);
}

static void dataRightOffset(Vector* V, size_t offset) {
	size_t offset_size = (V->size - offset) * V->elem_size;
	memmove(dataAccess(V, offset + 1), dataAccess(V, offset), offset_size);

	++V->size;
}

static void dataLeftOffset(Vector* V, size_t offset) {
	size_t offset_size = (V->size - offset - 1) * V->elem_size;
	memmove(dataAccess(V, offset), dataAccess(V, offset + 1), offset_size);

	--V->size;
}

VectorError vectorInit(Vector* V, size_t elem_size, size_t capacity) {
	VectorError error = NULLPTR_ERROR;

	if (V) {
		error = ELEM_SIZE_ERROR;

		if (elem_size) {
			V->size = 0;
			V->capacity = capacity;
			V->elem_size = elem_size;

			V->data = V->capacity ? malloc(V->capacity * V->elem_size) : NULL;

			error = OK_STATUS;
		}
	}

	return error;
}

VectorError vectorInitAssign(Vector* V, size_t elem_size, size_t count, void* elem) {
	VectorError error = vectorInit(V, elem_size, count);

	if (error == OK_STATUS && elem) {
		V->size = count;

		for (size_t i = 0; i != V->size; ++i)
			memcpy(dataAccess(V, i), elem, V->elem_size);
	}

	return error;
}

VectorError vectorAssign(Vector* V, size_t count, void* elem) {
	size_t V_elem_size = V->elem_size;
	VectorError error = vectorClear(V);

	if (error == OK_STATUS)
		error = vectorInitAssign(V, V_elem_size, count, elem);

	return error;
}

VectorError vectorCopy(Vector* V_dest, const Vector* V_src) {
	VectorError error = NULLPTR_ERROR;

	if (V_src && V_dest) {
		V_dest->size = V_src->size;
		V_dest->capacity = V_src->capacity;
		V_dest->elem_size = V_src->elem_size;

		free(V_dest->data);

		V_dest->data = malloc(V_dest->capacity * V_dest->elem_size);
		memcpy(V_dest->data, V_src->data, V_dest->capacity * V_dest->elem_size);

		error = OK_STATUS;
	}

	return error;
}

VectorError vectorSwap(Vector* V_a, Vector* V_b) {
	VectorError error = NULLPTR_ERROR;

	if (V_a && V_b) {
		Vector tmp = EMPTY_VECTOR;

		vectorCopy(V_a,  &tmp);
		vectorCopy(V_b,  V_a);
		vectorCopy(&tmp, V_b);
		vectorClear(&tmp);

		error = OK_STATUS;
	}

	return error;
}

VectorError vectorPushBack(Vector* V, void* elem) {
	return vectorInsert(V, VECTOR_END, elem);
}

VectorError vectorPushFront(Vector* V, void* elem) {
	return vectorInsert(V, VECTOR_BEGIN, elem);
}

VectorError vectorInsert(Vector* V, size_t elem_index, void* elem) {
	VectorError error = NULLPTR_ERROR;

	if (V) {
		error = INDEX_OUT_OF_BOUND_ERROR;

		if (vectorIsEmpty(V) || elem_index <= V->size) {
			dataExpand(V);
			dataRightOffset(V, elem_index);
			memcpy(dataAccess(V, elem_index), elem, V->elem_size);

			error = OK_STATUS;
		}
	}

	return error;
}

VectorError vectorPopBack(Vector* V) {
	return vectorErase(V, VECTOR_END - 1);
}

VectorError vectorPopFront(Vector* V) {
	return vectorErase(V, VECTOR_BEGIN);
}

VectorError vectorErase(Vector* V, size_t elem_index) {
	VectorError error = NULLPTR_ERROR;

	if (V) {
		error = INDEX_OUT_OF_BOUND_ERROR;

		if (elem_index < V->size) {
			dataLeftOffset(V, elem_index);

			error = OK_STATUS;
		}
	}

	return error;
}

bool vectorIsEmpty(const Vector* V) {
	assert(V != NULL);

	return V->data == NULL;
}

VectorError vectorShrinkToFit(Vector* V) {
	VectorError error = NULLPTR_ERROR;

	if (V) {
		void* new_data = malloc(V->size * V->elem_size);
		memcpy(new_data, V->data, V->size * V->elem_size);

		free(V->data);

		V->capacity = V->size;
		V->data = new_data;

		error = OK_STATUS;
	}

	return error;
}

VectorError vectorResize(Vector* V, size_t new_size) {
	VectorError error = NULLPTR_ERROR;

	if (V) {
		void* new_data = new_size ? malloc(new_size * V->elem_size) : NULL;

		memcpy(new_data, V->data, new_size * V->elem_size);
		free(V->data);

		V->size = new_size;
		V->capacity = new_size;
		V->data = new_data;

		error = OK_STATUS;
	}

	return error;
}

VectorError vectorClear(Vector* V) {
	VectorError error = NULLPTR_ERROR;

	if (V) {
		V->size = 0;
		V->capacity = 0;
		V->elem_size = 0;

		free(V->data);
		V->data = NULL;

		error = OK_STATUS;
	}

	return error;
}

void* vectorAt(Vector* V, size_t elem_index) {
	assert(V != NULL);
	assert(V->data != NULL);
	assert(elem_index < V->size);
	assert(V->elem_size != 0);

	return dataAccess(V, elem_index);
}