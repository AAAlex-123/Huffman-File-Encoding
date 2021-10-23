#include <stddef.h>
#include "tree.h"

struct TREE_NODE* combine_nodes(struct TREE_NODE* n1, struct TREE_NODE* n2) {

	struct TREE_NODE* newnode = malloc(sizeof(struct TREE_NODE));

	newnode->depth = n1->depth + 1;
	newnode->left = n1;
	newnode->right = n2;
	newnode->value = NULL;
	newnode->frequency = n1->frequency + n2->frequency;

	return newnode;
}

struct MIN_HEAP* make_heap(int capacity) {
	struct MIN_HEAP *heap = malloc(sizeof(struct MIN_HEAP));
	heap->size = 0;
	heap->max_capacity = capacity;
	heap->nodes = malloc((capacity + 1) * sizeof(struct TREE_NODE));
	return heap;
}

void add_node(struct MIN_HEAP* heap, struct TREE_NODE* value) {
	if (heap->size == heap->max_capacity) {
		heap->max_capacity *= 2;
		struct TREE_NODE* new_nodes = malloc((heap->max_capacity + 1) * sizeof(struct TREE_NODE));
		memcpy(new_nodes, heap->nodes, heap->size + 1);
		heap->nodes = new_nodes;
	}

	heap->nodes[heap->size + 1] = *value;

	// float to the top
	int curr = heap->size + 1;
	while (curr > 1 && heap->nodes[curr].frequency < heap->nodes[curr / 2].frequency) {
		struct TREE_NODE temp = heap->nodes[curr / 2];
		heap->nodes[curr / 2] = heap->nodes[curr];
		heap->nodes[curr] = temp;
		curr /= 2;
	}

	heap->size++;
}

struct TREE_NODE* remove_min(struct MIN_HEAP* heap) {
	struct TREE_NODE* removed = &heap->nodes[1];
	heap->nodes[1] = heap->nodes[heap->size];

	// swim to the bottom
	int curr = 1;
	while (curr < heap->size && heap->nodes[curr].frequency > heap->nodes[curr * 2].frequency) {
		struct TREE_NODE temp = heap->nodes[curr * 2];
		heap->nodes[curr * 2] = heap->nodes[curr];
		heap->nodes[curr] = temp;
		curr *= 2;
	}

	heap->size--;
	return removed;
}

