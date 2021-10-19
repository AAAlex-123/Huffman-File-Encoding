#include <cstdio>

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
	// get encoding map: char* orig_str -> MAP* encoding map
	MAP* encoding_map = get_encoding_map(original_string);

	// encode with map: char* orig_str -> char* encoded str
	//  - the encoding entails writing the map to the string
	char* encoded_string = encode_with_map(encoding_map, original_string);

	// return encoded string
	return encoded_string;
}

void write_encoded(FILE* fp, char* encoded_string) {
	// write encoded string
	fwrite(fp, encoded_string);

	return;
}

// encode

MAP* get_encoding_map(char* string) {
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

	char* encoded_string = malloc(10 * sizeof(char));

	// first encode the map into the string
	for (int i = 0; i < encoding_map->bucket_count; ++i) {
		for (LIST_NODE* curr = encoding_map->buckets[i]->head; curr != NULL; curr = curr->next) {
			append_to_string(encoded_string, curr->key);
			append_to_string(encoded_string, "=");
			append_to_string(encoded_string, curr->value);
			append_to_string(encoded_string, ",");
		}
	}

	// for each character of the original string
	// get its encoding and write it to another string
	for (int i = 0, length = strlen(string); i < length; ++i)
		append_to_string(encoded_string, get(encoding_map, string[i]));

	// return the encoded string
	return encoded_string;
}

// TODO: vvv IMPLEMENT vvv

// get_encoding_map

MAP* get_frequency_map(char* string) {
	// for each character of the original string
	// increment its frequency in the map
	// return the map
	return NULL;
}

TREE_NODE* make_hufhuf_tree(MAP* map) {
	// algorithm lol
	return NULL;
}

MAP* get_map_from_tree(TREE_NODE* hufhuf_tree) {
	// dfs, depth, path
	// path[depth] = '0'/'1'
	// path[depth+1] = NULL
	// if (node.val != NULL) map.put(val, path)
	// backtrack a bit
	return NULL;
}

void append_to_string(char* original, char* to_append) {
	printf("appending to '%s': '%s'", original, to_append);
}

