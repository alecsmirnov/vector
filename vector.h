#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <malloc.h>

/* C++ std::vector standard Grown factor */
#define GROWN_FACTOR 1.5					

/* vector typename creator: */
#define createType(type) vector##_##type	


/* Vector declaration keyword */
#define declareVectorType(type)	typedef struct createType(type) {				\
	type* data;																	\
																				\
	size_t size;																\
	size_t capacity;															\
} createType(type);																\
																				\
/* Vector initialization method */												\
void initVector_##type(createType(type)* V, size_t capacity) {					\
	V->size = 0;																\
	V->capacity = capacity;														\
																				\
	V->data = V->capacity ? (type*)malloc(sizeof(type) * V->capacity) : NULL;	\
}																				\
																				\
/* Vector free method */														\
void freeVector_##type(createType(type)* V) {									\
	V->size = V->capacity = 0;													\
																				\
	free(V->data);																\
	V->data = NULL;																\
}																				\
																				\
/* Vector push back method */													\
void pushBackVector_##type(createType(type)* V, type value) {					\
	if (V->size == V->capacity) {												\
		V->capacity = (size_t)(V->capacity * GROWN_FACTOR);						\
																				\
		if (V->size == V->capacity)												\
			++V->capacity;														\
																				\
		V->data = (type*)realloc(V->data, sizeof(type) * V->capacity);			\
	}																			\
																				\
	V->data[V->size++] = value;													\
}																				\
																				\
/* Vector resize method */														\
void resizeVector_##type(createType(type)* V, size_t capacity) {				\
	if (0 < capacity) {															\
		V->capacity = capacity;													\
																				\
		V->data = (type*)realloc(V->data, sizeof(type) * V->capacity);			\
	}																			\
	else																		\
		freeVector_##type(V);													\
}

#endif