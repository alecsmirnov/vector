#include <stdio.h>

#include "vector.h"

typedef const char* CPCHAR;
declareVectorType(int)
declareVectorType(char)
declareVectorType(CPCHAR)

int main(int argc, char* argv[]) {
	vector_int* V_int = (vector_int*)malloc(sizeof(vector_int));
	initVector_int(V_int, 0);
	printf("Vector_int size: %d, capacity: %d\n", V_int->size, V_int->capacity);

	pushBackVector_int(V_int, 9);
	pushBackVector_int(V_int, 8);
	pushBackVector_int(V_int, 7);
	pushBackVector_int(V_int, 6);
	pushBackVector_int(V_int, 5);
	pushBackVector_int(V_int, 4);
	pushBackVector_int(V_int, 3);
	pushBackVector_int(V_int, 2);
	pushBackVector_int(V_int, 1);
	pushBackVector_int(V_int, 0);

	for (size_t i = 0; i != V_int->size; ++i)
		printf("%d ", V_int->data[i]);
	puts("");

	printf("Vector_int size: %d, capacity: %d\n\n", V_int->size, V_int->capacity);

	freeVector_int(V_int);
	free(V_int);
	//****************************************************************************

	vector_char V_char;
	initVector_char(&V_char, 0);
	printf("Vector_char size: %d, capacity: %d\n", V_char.size, V_char.capacity);

	pushBackVector_char(&V_char, 'a');
	pushBackVector_char(&V_char, 'B');
	pushBackVector_char(&V_char, 'b');
	pushBackVector_char(&V_char, 'C');
	pushBackVector_char(&V_char, 'c');
	pushBackVector_char(&V_char, 'C');
	pushBackVector_char(&V_char, 'd');

	for (size_t i = 0; i != V_char.size; ++i)
		printf("%c ", V_char.data[i]);
	puts("");

	printf("Vector_char size: %d, capacity: %d\n\n", V_char.size, V_char.capacity);

	freeVector_char(&V_char);
	//****************************************************************************

	vector_CPCHAR V_cpchar;
	initVector_CPCHAR(&V_cpchar, 6);
	
	printf("Vector_CPCHAR size: %d, capacity: %d\n", V_cpchar.size, V_cpchar.capacity);

	pushBackVector_CPCHAR(&V_cpchar, "This");
	pushBackVector_CPCHAR(&V_cpchar, "right");
	pushBackVector_CPCHAR(&V_cpchar, "here");
	pushBackVector_CPCHAR(&V_cpchar, "is");
	pushBackVector_CPCHAR(&V_cpchar, "my");
	pushBackVector_CPCHAR(&V_cpchar, "swag!");

	for (size_t i = 0; i != V_cpchar.size; ++i)
		printf("%s ", V_cpchar.data[i]);
	puts("");

	printf("Vector_CPCHAR size: %d, capacity: %d\n", V_cpchar.size, V_cpchar.capacity);

	freeVector_CPCHAR(&V_cpchar);

	return 0;
}