#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdlib.h>

#ifdef STATIC
    #include <stdint.h>

    #define LIST_MAX_SIZE (1024*32)
    
    struct _List {
        int8_t elem[LIST_MAX_SIZE];
        size_t elem_size;
        size_t size;
    };
#endif

typedef struct _List List;

/** Creates an empty list with the specified element size (in bytes). */
List * list_create(List * list, size_t elem_size);

/** Destroy a list and free its elements. */
void list_free(List * list);

/** Push an element to the list. */
void list_push(List * list, void* value);

/** Returns a pointer to the element in the given position (0-based). */
void* list_get(List * list, size_t pos);

/** Removes from the list the element in the given position (0-based). */
void list_remove(List * list, size_t pos);

/** Returns true if the list is empty, and false otherwise. */
bool list_empty(List * l);

/** Returns the number of items currently in the list. */
size_t list_size(List * l);

#endif
