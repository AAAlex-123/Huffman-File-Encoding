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

int main() {
	// read file: FILE* file -> char* contents
	// encode: char* contents -> char* encoded contents
	// write file: FILE* file, char* encoded contents -> null
	return 0;
}

const char* read_file(const FILE* fp) {
	// get size
	// allocate memory for contents
	// read contents into buffer
	// return buffer
	return NULL;
}

const char* encode(const char* original_string) {
	// get encoding map: char* orig_str -> MAP* encoding map
	// encode with map: char* orig_str -> char* encoded str
	//  - the encoding entails writing the map to the string
	return NULL;
}

void write_encoded(const FILE* fp, const char* encoded_string) {
	// write frequency map
	// write encoded string
	return;
}

// encode

MAP* get_encoding_map(char* string) {
	// get frequency map of each character: char* str -> MAP* freq map
	// make tree with huffman stuff: MAP* freq map -> TREE* hufhuf tree
	// traverse tree to get each character's encoding: TREE* hufhuf tree -> MAP* encoding map
	// return map
	return NULL;
}

char* encode_with_map(MAP* map, char* string) {
	// for each character of the original string
	// get its encoding and write it to another string
	// return the encoded string
	return NULL;
}

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

