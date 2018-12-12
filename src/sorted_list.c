#include "sorted_list.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/** Structure of each node */
typedef struct node {
	Elem value;
	struct node* next;
} node;

/** Structure of the sorted list */
struct _SortedList {
	node *begin;
};

/** Create a Sorted List, and return it */
SortedList* sorted_list_create() {
	SortedList* list = malloc(sizeof(SortedList));
	if (list == NULL)
		return NULL;

	list->begin = NULL;
	return list;
}

/** Destroy the sorted list and free every element */
void sorted_list_free(SortedList* list) {
	if (list == NULL)
		return; //nothing to remove

	//destroy all the elements
	while (list->begin != NULL) {
		node* aux = list->begin->next;
		free(list->begin);
		list->begin = aux;
 	}
 	//free the list
 	free(list);
}

/** Internal function; update the "prev" and "actual" pointers, according to the value searched */
void internal_search_sorted(SortedList* list, Elem value, node** prev, node** actual) {
	*prev = NULL;
	*actual = list->begin;

	while (*actual != NULL && (*actual)->value < value) {
		*prev = *actual;
		*actual = (*actual)->next;
	}
}

/** Search for a element into the list */
bool sorted_list_search(SortedList* list, Elem value) {
	node *prev, *actual;
	internal_search_sorted(list, value, &prev, &actual);
	return actual != NULL && actual->value == value;
}

/** Insert a element in the list */
void sorted_list_insert(SortedList *list, Elem value) {
	node *prev, *actual, *new;
	internal_search_sorted(list, value, &prev, &actual);

	if (actual != NULL && actual->value == value)
		return; //repeated element

	new = malloc(sizeof(node));
	if (new == NULL)
		return; //no space

	// Update pointers
	new->value = value;
	new->next = actual;

	if (prev == NULL)
		list->begin = new;
	else
		prev->next = new;
}

/** Remove a element from the list */
int sorted_list_remove(SortedList* list, Elem value) {
	node *prev, *actual;
	internal_search_sorted(list, value, &prev, &actual);

	if (actual == NULL || actual->value != value)
		return -1; //element not found

	// update pointers
	if (prev == NULL)
		list->begin = actual->next;
	else
		prev->next = actual->next;

	// remove it
	free(actual);
	return 0;
}

/** Print every element of the list; DEBUG ONLY */
int sorted_list_printf(SortedList* list) {
	node* aux = list->begin;
	while(aux != NULL) {
		printf("%d ", aux->value);
		aux = aux->next;
	}
	return printf("\n");
}
