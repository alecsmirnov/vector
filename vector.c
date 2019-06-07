#include "vector.h"

#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <assert.h>

/* Defines */
#define GROWTH_FACTOR 1.5		/* C++ std::vector standard Growth factor */

#define INITIAL_CAPACITY 1		

/* Private functions */
static void initCapacity(Vector* V) {
	V->capacity = INITIAL_CAPACITY;
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

/* Public functions */
void vectorInit(Vector* V, size_t elem_size, size_t capacity) {
	assert(("Vector can't be a NULL pointer", V != NULL));
	assert(("Element size can't be equal 0", 0 < elem_size));

	V->size = 0;
	V->capacity = capacity;
	V->elem_size = elem_size;

	V->data = V->capacity ? malloc(V->capacity * V->elem_size) : NULL;
}

void vectorInitAssign(Vector* V, size_t elem_size, size_t capacity, void* elem) {
	assert(("Vector can't be a NULL pointer", V != NULL));
	assert(("Element size can't be equal 0", 0 < elem_size));

	vectorInit(V, elem_size, capacity);

	if (elem) {
		V->size = capacity;

		for (size_t i = 0; i != V->size; ++i)
			memcpy(dataAccess(V, i), elem, V->elem_size);
	}
}

void vectorAssign(Vector* V, size_t capacity, void* elem) {
	assert(("Vector can't be a NULL pointer", V != NULL));

	size_t V_elem_size = V->elem_size;

	vectorClear(V);
	vectorInitAssign(V, V_elem_size, capacity, elem);
}

void vectorCopy(Vector* V_dest, const Vector* V_src) {
	assert(("Source vector can't be a NULL pointer", V_dest != NULL));
	assert(("Destination vector can't be a NULL pointer", V_src != NULL));

	V_dest->size = V_src->size;
	V_dest->capacity = V_src->capacity;
	V_dest->elem_size = V_src->elem_size;

	free(V_dest->data);
	V_dest->data = NULL;

	if (V_src->capacity) {
		V_dest->data = malloc(V_src->capacity * V_src->elem_size);
		memcpy(V_dest->data, V_src->data, V_src->capacity * V_src->elem_size);
	}
}

void vectorSwap(Vector* V_a, Vector* V_b) {
	assert(("A-vector can't be a NULL pointer", V_a != NULL));
	assert(("B-vector can't be a NULL pointer", V_b != NULL));

	Vector V_tmp = {0, 0, 0, NULL};

	vectorCopy(&V_tmp, V_a);
	vectorCopy(V_a, V_b);
	vectorCopy(V_b, &V_tmp);

	vectorClear(&V_tmp);
}

void vectorPushBack(Vector* V, void* elem) {
	assert(("Vector can't be a NULL pointer", V != NULL));
	assert(("Element can't be a NULL pointer", elem != NULL));

	vectorInsert(V, V->size, elem);
}

void vectorPushFront(Vector* V, void* elem) {
	assert(("Vector can't be a NULL pointer", V != NULL));
	assert(("Element can't be a NULL pointer", elem != NULL));

	vectorInsert(V, 0, elem);
}

void vectorInsert(Vector* V, size_t elem_index, void* elem) {
	assert(("Vector can't be a NULL pointer", V != NULL));
	assert(("Index can't be more than vector size", elem_index <= V->size));

	dataExpand(V);
	dataRightOffset(V, elem_index);
	memcpy(dataAccess(V, elem_index), elem, V->elem_size);
}

void vectorPopBack(Vector* V) {
	assert(("Vector can't be a NULL pointer", V != NULL));

	vectorErase(V, V->size - 1);
}

void vectorPopFront(Vector* V) {
	assert(("Vector can't be a NULL pointer", V != NULL));

	vectorErase(V, 0);
}

void vectorErase(Vector* V, size_t elem_index) {
	assert(("Vector can't be a NULL pointer", V != NULL));
	assert(("Index can't be more than or equal to vector size", elem_index < V->size));

	dataLeftOffset(V, elem_index);
}

bool vectorIsEmpty(const Vector* V) {
	assert(("Vector can't be a NULL pointer", V != NULL));

	return V->data == NULL;
}

void vectorShrinkToFit(Vector* V) {
	assert(("Vector can't be a NULL pointer", V != NULL));

	void* new_data = malloc(V->size * V->elem_size);
	memcpy(new_data, V->data, V->size * V->elem_size);

	free(V->data);

	V->capacity = V->size;
	V->data = new_data;
}

void vectorResize(Vector* V, size_t new_size) {
	assert(("Vector can't be a NULL pointer", V != NULL));

	if (V->capacity < new_size) {
		void* new_data = malloc(new_size * V->elem_size);
		memcpy(new_data, V->data, new_size * V->elem_size);

		free(V->data);

		V->capacity = new_size;
		V->data = new_data;
	}

	V->size = new_size;
}

void vectorClear(Vector* V) {
	assert(("Vector can't be a NULL pointer", V != NULL));

	V->size = 0;
	V->capacity = 0;
	V->elem_size = 0;

	free(V->data);
	V->data = NULL;
}

void* vectorAt(Vector* V, size_t elem_index) {
	assert(("Vector can't be a NULL pointer", V != NULL));
	assert(("Vector can't be empty", V->data != NULL));
	assert(("Index can't be more than or equal to vector size", elem_index < V->size));

	return dataAccess(V, elem_index);
}