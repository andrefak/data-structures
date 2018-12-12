#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdlib.h>

#include "error.h"

#ifdef STATIC
    #include <stdint.h>

    struct _Stack {
        int8_t elem[1024*32];
        size_t elem_size;
        size_t max_size;
        size_t size;
    };
#endif

typedef struct _Stack Stack;

/** Creates a stack with the specified element size and maximum number of elements. */
Stack * stack_create(Stack * stack, size_t elem_size, size_t max_elems);

/** Frees the memory used by the stack. */
void stack_free(Stack * stack);

/**
 * Pushes a copy of value into the top of the stack.
 * 
 * Fills an error in 'error' if the stack is full.
 */
void stack_push(Stack * stack, void * value, Error * error);

/**
 * Pops the top of the stack.
 * 
 * Fills an error in 'error' if the stack is empty.
 */
void stack_pop(Stack * stack, Error * error);

/** Returns a pointer to the value that is on the top of the stack */
void * stack_top(const Stack * stack);

/** Tell whether the stack is full. */
bool stack_full(const Stack * stack);

/** Tells whether the stack is empty. */
bool stack_empty(const Stack * stack);

/** Returns the number of items in the stack. */
size_t stack_size(const Stack * stack);

#endif
