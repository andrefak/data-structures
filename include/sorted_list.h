#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdbool.h>
#include <stdlib.h>

#include "common.h"

typedef struct _SortedList SortedList;

/** Create a Sorted List, and return it */
SortedList* sorted_list_create();

/** Destroy the sorted list and free every element */
void sorted_list_free(SortedList* list);

/** Search for a element into the list */
bool sorted_list_search(SortedList* list, Elem value);

/** Insert a element in the list */
void sorted_list_insert(SortedList *list, Elem value);

/** Remove a element from the list */
int sorted_list_remove(SortedList* list, Elem value);

/** Print every element of the list; DEBUG ONLY */
int sorted_list_printf(SortedList* list);

#endif
