#include "sorted_list_sentinel.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

/** Struct of the node; every node have a pointer to the next element of the list */
typedef struct node {
	Elem value;
	struct node* next;
} node;

/** Struct of the list; it has a begin and a sentinel */
struct _SortedListSent {
	node *begin, *sentinel;
};

/** Create a Sorted List with Sentinel, and return it */
SortedListSent* sorted_list_sent_create() {
	SortedListSent* list = malloc(sizeof(SortedListSent));
	if (list == NULL) //error - no memory
		return NULL;

	list->sentinel = malloc(sizeof(node));
	if (list->sentinel == NULL) { //error - no memory
		free(list);
		return NULL;
	}

	list->sentinel->next = NULL;
	list->sentinel->value = 0;

	list->begin = list->sentinel;
	return list;
}

/** Destroy the sorted list and free every element */
void sorted_list_sent_free(SortedListSent* list) {
	if (list == NULL)
		return; //nothing to free

	node* aux;
	while(list->begin != NULL) {
		aux = list->begin->next;
		free(list->begin);
		list->begin = aux;
 	}

 	free(list);
}

/**
 * Internal search of the list: the value arguments "prev" and "actual" are
 * changed, according to the value searched
 */
void internal_search_sentinel(SortedListSent* list, Elem value, node** prev, node** actual) {
	*prev = NULL;
	*actual = list->begin;
	list->sentinel->value = value;

	// iterates until a greater or equal value is found on the list
	while((*actual)->value < value) {
		*prev = *actual;
		*actual = (*actual)->next;
	}
}

/** Search for a element into the list */
bool sorted_list_sent_search(SortedListSent* list, Elem value) {
	node *prev, *actual;
	internal_search_sentinel(list, value, &prev, &actual); //call internal search

	// Return whether the element is found and isn't the sentinel
	return actual != list->sentinel && actual->value == value;
}

/** Insert a element in the list */
void sorted_list_sent_insert(SortedListSent *list, Elem value) {
	node *prev, *actual, *new;

	// Call internal search to see where the element will be inserted
	internal_search_sentinel(list, value, &prev, &actual);

	if (actual != list->sentinel && actual->value == value)
		return; //repeated element

	// insert the element
	new = malloc(sizeof(node));
	if (new == NULL) return; //no space

	new->value = value;
	new->next = actual;

	// update pointers
	if (prev == NULL)
		list->begin = new;
	else
		prev->next = new;
}

/** Remove a element from the list */
int sorted_list_sent_remove(SortedListSent* list, Elem value) {
	node *prev, *actual;
	internal_search_sentinel(list, value, &prev, &actual);

	if (actual == list->sentinel || actual->value != value)
		return -1; //element not found on the list

	// update pointers
	if (prev == NULL)
		list->begin = actual->next;
	else
		prev->next = actual->next;

	free(actual);
	return 0;
}

/** Print every element of the list; DEBUG ONLY */
int sorted_list_sent_printf(SortedListSent* list) {
	node* aux = list->begin;
	while(aux != list->sentinel) {
		printf("%d ", aux->value);
		aux = aux->next;
	}
	return printf("\n");
}
