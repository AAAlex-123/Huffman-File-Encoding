#include <stddef.h>
#include "tree.h"

TREE_NODE* combine_nodes(TREE_NODE* n1, TREE_NODE* n2) {

	TREE_NODE* newnode = malloc(sizeof(TREE_NODE));

	newnode->depth = n1->depth + 1;
	newnode->left = n1;
	newnode->right = n2;
	newnode->value = NULL;
	newnode->frequency = n1->frequency + n2->frequency;

	return newnode;
}

MIN_HEAP* make_heap(int capacity) {
	MIN_HEAP *heap = malloc(sizeof(MIN_HEAP));
	heap->size = 0;
	heap->max_capacity = capacity;
	heap->nodes = malloc((capacity + 1) * sizeof(TREE_NODE));
	return heap;
}

void add_node(MIN_HEAP* heap, TREE_NODE* value) {
	if (heap->size == heap->max_capacity) {
		heap->max_capacity *= 2;
		TREE_NODE* new_nodes = malloc((heap->max_capacity + 1) * sizeof(TREE_NODE));
		memcpy(new_nodes, heap->nodes, heap->size + 1);
		heap->nodes = new_nodes;
	}

	heap->nodes[heap->size + 1] = *value;

	// float to the top
	int curr = heap->size + 1;
	while (curr > 1 && heap->nodes[curr].frequency < heap->nodes[curr / 2].frequency) {
		TREE_NODE temp = heap->nodes[curr / 2];
		heap->nodes[curr / 2] = heap->nodes[curr];
		heap->nodes[curr] = temp;
		curr /= 2;
	}

	heap->size++;
}

TREE_NODE* remove_min(MIN_HEAP* heap) {
	TREE_NODE* removed = &heap->nodes[1];
	heap->nodes[1] = heap->nodes[heap->size];

	// swim to the bottom
	int curr = 1;
	while (curr < heap->size && heap->nodes[curr].frequency > heap->nodes[curr * 2].frequency) {
		TREE_NODE temp = heap->nodes[curr * 2];
		heap->nodes[curr * 2] = heap->nodes[curr];
		heap->nodes[curr] = temp;
		curr *= 2;
	}

	heap->size--;
	return removed;
}

