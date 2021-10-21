
typedef struct MAP {

	int bucket_count;
	LIST** buckets;

} MAP;

MAP* create_map(int buckets);

 // put if not exists, update otherwise
void put(MAP* map, char* key, char* value);

// get if exists, NULL otherwise
char* get(MAP* map, char* key);

int hash(char* key);

typedef struct LIST {

	LIST_NODE* head;

} LIST;

typedef struct LIST_NODE {

	LIST_NODE* next;
	char* key, value;

} LIST_NODE;

LIST_NODE* create_node(char* key, char* value);

// append
void append(LIST* list, LIST_NODE* node);

// get if exists, NULL otherwise
LIST_NODE* get(LIST* list, char* key);

