#include "map.h"

struct TREE_NODE {

	int depth;
	struct TREE_NODE* left, *right;

	char* value;
	int frequency;
};

struct TREE_NODE* combine_nodes(struct TREE_NODE* n1, struct TREE_NODE* n2);

struct MIN_HEAP {

	int size, max_capacity;
	struct TREE_NODE* nodes;
};

// initialise nodes array
struct MIN_HEAP* make_heap(int capacity);

// add and keep heap properties
void add_node(struct MIN_HEAP* heap, struct TREE_NODE* value);

// remove min and keep heap properties
struct TREE_NODE* remove_min(struct MIN_HEAP* heap);

