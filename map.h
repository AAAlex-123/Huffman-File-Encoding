struct LIST;
struct LIST_NODE;

typedef struct {

	int bucket_count;
	LIST** buckets;

} MAP;

// put if not exists, update otherwise
void put(MAP* map, char* key, char* value);

// get if exists, NULL otherwise
char* get(MAP* map, char* key);

typedef struct {

	int dummy;

} MAP_NODE;


typedef struct {

	LIST_NODE* head;

} LIST;

// append
void add(LIST* list, char* key, char* value);

// get if exists, NULL otherwise
char* get(LIST* list, char* key);

typedef struct {

	LIST_NODE* next;
	char* key, value;

} LIST_NODE;

