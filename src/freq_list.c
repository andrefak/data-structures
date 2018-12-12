#include "freq_list.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/** Structure of each node */
typedef struct node {
	Elem value;
	struct node *next, *prev;
} node;

/** Structure of the frequency list */
struct _freqList {
	node *begin, *end;
};

/** Create a Frequency List, and return it */
FreqList* freq_list_create() {
	FreqList* list = malloc(sizeof(FreqList));
	if (list == NULL)
		return NULL;

	list->begin = list->end = NULL;
	return list;
}

/** Destroy the frequency list and free every element */
void freq_list_free(FreqList* list) {
	if (list == NULL) //nothing to free
		return;

	//free everything
	node* aux;
	while(list->begin != list->end) {
		aux = list->begin->next;
		free(list->begin);
		list->begin = aux;
	}
	free(list->end);

	free(list);
}

/** Search for a element into the list, and update the order */
bool freq_list_search(FreqList* list, Elem value) {
	node *n;
	n = list->begin;

	while(n != list->end && n->value != value)
		n = n->next;
	if (n == list->end && n != NULL && n->value != value)
		n = NULL;

	if (n == NULL)
		return false;

	// shift one position towards the beginning
	if (n != list->begin && n->prev != n) {
		int aux = n->prev->value;
		n->prev->value = n->value;
		n->value = aux;
	}

	return true;
}

/** Insert a element in the list */
void freq_list_insert(FreqList *list, Elem value) {
	node* new = malloc(sizeof(node));
	if (new == NULL)
		return; //no space

	new->value = value;

	//update pointers and values
	if (list->begin == NULL) {
		list->begin = list->end = new;
		new->next = new->prev = new;
	} else {
		list->end->next = new;
		new->prev = list->end;
		new->next = list->begin;
		list->end = new;
	}
}

/** Remove a element from the list */
int freq_list_remove(FreqList* list, Elem value) {

	//find the element to be removed
	node* n = list->begin;
	while (n != NULL && n != list->end && n->value != value)
		n = n->next;

	if (n == NULL || (n == list->end && n->value != value))
		return -1; //element not found
	
	//update pointers
	node* aux;
	if (list->begin == list->end)
		list->begin = list->end = NULL;	
	else if (n == list->begin) {
		aux = n->next;
		list->end->next = aux;
		aux->prev = list->end;
		list->begin = aux;
	} else if (n == list->end) {
		aux = n->prev;
		list->end = aux;
		aux->next = list->begin;
		list->begin->prev = aux;
	} else {
		aux = n->prev;
		aux->next = n->next;
		n->next->prev = n->prev;
	}

	//remove
	free(n);
	return 0;
}

/** Print every element of the list; DEBUG ONLY */
int freq_list_printf(FreqList* list) {
	node* aux = list->begin;
	while(aux != list->end) {
		printf("%d ", aux->value);
		aux = aux->next;
	}
	if (aux != NULL) printf("%d", aux->value);
	return printf("\n");
}
