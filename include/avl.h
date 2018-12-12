#ifndef AVL_H
#define AVL_H

#include <stdbool.h>
#include <stdlib.h>

#include "common.h"

typedef struct _avl AVL;

/** Create an AVL and return it */
AVL* avl_create();

/** Destroy the tree and free the alloc'd memory */
void avl_free(AVL* tree);

/** Search for an element in the tree */
bool avl_search(AVL* tree, Elem value);

/** Insert an element into the tree */
void avl_insert(AVL *tree, Elem value);

/** Remove an element from the tree */
int avl_remove(AVL* tree, Elem value);

/** Print all the elements of the AVL (in order); DEBUG ONLY */
int avl_printf(AVL* tree);

#endif