typedef struct _Node
{
    char *name;
    char *value;
    struct _Node *next;
} Node_env;

typedef struct _List
{
    Node_env *start;
    Node_env *end;
    int size;
} List_env;

/*Create the object*/
/*Returns a pointer to the object on the heap memory.*/
List_env *create_list_env();

/*Add to the first node.*/
/*void add_first(List *self, char *val);*/

/*Add to the last node.*/
void add_last_env(List_env *self, char *name, char *val);

/*Add before given index.*/
/*Returns 0 if succeeded, -1 elsewise.*/
/*int add_before_index(List *self, int index, char *val);*/

/*Add after given index.*/
/*Returns 0 if succeeded, -1 elsewise.*/
/*int add_after_index(List *self, int index, char *val);*/

/*Get the first value.*/
// char *get_first(List *self);

// /*Get the last value.*/
// char *get_last(List *self);

/*Get value at given index.*/
char *get_env(List_env *self, int index);

// /*Remove first value.*/
// /*Returns 0 if succeeded, -1 elsewise.*/
// int remove_first(List *self);

// /*Remove last value.*/
// /*Returns 0 if succeeded, -1 elsewise.*/
// int remove_last(List *self);

// /*Remove given value.*/
// /*Returns 0 if succeeded, -1 elsewise.*/
// int remove_by_value(List *self, char *val);

// /*Print the list in python's list printing style.*/
// void print_list(List *self);

// /*Free the list from heap memory.*/
// void free_list(List *self);

/*Returns 1 if val contains in list, 0 elsewise.*/
int contains_env(List_env *self, char *name);

/*Returns 1 if list is empty, 0 elsewise.*/
int is_empty_env(List_env *self);

/*Clone the list.*/
/*Returns a copy of list if succeeded, NULL elsewise.*/
// List *clone(List *self);

// /*Reverse the list.*/
// /*Returns a copy of the reversed list if succeeded, NULL elsewise.*/
// List *reverse(List *self);