#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#include "error.h"

#ifdef STATIC
    #include <stdint.h>
    
    #define QUEUE_MAX_SIZE (1024*32)
    struct _Queue {
        int8_t elem[QUEUE_MAX_SIZE];
        size_t head;
        size_t tail;
        size_t elem_size;
        size_t size;
    };
#endif

typedef struct _Queue Queue;

/** Creates an empty queue with the specified element size (in bytes). */
Queue * queue_new(Queue * pre_allocated, size_t elem_size);

/** Frees the memory of the queue and its elements. */
void queue_free(Queue * queue);

/** 
 * Puts a copy of `value` at the end of the queue.
 * 
 * If the queue is size limited, fills an error when the queue is full.
 */
void queue_push(Queue * queue, const void * value, Error * error);

/**
 * Pops the first element of the queue.
 * 
 * Fills an error in 'error' if the queue is empty.
 */
void queue_pop(Queue * queue, Error * error);

/**
 * Returns a pointer to first element of the queue.
 * 
 * Returns NULL if the queue is empty.
 */
void * queue_top(const Queue * q);

/** Tells whether the queue is empty. */
bool queue_empty(const Queue * q);

#endif
