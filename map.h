
struct MAP {

	int bucket_count;
	struct LIST** buckets;

} MAP;

struct MAP* create_map(int buckets);

 // put if not exists, update otherwise
void put(struct MAP* map, char* key, char* value);

// get if exists, NULL otherwise
char* get(struct MAP* map, char* key);

int hash(char* key);

struct LIST {

	struct LIST_NODE* head;

} LIST;

struct LIST_NODE {

	struct LIST_NODE* next;
	char* key, value;

} LIST_NODE;

struct LIST_NODE* create_node(char* key, char* value);

// append
void append(struct LIST* list, struct LIST_NODE* node);

// get if exists, NULL otherwise
struct LIST_NODE* get(struct LIST* list, char* key);

