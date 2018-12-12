#ifndef FREQ_LIST_H
#define FREQ_LIST_H

#include <stdbool.h>
#include <stdlib.h>

#include "common.h"

typedef struct _freqList FreqList;

/** Create a Frequency List, and return it */
FreqList* freq_list_create();

/** Destroy the frequency list and free every element */
void freq_list_free(FreqList* list);

/** Search for a element into the list */
bool freq_list_search(FreqList* list, Elem value);

/** Insert a element in the list */
void freq_list_insert(FreqList *list, Elem value);

/** Remove a element from the list */
int freq_list_remove(FreqList* list, Elem value);

/** Print every element of the list; DEBUG ONLY */
int freq_list_printf(FreqList* list);

#endif
