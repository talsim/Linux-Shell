typedef struct Node
{
	char* data;
	struct Node *next;
} Node;

typedef struct List
{
	Node *start;
	Node *end;
	int size;
} List;

// create the object
List* create_list();

void add_first(List* self, char* val);
void add_last(List *self, char* val);
void add_before_index(List* self, int index, char* val);
void add_after_index(List* self, int index, char* val);
void remove_first(List *self);
void remove_last(List *self);
void remove_by_value(List* self, char* val);
void print_list(List *self);
void free_list(List *self);
int contains(List* self, char* val);
char* get_first(List* self);
char* get_last(List* self);
char* get(List* self, int index);
int is_empty(List *self);
List* reverse(List *self);
List* clone(List *self);