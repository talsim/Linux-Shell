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

/*Create the object*/
/*Returns a pointer to the object on the heap memory.*/
List* create_list();

/*Add to the first node.*/
void add_first(List* self, char* val);

/*Add to the last node.*/
void add_last(List *self, char* val);

/*Add before given index.*/
/*Returns 0 if succeeded, -1 elsewise.*/
int add_before_index(List* self, int index, char* val);

/*Add after given index.*/
/*Returns 0 if succeeded, -1 elsewise.*/
int add_after_index(List* self, int index, char* val);

/*Get the first value.*/
char* get_first(List* self);

/*Get the last value.*/
char* get_last(List* self);

/*Get value at given index.*/
char* get(List* self, int index);

/*Remove first value.*/
/*Returns 0 if succeeded, -1 elsewise.*/
int remove_first(List* self);

/*Remove last value.*/
/*Returns 0 if succeeded, -1 elsewise.*/
int remove_last(List* self);

/*Remove given value.*/
/*Returns 0 if succeeded, -1 elsewise.*/
int remove_by_value(List* self, char* val);

/*Print the list in python's list printing style.*/
void print_list(List *self);

/*Free the list from heap memory.*/
void free_list(List *self);

/*Returns true if val contains in list, false elsewise.*/
int contains(List *self, char* val);

/*Returns true is list is empty, false elsewise.*/
int is_empty(List *self);

/*Clone the list.*/
/*Returns a copy of list if succeeded, NULL elsewise.*/
List* clone(List* self);

/*Reverse the list.*/
/*Returns a copy of the reversed list if succeeded, NULL elsewise.*/
List* reverse(List *self);