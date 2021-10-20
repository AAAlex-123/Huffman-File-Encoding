#include "map.h"

typedef struct {

	int depth;
	struct TREE_NODE* left, *right;

	char* value;
	int frequency;

} TREE_NODE;

TREE_NODE* combine_nodes(TREE_NODE* n1, TREE_NODE* n2);

typedef struct {

	int size, max_capacity;
	TREE_NODE* nodes;

} MIN_HEAP;

// initialise nodes array
MIN_HEAP* make_heap(int capacity);

// add and keep heap properties
void add_node(MIN_HEAP* heap, TREE_NODE* value);

// remove min and keep heap properties
TREE_NODE* remove_min(MIN_HEAP* heap);

