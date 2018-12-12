#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stdlib.h>

#include "error.h"

#include "common.h"

#define VECTOR_MAX_SIZE 100001

struct _vector {
	int elem[VECTOR_MAX_SIZE]; //array of elements
	size_t size; //quantity of stored elements
};

typedef struct _vector Vector;

/** Empty the vector */
void vector_create(Vector* vector);

/** Empty the vector */
void vector_free(Vector* vector);

/** Search for a element in the vector */
bool vector_search(Vector* vec, Elem value);

/** Insert a element in the vector */
void vector_insert(Vector *vector, Elem value);

/** Remove a specific element of the vector */
int vector_remove(Vector* vector, Elem value);

/** Print the elements of the vector; DEBUG ONLY */
void vector_printf(Vector* v);

#endif