#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/LinkedListEnv.h"

// Create a node to add to a list
static Node *create_node(char *name, char *value);
// gets a value and return's its node
static Node* get_node_by_value(List* self, char* val);
// gets an index and return's its node
static Node* get_node_by_index(List* self, int index);
// gets a node and return's the node before
static Node* get_the_node_before(List* self, Node* node, Node* startPos);
// check's if the index is out of the list bounds
static int is_index_out_of_bounds(List* self, int index);

List* create_list()
{
	List *ans = (List*)malloc(sizeof(List));
	ans->size = 0;
	ans->start = NULL;
	ans->end = NULL;
	return ans;
}

void add_first(List *self, char* name, char* val)
 {
	if (is_empty(self))
	{
		add_last(self, val);
		return;
	}
	Node *add = create_node(name, val);
	add->next = self->start;
	self->start = add;
	self->size++;
}

void add_last(List *self, char* name, char* val)
{
	Node *to_add = create_node(name, val);
	if (is_empty(self))
	{
		self->start = to_add;
		self->end = to_add;
	}
	else
	{
		self->end->next = to_add;
		self->end = to_add;
	}
	self->size++;
}

int add_before_index(List* self, int index, char* name, char* val)
{
	Node* node = get_node_by_index(self, index);
	if (is_index_out_of_bounds(self, index))
		return -1;
	else if (self->start == node) // case start
		add_first(self, val);
	else if (self->end == node) // case end
	{
		Node* bef = get_the_node_before(self, node, self->start);
		Node* new_node = create_node(name, val);
		bef->next = new_node;
		new_node->next = self->end;
	}
	else // case not end or start
	{
		Node* bef = get_the_node_before(self, node, self->start->next);
		Node* new_node = create_node(name,val);
		bef->next = new_node;
		new_node->next = node;
	}
	self->size++;
	return 0;
}

int add_after_index(List* self, int index, char* val)
{
	Node* node = get_node_by_index(self, index);
	if (is_index_out_of_bounds(self, index))
		return -1;
	else if (self->start == node) // case start
	{
		Node* start_next_next = self->start->next->next;
		Node* new_node = create_node(name,val);
		self->start->next = new_node;
		new_node->next = start_next_next;
	}
	else if (self->end == node) // case end
		add_last(self, name,val);
	else // case not end or start
	{
		Node* new_node = create_node(name,val);
		Node* next_node = node->next;
		node->next = new_node;
		new_node->next = next_node;
	}
	self->size++;
	return 0;
}

void print_list(List *self) // prints until the next NULL
{
	printf("[");
	if (!is_empty(self))
	{
		Node *curr = self->start;
		while (curr != NULL)
		{
			if (curr == self->end)
				printf("%s", curr->data);
			else
				printf("%s, ", curr->data);
			curr = curr->next;
		}
	}
	printf("]\n");
}

void free_list(List *self)
{
	Node *curr = self->start;
	Node *tmp = NULL;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->data);
		free(tmp);
	}
	free(self);
}

char* get_first(List* self)
{
	Node* first = self->start;
	if (first != NULL)
		return first->data;
	else
	{
		fprintf(stderr, "Error: The first node is empty!\n");
		return 0;
	}
}

char* get_last(List* self)
{
	Node* last = self->end;
	if (last != NULL)
		return last->data;
	else
	{
		fprintf(stderr, "Error: The last node is empty!\n");
		return 0;
	}
}

char* get(List* self, int index)
{
	if (is_index_out_of_bounds(self, index))
		return NULL;

	int count = 0;
	Node* curr = self->start;
	while (curr != NULL)
	{
		if (count == index)
			return curr->data;
		count++;
		curr = curr->next;
	}
	return NULL;
}

int remove_first(List* self)
{
	if (is_empty(self))
		return -1;
	Node* tmp = self->start;
	if (tmp != NULL)
	{
		self->start = self->start->next;
		free(tmp);
	}
	self->size--;
	return 0;
}

int remove_last(List* self)
{
	if (is_empty(self))
		return -1;
	Node* curr = NULL;
	Node* tmp = self->end;
	for (curr = self->start; curr->next != self->end; curr = curr->next); // find the node before end
	self->end = curr;
	self->end->next = NULL;
	free(tmp);
	self->size--;
	return 0;
}

/*int remove_by_value(List* self, char* val)
{
	// check if the value is in the list
	if (!contains(self, val))
		return -1;
	// go through the list and take care of all the cases
	else if (self->start->data == val) // case its the first node
	{
		remove_first(self);
	}

	else if (self->end->data == val) // case its the last node
	{
		remove_last(self);
	}

	else // case its not end or start
	{
		Node* remove = get_node_by_value(self, val);
		Node* bef_remove = get_the_node_before(self, remove, self->start->next);
		bef_remove->next = remove->next; // linking the node before remove to the node after remove
		free(remove); //freeing remove
	}
	self->size--;
	return 0;
}*/

int contains(List *self, char* val) // search for a val in the list
{
	return get_node_by_value(self, val) != NULL;
}

int is_empty(List *self)
{
	return self->size == 0;
}

/*List* reverse(List *self)
{
	List* list = clone(self); // create a copy of list
	if (list == NULL) // if clone failed
		return NULL;
	Node* tmp = list->start; // save self->start to later set self->end to it
	Node* prev = NULL;
	Node* curr = list->start;
	Node* next = NULL;
	while (curr != NULL)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	list->start = prev;
	list->end = tmp;
	return list;
}*/

/*List* clone(List *self)
{
	// check if self is null
	if (is_empty(self))
		return NULL;

	// create new list
	List *new_list = (List*)malloc(sizeof(List));
	new_list->start = create_node(self->start->data);

	// nodes for iteartion
	Node *curr_node = self->start;
	Node *prev_new_node = new_list->start;
	Node *next_new_node = prev_new_node->next; // NULL

	while (curr_node->next != NULL)
	{
		// copy data
		next_new_node = create_node(curr_node->next->data);
		prev_new_node->next = next_new_node;

		// go to next
		prev_new_node = prev_new_node->next;
		curr_node = curr_node->next;
	}
	// update new list -> end
	new_list->end = next_new_node;

	// update new list -> size
	new_list->size = self->size;

	// return new list
	return new_list;
}*/

static Node* get_node_by_value(List *self, char* val)
{
	Node *curr = self->start;
	while (curr != NULL)
	{
		if (curr->data == val)
			return curr;
		curr = curr->next;
	}
	return NULL;
}

static Node* get_node_by_index(List *self, int index)
{
	Node *curr = self->start;
	int count = 0;
	while (curr != NULL)
	{
		if (count == index)
			return curr;
		count++;
		curr = curr->next;
	}
	return NULL;
}

static Node* get_the_node_before(List *self, Node* node, Node *startPos)
{
	Node *bef_node = startPos;
	for (; bef_node->next != node; bef_node = bef_node->next);
	return bef_node;
}

static int is_index_out_of_bounds(List *self, int index)
{
	return index >= self->size;
}

static Node* create_node(char* name, char* value)
{
	Node *new_node = (Node*)malloc(sizeof(Node));
	new_node->name = name;
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}