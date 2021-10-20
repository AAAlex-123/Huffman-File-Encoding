#include "map.h"
#include <cstddef>

struct TREE_NODE;

typedef struct {

	int depth;
	TREE_NODE* left, right;

	char* value;
	int frequency;

} TREE_NODE;

TREE_NODE* make_node(TREE_NODE* n1, TREE_NODE* n2) {

	TREE_NODE* newnode = malloc(sizeof(TREE_NODE));

	newnode->depth = n1->depth;
	newnode->left = n1;
	newnode->right = n2;
	newnode->value = NULL;
	newnode->frequency = n1->frequency + n2->frequency;

	n1->depth += 1;
	n2->depth += 1;

	return newnode;
}

typedef struct {

	int size;

} MIN_HEAP;

// add and keep heap properties
void add(MIN_HEAP* heap, TREE_NODE* value);

// remove min and keep heap properties
TREE_NODE* remove_min(MIN_HEAP* heap);

