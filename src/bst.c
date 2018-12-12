#include "bst.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/** Structure of each node */
typedef struct node {
	Elem value;
	struct node *left, *right;
} node;

/** Structure of the BST */
struct _bst {
	node *root;
};

/** Create a Binary Search Tree and return it */
BST* bst_create() {
	BST* tree = malloc(sizeof(BST));
	if (tree == NULL)
		return NULL;

	tree->root = NULL;
	return tree;
}

/** Internal call of the free function; works recursively */
static void internal_bst_free(node* n) {
	if (n == NULL) return;

	//free the children, then itself
	internal_bst_free(n->left);
	internal_bst_free(n->right);
	free(n);
}

/** Destroy the BST and free every element */
void bst_free(BST* tree) {
	if (tree == NULL)
		return; //nothing to free
	internal_bst_free(tree->root);
	free(tree);
}

/** Internal call of the search function; works by recursion */
static bool internal_bst_search(node* n, Elem value) {
	if (n == NULL)
		return false;

	if (n->value == value) //element found
		return true;

	//the element must be on the left or right child
	if (value < n->value)
		return internal_bst_search(n->left, value);
	if (value > n->value)
		return internal_bst_search(n->right, value);
	return false;
}

/** Searches for an element in the tree */
bool bst_search(BST* tree, Elem value) {
	if (tree == NULL) return false;
	return internal_bst_search(tree->root, value);
}

/** Internal call of the insertion function */
static void internal_bst_push(node** n, Elem value) {
	if (*n == NULL) { //insert and update pointers
		*n = malloc(sizeof(node));
		if (*n == NULL) return;
		(*n)->value = value;
		(*n)->left = (*n)->right = NULL;
	} else {
		//finding the right place to insert
		if (value < (*n)->value)
			internal_bst_push(&((*n)->left), value);
		else if (value > (*n)->value)
			internal_bst_push(&((*n)->right), value);
		else return;
	}
}

/** Insert an element in the tree */
void bst_insert(BST *tree, Elem value) {
	if (tree != NULL)
		internal_bst_push(&(tree->root), value);
}

/** Internal call of the remove function */
static void internal_bst_remove(node** n, Elem value) {
	int childNum = 0;
	node *aux, *parAux;

	if (*n == NULL) return; //nothing to remove

	if ((*n)->value == value) { //remove
		if ((*n)->left != NULL) childNum++; //increases the number of children
		if ((*n)->right != NULL) childNum++;
		switch (childNum) {
			case 0: //the node is a leaf
				free(*n);
				*n = NULL;
				break;
			case 1: //the node has only one child
				aux = *n;
				*n = ((*n)->left != NULL) ? (*n)->left : (*n)->right;
				free(aux);
				break;
			case 2:
				//the node has two children: must be replaced by the greatest element of the left subtree
				aux = (*n)->left;
				parAux = *n;
				while (aux->right != NULL) {
					parAux = aux;
					aux = aux->right;
				}

				(*n)->value = aux->value;
				if (parAux->left == aux) internal_bst_remove(&(parAux->left), aux->value);
				else internal_bst_remove(&(parAux->right), aux->value);
				break;
		}
	} else { //finding the element to remove
		if (value < (*n)->value)
			internal_bst_remove(&((*n)->left), value);
		else
			internal_bst_remove(&((*n)->right), value);
	}

}

/** Remove an element from the tree */
int bst_remove(BST* tree, Elem value) {
	internal_bst_remove(&(tree->root), value);
	return 0;
}

/** Recursive function to print the elements */
static void internal_bst_print(node* n) {
	if (n == NULL) return;
	internal_bst_print(n->left);
	printf("%d ", n->value);
	internal_bst_print(n->right);
}

/** Print all the elements of the tree; DEBUG ONLY */
int bst_printf(BST* tree) {
	internal_bst_print(tree->root);
	return printf("\n");
}