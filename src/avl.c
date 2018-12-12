#include "avl.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

/** Struct of each node of the tree */
typedef struct node {
	Elem value;
	struct node *left, *right;
	int8_t bal_factor;
	int8_t height;
} node;

/** Struct of the AVL tree */
struct _avl {
	node *root;
};

/** Create an AVL and return it */
AVL* avl_create() {
	AVL* tree = malloc(sizeof(AVL));
	if (tree == NULL) //no memory available
		return NULL;

	tree->root = NULL;
	return tree;
}

/** Internal part of the free function */
void internal_avl_free(node* n) {
	if (n == NULL)
		return; //nothing to free

	//free the children, then itself
	internal_avl_free(n->left);
	internal_avl_free(n->right);
	free(n);
}

/** Destroy the tree and free the alloc'd memory */
void avl_free(AVL* tree) {
	if (tree == NULL) return;
	internal_avl_free(tree->root); //call the internal function
	free(tree); //free the avl block
}

/** Internal part of the search function; works by recursion */
bool internal_avl_search(node* n, Elem value) {
	if (n == NULL) //out of bounds
		return false;

	if (n->value == value) //element found
		return true;

	/** the element must be on the left or right child */
	if (value < n->value)
		return internal_avl_search(n->left, value);
	if (value > n->value)
		return internal_avl_search(n->right, value);

	return false;
}

/** Search for an element in the tree */
bool avl_search(AVL* tree, Elem value) {
	if (tree == NULL) return false;
	return internal_avl_search(tree->root, value);
}

static int8_t calc_height(node *n) {
	int8_t left = n->left != NULL ? n->left->height : (int8_t)-1;
	int8_t right = n->right != NULL ? n->right->height : (int8_t)-1;
	return (int8_t) 1 + (left > right ? left : right);
}

static int8_t calc_balance_factor(node *n) {
	int8_t left = n->left != NULL ? n->left->height : (int8_t)-1;
	int8_t right = n->right != NULL ? n->right->height : (int8_t)-1;
	return right - left;
}

/**
 *    |             |
 *    A             B
 *   / \           / \
 *  c   B    =>   A   e
 *     / \       / \  e
 *    d   e     c   d e
 *        e
 *        e
 *
 * where:
 * 	 - A is the node p has a pointer to
 * 	 - height(e) >= height(d)
 */
static void rotate_left(node **p) {
	node *A = *p;
	node *B = A->right;

	A->right = B->left;
	B->left = A;
	*p = B;

	A->height = calc_height(A);
	B->height = calc_height(B);
	A->bal_factor = calc_balance_factor(A);
	B->bal_factor = calc_balance_factor(B);
}

/**
 *     |           |
 *     A           B
 *    / \         / \
 *   B   e  =>   c   A
 *  / \          c  / \
 * c   d         c d   e
 * c
 * c
 *
 * where:
 * 	 - A is the node p has a pointer to
 * 	 - height(c) >= height(d)
 */
static void rotate_right(node **p) {
	node *A = *p;
	node *B = A->left;

	A->left = B->right;
	B->right = A;
	*p = B;

	A->height = calc_height(A);
	B->height = calc_height(B);
	A->bal_factor = calc_balance_factor(A);
	B->bal_factor = calc_balance_factor(B);
}

/** Left Right Rotation */
static void rotate_left_right(node **p) {
	rotate_left(&((*p)->left));
	rotate_right(p);
}

/** Right Left rotation */
static void rotate_right_left(node **p) {
	rotate_right(&((*p)->right));
	rotate_left(p);
}

static void rebalance(node *n, node **parent) {
	n->height = calc_height(n);
	n->bal_factor = calc_balance_factor(n);

	if (n->bal_factor == +2 && n->right->bal_factor >= 0) {
		rotate_left(parent);
	} else if (n->bal_factor == +2 && n->right->bal_factor == -1) {
		rotate_right_left(parent);
	} else if (n->bal_factor == -2 && n->left->bal_factor <= 0) {
		rotate_right(parent);
	} else if (n->bal_factor == -2 && n->left->bal_factor == +1) {
		rotate_left_right(parent);
	}
}

/** Create a node with specified info */
node* createNode(Elem value, node *left, node *right, int8_t bal_factor, int8_t height) {
	node* new = malloc(sizeof(node));
	if (new == NULL) return NULL; // TODO return error

	new->value = value;
	new->left = left;
	new->right = right;
	new->bal_factor = bal_factor;
	new->height = height;

	return new;
}

/** Internal part of the insertion */
static void internal_avl_insert(node **n, Elem value) {
	if (*n == NULL) { // insert
		*n = createNode(value, NULL, NULL, 0, 0);
	} else {
		if (value < (*n)->value) {
			// element must be inserted on the left child
			internal_avl_insert(&((*n)->left), value);
			rebalance(*n, n);
		} else if (value > (*n)->value) {
			// element must be inserted on the right child
			internal_avl_insert(&((*n)->right), value);
			rebalance(*n, n);
		} else {
			return; // element is already in the tree
		}
	}
}

/** Insert an element into the tree */
void avl_insert(AVL *tree, Elem value) {
	if (tree != NULL)
		internal_avl_insert(&(tree->root), value);
}

static void internal_avl_remove(node** n, Elem value) {
	int childNum = 0;
	node *aux, *parAux;

	if (*n == NULL) return;

	if ((*n)->value == value) { // remove

		if ((*n)->left != NULL) childNum++;
		if ((*n)->right != NULL) childNum++;
		switch (childNum) {
			case 0:
				free(*n);
				*n = NULL;
				break;
			case 1:
				aux = *n;
				*n = ((*n)->left != NULL) ? (*n)->left : (*n)->right;
				free(aux);
				rebalance(*n, n);
				break;
			case 2:
				aux = (*n)->left;
				parAux = *n;

				while (aux->right != NULL) {
					parAux = aux;
					aux = aux->right;
				}

				(*n)->value = aux->value;
				if (parAux->left == aux) {
					internal_avl_remove(&(parAux->left), aux->value);
					rebalance(*n, n);
				} else {
					internal_avl_remove(&(parAux->right), aux->value);
					rebalance(*n, n);
				}
				break;
		}
	} else {
		if (value < (*n)->value) {
			internal_avl_remove(&((*n)->left), value);
			rebalance(*n, n);
		} else {
			internal_avl_remove(&((*n)->right), value);
			rebalance(*n, n);
		}
	}
}

/** Remove an element from the tree */
int avl_remove(AVL* tree, Elem value) {
	internal_avl_remove(&(tree->root), value);
	return 0;
}

/** Internal call of print function */
static void internal_avl_print(node* n) {
	if (n == NULL) return;

	printf("(");
	internal_avl_print(n->left);
	printf(" %d[%d] ", n->value, n->bal_factor);
	internal_avl_print(n->right);
	printf(")");
}

/** Print all the elements of the AVL (in order); DEBUG ONLY */
int avl_printf(AVL* tree) {
	internal_avl_print(tree->root);
	return printf("\n");
}
