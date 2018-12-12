#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stdlib.h>

#include "common.h"

typedef struct _bst BST;

/** Create a Binary Search Tree and return it */
BST* bst_create();

/** Destroy the BST and free every element */
void bst_free(BST* tree);

/** Search for an element in the tree */
bool bst_search(BST* tree, Elem value);

/** Insert an element in the tree */
void bst_insert(BST *tree, Elem value);

/** Remove an element from the tree */
int bst_remove(BST* tree, Elem value);

/** Print all the elements of the tree; DEBUG ONLY */
int bst_printf(BST* tree);

#endif
