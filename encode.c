#include <stdio.h>

#include "map.h"
#include "tree.h"

char* read_file(FILE* fp);
char* encode(char* original_string);
void write_encoded(FILE* fp, char* encoded_string);

// encode(char*):
MAP* get_encoding_map(char* string);
char* encode_with_map(MAP* map, char* string);

// get_encoding_map(char*):
MAP* get_frequency_map(char* string);
TREE_NODE* make_hufhuf_tree(MAP* map);
MAP* get_map_from_tree(TREE_NODE* hufhuf_tree);

int main(int argc, char** argv) {
	printf("main with %d args:\n", argc);
	for (int i = 0; i < argc; ++i)
		printf("argv[%d]=%s", i, argv[i]);

	// read file: FILE* file -> char* contents
	FILE* infp = fopen(argv[1], "r");
	char* file_contents = read_file(infp);

	// encode: char* contents -> char* encoded contents
	char* encoded_contents = encode(file_contents);

	// write file: FILE* file, char* encoded contents -> null
	FILE* outfp = fopen("encoded_" + *argv[1], "w");
	write_encoded(outfp, encoded_contents);

	// cleanup
	fclose(infp);
	fclose(outfp);

	return 0;
}

char* read_file(FILE* fp) {
	printf("reading file '%s'", fp);

	// get size
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// allocate memory for contents
	char* buffer = malloc(size * sizeof(char));

	// read contents into buffer
	fread(buffer, sizeof(char), size, fp);

	// return buffer
	return buffer;
}

char* encode(char* original_string) {
	printf("encoding string '%s'\n", original_string);

	// get encoding map: char* orig_str -> MAP* encoding map
	MAP* encoding_map = get_encoding_map(original_string);

	// encode with map: char* orig_str -> char* encoded str
	//  - the encoding entails writing the map to the string
	char* encoded_string = encode_with_map(encoding_map, original_string);

	// return encoded string
	return encoded_string;
}

void write_encoded(FILE* fp, char* encoded_string) {
	printf("writing encoded string '%s' to file '%s'", encoded_string, fp);

	// write encoded string
	fputs(encoded_string, fp);

	return;
}

// encode

MAP* get_encoding_map(char* string) {
	printf("creating encoding map from string '%s'\n", string);

	// get frequency map of each character: char* str -> MAP* freq map
	MAP* frequency_map = get_frequency_map(string);

	// make tree with huffman stuff: MAP* freq map -> TREE* hufhuf tree
	TREE_NODE* tree = make_hufhuf_tree(frequency_map);

	// traverse tree to get each character's encoding: TREE* hufhuf tree -> MAP* encoding map
	MAP* encoding_map = get_map_from_tree(tree);

	// return map
	return encoding_map;
}

char* encode_with_map(MAP* encoding_map, char* string) {
	prtinf("encoding string '%s' with map\n", string);

	char* encoded_string = malloc(10 * sizeof(char));

	// first encode the map into the string
	for (int i = 0; i < encoding_map->bucket_count; ++i) {
		for (LIST_NODE* curr = encoding_map->buckets[i]->head; curr != NULL; curr = curr->next) {
			encoded_string = append_to_string(encoded_string, curr->key);
			encoded_string = append_to_string(encoded_string, "=");
			encoded_string = append_to_string(encoded_string, curr->value);
			encoded_string = append_to_string(encoded_string, ",");
		}
	}

	// for each character of the original string
	// get its encoding and write it to another string
	for (int i = 0, length = strlen(string); i < length; ++i)
		encoded_string = append_to_string(encoded_string, get(encoding_map, string[i]));

	printf("encoding result: '%s'\n", encoded_string);
	// return the encoded string
	return encoded_string;
}

// get_encoding_map

MAP* get_frequency_map(char* string) {
	printf("making frequency map from '%s'\n", string);

	MAP* frequency_map = create_map(15);

	// for each character of the original string
	for (int i = 0, length = strlen(string); i < length; ++i) {
		char* curr_char = string[i];

		// increment its frequency in the map
		if (get(frequency_map, curr_char) == NULL) {
			put(frequency_map, curr_char, "1");
		}
		else {
			int new_frequency = atoi(get(frequency_map, curr_char)) + 1;

			int new_str_length = new_frequency % 10;
			char* new_freq = malloc((new_str_length + 1) * sizeof(char));
			sprintf(new_freq, "%d", new_frequency);

			put(frequency_map, curr_char, new_freq);
		}
	}

	// return the map
	return frequency_map;
}

TREE_NODE* make_hufhuf_tree(MAP* freq_map) {
	printf("making hufhuf tree\n");

	MIN_HEAP* heap = make_heap(5);

	// algorithm lol
	for (int i = 0; i < freq_map->bucket_count; ++i) {
		for (LIST_NODE* curr = freq_map->buckets[i]->head; curr != NULL; curr = curr->next) {
			TREE_NODE* node = malloc(sizeof(TREE_NODE));
			node->value = curr->key;
			node->frequency = curr->value;

			add_node(heap, node);
		}
	}

	while (heap->size > 1) {
		TREE_NODE *n1, *n2, *newnode;
		n1 = remove_min(heap);
		n2 = remove_min(heap);
		newnode = combine_nodes(n1, n2);

		add_node(heap, newnode);
	}

	TREE_NODE* hufhuf_tree = remove_min(heap);

	return hufhuf_tree;
}

MAP* get_map_from_tree(TREE_NODE* hufhuf_tree) {
	printf("getting map from tree\n");

	MAP* encoding_map = create_map(15);
	char* path = malloc(hufhuf_tree->depth * sizeof(char));
	int current_depth = 0;

	dfs(hufhuf_tree, encoding_map, path, current_depth);

	// cleanup
	free(path);

	return encoding_map;
}

char* append_to_string(char* original, char* to_append) {
	printf("appending '%s' to '%s'\n", to_append, original);

	int old_length = strlen(original);
	int new_length = strlen(to_append) + old_length;
	
	char* combined = malloc((new_length + 1) * sizeof(char));
	memcpy(combined, original, old_length);
	memcpy(combined + old_length, to_append, new_length);

	return combined;
}

void dfs(TREE_NODE* hufhuf_tree, MAP* map, char* path, int depth) {
	printf("exploring: '%s', at depth %d\n", path, depth);

	// if leaf not found
	if (hufhuf_tree->value == NULL) {
		path[depth + 1] = '\0';
		// mark left and explore
		path[depth] = '0';
		dfs(hufhuf_tree->left, map, path, depth + 1);
		// mark right and explore
		path[depth] = '1';
		dfs(hufhuf_tree->right, map, path, depth + 1);
	}
	// if leaf found
	else {
		// get key from tree node
		char* found = hufhuf_tree->value;
		int length = strlen(found);
		char* new_char = malloc(length * sizeof(char));
		memcpy(new_char, found, length);

		// get value from path
		char* path_to_char = malloc(strlen(path) * sizeof(char));
		memcpy(path_to_char, path, strlen(path));
		
		// add encoding to map
		put(map, new_char, path_to_char);
	}
}

