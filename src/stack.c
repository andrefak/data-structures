#include "stack.h"

#include <stdlib.h>
#include <string.h>

#include "error.h"

typedef struct _Node {
	void * value;
	struct _Node * next;
} Node;

struct _Stack {
	Node * top;
	size_t elem_size;
	size_t max_size;
	size_t size;
};

//creates the stack
Stack * stack_create(Stack * s, size_t elem_size, size_t max_elems) {
	if (s == NULL) {
		s = (Stack*) malloc(sizeof(Stack));
	}

	s->top = NULL;
	s->elem_size = elem_size;
	s->max_size = max_elems;
	s->size = 0;

	return s;
}

void stack_free(Stack * stack) {
	if (stack != NULL) {
		//remove the elements of the stack
		while (!stack_empty(stack)) {
			Error error;
			stack_pop(stack, &error);
		}

		free(stack);
	}
}

void stack_pop(Stack * stack, Error * error) {
	if (stack_empty(stack)) { //stack is empty
		error->occurred = true;
		strcpy(error->msg, "Cannot pop from empty stack.");
		return;
	}

	Node * old = stack->top; //aux node

	stack->top = old->next; //change the top
	stack->size--;

	free(old->value);
	free(old);
}

void stack_push(Stack * stack, void * value, Error * error) {

	if (stack_full(stack)) { //stack is full
		error->occurred = true;
		strcpy(error->msg, "Cannot push to full stack.");
		return;
	}

	Node * new = (Node*) malloc(sizeof(Node));

	new->value = (void*) malloc(stack->elem_size);
	memcpy(new->value, value, stack->elem_size);
	new->next = stack->top;

	stack->top = new;
	stack->size++;
}

void * stack_top(const Stack * stack) {
	if (stack_empty(stack)) { //there is no top to return
		return NULL;
	} else {
		return stack->top->value;
	}
}

bool stack_full(const Stack * s) {
	return s->size == s->max_size;
}

bool stack_empty(const Stack * s) {
	return s->size == 0;
}

size_t stack_size(const Stack * s) {
	return s->size;
}
