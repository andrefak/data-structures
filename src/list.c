#include "list.h"
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
	void* value;
	struct _Node* next;
} Node;

struct _List {
	Node *begin, *end;
	size_t elem_size;
	size_t size;
};

List * list_create(List * list, size_t elem_size) {
	if (list == NULL) {
		list = (List*) malloc(sizeof(List));
	}

	//initial values
	
	list->begin = list->end = NULL;
	list->elem_size = elem_size;
	list->size = 0;

	return list;
}

void list_free(List* l) {
	//remove the elements
	if (l != NULL) {
		while (l->begin != NULL) {
			list_remove(l, 1);
		}
		l->begin = l->end = NULL;
		free(l);
	}
}

void list_push(List* l, void* value) {
	Node* n = (Node*) malloc(sizeof(Node));

	n->value = (void*) malloc(l->elem_size);
	memcpy(n->value, value, l->elem_size);

	if (l->begin == NULL) {
		l->begin = n;
	} else {
		l->end->next = n;
	}

	l->end = n;
	n->next = l->begin;

	l->size++;
}

void* list_get(List* l, size_t pos) {
	Node* n = l->begin;

	for (size_t count = 0; count < pos && n != NULL; count++) {
		n = n->next;
		if (n == l->begin) {
			return NULL;
		}
	}

	return n->value;
}

void list_remove(List* l, size_t pos) {

	Node* n = l->begin;
	Node* prev = NULL;
	
	//find the node of position
	for (size_t count = 0; count < pos && n != NULL; count++) {
		prev = n;
		n = n->next;
		if (n == l->begin) {
			n = NULL;
			break;
		}
	}

	if (n == NULL) { //didn't find
		return;
	}

	if (prev == NULL) { //first element
		l->begin = n->next;
	} else {
		prev->next = n->next;
	}
	
	if (n == l->end) { //last element
		if (prev != NULL) {
			l->end = prev;
		} else {
			l->end = l->begin;
		}
	}

	l->end->next = l->begin;

	l->size--;

	if (l->size == 0) {
		l->begin = l->end = NULL;
	}

	free(n->value);
	free(n);
}

bool list_empty(List* l) {
	return l->size == 0;
}

size_t list_size(List * l) {
	return l->size;
}
