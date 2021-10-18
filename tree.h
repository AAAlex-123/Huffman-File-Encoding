#include "map.h"

typedef struct {

	int dummy;

} TREE_NODE;

char* get_recursive(TREE_NODE* tree_node, char* key);

typedef struct {

	int dummy;

} MIN_HEAP;

// add and keep heap properties
void add(MIN_HEAP* heap, char* value);

// remove min and keep heap properties
char* remove_min(MIN_HEAP* heap);

