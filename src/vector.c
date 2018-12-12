#include "vector.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "error.h"

/** Empty the vector */
void vector_create(Vector * vector) {
	vector->size = 0;
}

/** Empty the vector */
void vector_free(Vector* vector) {
	vector->size = 0;
}

/** Returns the position of the element if found; -1 otherwise */
int vector_internal_search(int lo, int hi, Vector* vec, Elem value) {
	int mid = (lo + hi) / 2;
	while (lo <= hi) {
		if (vec->elem[mid] == value) {
			return mid;
		} else if (value < vec->elem[mid]) {
			hi = mid - 1;
		} else if (value > vec->elem[mid]) {
			lo = mid + 1;
		}
		mid = (lo + hi) / 2;
	}

	return -1;

}

/** Search for a element in the vector */
bool vector_search(Vector* vec, Elem value) {
	return vector_internal_search(0, (int)vec->size - 1, vec, value) != -1;
}

/** Insert a element in the vector */
void vector_insert(Vector *vector, Elem value) {
	if (vector->size == VECTOR_MAX_SIZE) return;

	if (vector_search(vector, value)) return; //element already inserted

	size_t pos;
	for (pos = vector->size; pos > 0 && vector->elem[pos-1] > value; pos--)
		vector->elem[pos] = vector->elem[pos-1];
	vector->elem[pos] = value;

	vector->size++;
}

/** Remove a specific element of the vector */
int vector_remove(Vector* vector, Elem value) {
	if (vector->size == 0) return -1;

	int pos = vector_internal_search(0, (int)vector->size - 1, vector, value);
	if (pos == -1) return -1;

	for (size_t i = (size_t)pos + 1; i < vector->size; i++) //shift the remaining elements
		vector->elem[i-1] = vector->elem[i];
	
	vector->size--;
	return 1;
}

/** Print the elements of the vector; DEBUG ONLY */
void vector_printf(Vector* v) {
	for (size_t i = 0; i < v->size; i++)
		printf("%d ", v->elem[i]);
	printf("\n");
}
