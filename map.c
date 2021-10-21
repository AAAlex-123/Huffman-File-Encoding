#include <stddef.h>

#include "map.h"

MAP* create_map(int buckets) {
	MAP* map = malloc(sizeof(MAP));
	map->bucket_count = buckets;
	map->buckets = malloc(buckets * sizeof(LIST*));
	return map;
}

// put if not exists, update otherwise
void put(MAP* map, char* key, char* value) {
	LIST* bucket = map->buckets[hash(key)];
	if (get(map, key) == NULL) {
		append(bucket, create_node(key, value));
	}
	else {
		for (LIST_NODE* curr = bucket->head; curr != NULL; curr = curr->next)
			if (strcmp(curr->key, key) == 0)
				curr->value = value;
	}
}

// get if exists, NULL otherwise
char* get(MAP* map, char* key) {
	LIST* bucket = map->buckets[hash(key)];
	for (LIST_NODE* curr = bucket->head; curr != NULL; curr = curr->next)
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

LIST_NODE* create_node(char* key, char* value) {
	LIST_NODE* node = malloc(sizeof(LIST_NODE));
	node->key = key;
	node->value = value;
	node->next = NULL;
	return node;
}

// append
void append(LIST* list, LIST_NODE* node) {
	LIST_NODE* curr;
	for (curr = list->head; curr != NULL; curr = curr->next)
		;

	curr->next = node;
}

// get if exists, NULL otherwise
LIST_NODE* get(LIST* list, char* key) {
	for (LIST_NODE* curr = list->head; curr != NULL; curr = curr->next)
		if (strcmp(curr->key, key) == 0)
			return curr;
	return NULL;
}

