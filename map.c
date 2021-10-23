#include <stddef.h>

#include "map.h"

struct MAP* create_map(int buckets) {
	struct MAP* map = malloc(sizeof(struct MAP));
	map->bucket_count = buckets;
	map->buckets = malloc(buckets * sizeof(struct LIST*));
	return map;
}

// put if not exists, update otherwise
void put(struct MAP* map, char* key, char* value) {
	struct LIST* bucket = map->buckets[hash(key)];
	if (get(map, key) == NULL) {
		append(bucket, create_node(key, value));
	}
	else {
		for (struct LIST_NODE* curr = bucket->head; curr != NULL; curr = curr->next)
			if (strcmp(curr->key, key) == 0)
				curr->value = value;
	}
}

// get if exists, NULL otherwise
char* get(struct MAP* map, char* key) {
	struct LIST* bucket = map->buckets[hash(key)];
	for (struct LIST_NODE* curr = bucket->head; curr != NULL; curr = curr->next)
		if (strcmp(curr->key, key) == 0)
			return curr->value;
	return NULL;
}

int hash(char* key) {
	int hash = 7;
	for (int i = 0, length=strlen(key); i < length; ++i) {
		hash = hash * 31 + key[i];
	}
	return hash;
}

struct LIST_NODE* create_node(char* key, char* value) {
	struct LIST_NODE* node = malloc(sizeof(struct LIST_NODE));
	node->key = key;
	node->value = value;
	node->next = NULL;
	return node;
}

// append
void append(struct LIST* list, struct LIST_NODE* node) {
	struct LIST_NODE* curr;
	for (curr = list->head; curr != NULL; curr = curr->next)
		;

	curr->next = node;
}

// get if exists, NULL otherwise
struct LIST_NODE* get(struct LIST* list, char* key) {
	for (struct LIST_NODE* curr = list->head; curr != NULL; curr = curr->next)
		if (strcmp(curr->key, key) == 0)
			return curr;
	return NULL;
}

