#ifndef SORTED_LIST_SENTINEL_H
#define SORTED_LIST_SENTINEL_H

#include <stdbool.h>
#include <stdlib.h>

#include "common.h"

typedef struct _SortedListSent SortedListSent;

/** Create a Sorted List with Sentinel, and return it */
SortedListSent* sorted_list_sent_create();

/** Destroy the sorted list and free every element */
void sorted_list_sent_free(SortedListSent* list);

/** Search for a element into the list */
bool sorted_list_sent_search(SortedListSent* list, Elem value);

/** Insert a element in the list */
void sorted_list_sent_insert(SortedListSent *list, Elem value);

/** Remove a element from the list */
int sorted_list_sent_remove(SortedListSent* list, Elem value);

/** Print every element of the list; DEBUG ONLY */
int sorted_list_sent_printf(SortedListSent* list);

#endif