#include "queue.h"

#include <stdlib.h>
#include <string.h>

#include "error.h"

typedef struct _Elem {
    void * value;
    struct _Elem *next, *prev;
} Elem;

struct _Queue {
    Elem *head, *tail;
    size_t elem_size;
};

Queue * queue_new(Queue * q, size_t elem_size) {
    if (q == NULL) {
        q = (Queue *) malloc(sizeof(Queue));
    }

    //initial values
    q->elem_size = elem_size;
    q->head = NULL;
    q->tail = NULL;

    return q;
}

void queue_free(Queue * q) {
    if (q == NULL) {
        return;
    }
    //remove the elements
    Error erro;
    while (! queue_empty(q)) {
        queue_pop(q, &erro);
    }
    free(q);
}

void queue_push(Queue * q, const void * value, Error * error) {
	//push to the queue
    Elem * new_elem = (Elem *) malloc(sizeof(Elem));
    new_elem->value = malloc(q->elem_size);
    memcpy(new_elem->value, value, q->elem_size);

    new_elem->next = NULL;
    new_elem->prev = NULL;
    
    if (q->tail == NULL) { //first element
        q->head = new_elem;
        q->tail = new_elem;
    } else {
        new_elem->next = q->tail;
        q->tail->prev = new_elem;
        q->tail = new_elem;
    }

    error->occurred = false;
}

void * queue_top(const Queue * q) {

    if (queue_empty(q)) {
        return NULL; //there is nothing to remove
    } else {
        return q->head->value;
    }
}

void queue_pop(Queue * q, Error * error) {

    if (q->head == NULL) { //queue is empty
        error->occurred = true;
        strcpy(error->msg, "Cannot pop from empty queue.");
    } else {
        Elem * n = q->head->prev;
        free(q->head->value);
        free(q->head);
        q->head = n;
    }
}

bool queue_empty(const Queue * q) {
    return q->head == NULL;
}
