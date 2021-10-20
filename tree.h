#include "map.h"

struct TREE_NODE;

typedef struct {

	int depth;
	TREE_NODE* left, right;

	char* value;
	int frequency;

} TREE_NODE;

typedef struct {

	int dummy;

} MIN_HEAP;

// add and keep heap properties
void add(MIN_HEAP* heap, char* value);

// remove min and keep heap properties
char* remove_min(MIN_HEAP* heap);

