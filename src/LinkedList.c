#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/LinkedList.h"

// Create a node to add to a list from a given value val
static Node* create_node(char*);
// gets a value and return's its node
static Node* get_node_by_value(List*, char*);
// gets an index and return's its node
static Node* get_node_by_index(List*, int);
// gets a node and return's the node before
static Node* get_the_node_before(List*, Node*, Node*);
// check's if the index is out of the list bounds
static int is_index_out_of_bounds(List*, int);

List* create_list()
{
	List *ans = (List*)malloc(sizeof(List));
	ans->size = 0;
	ans->start = NULL;
	ans->end = NULL;
	return ans;
}

void add_first(List *self, char* val)
 {
	if (is_empty(self))
	{
		add_last(self, val);
		return;
	}
	Node *add = create_node(val);
	add->next = self->start;
	self->start = add;
	self->size++;
}

void add_last(List *self, char* val)
{
	Node *to_add = create_node(val);
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

void add_before_index(List *self, int index, char* val)
{
	Node *node = get_node_by_index(self, index);
	if (is_index_out_of_bounds(self, index))
	{
		fprintf(stderr, "Error: linked list out of bounds!\n");
		exit(1);
	}
	else if (self->start == node) // case start
		add_first(self, val);
	else if (self->end == node) // case end
	{
		Node *bef = get_the_node_before(self, node, self->start);
		Node *new_node = create_node(val);
		bef->next = new_node;
		new_node->next = self->end;
	}
	else // case not end or start
	{
		Node *bef = get_the_node_before(self, node, self->start->next);
		Node *new_node = create_node(val);
		bef->next = new_node;
		new_node->next = node;
	}
	self->size++;
}

void add_after_index(List *self, int index, char* val)
{
	Node *node = get_node_by_index(self, index);
	if (is_index_out_of_bounds(self, index))
	{
		fprintf(stderr, "Error: linked list out of bounds!\n");
		exit(1);
	}
	else if (self->start == node) // case start
	{
		Node *start_next_next = self->start->next->next;
		Node *new_node = create_node(val);
		self->start->next = new_node;
		new_node->next = start_next_next;
	}
	else if (self->end == node) // case end
		add_last(self, val);
	else // case not end or start
	{
		Node *new_node = create_node(val);
		Node *next_node = node->next;
		node->next = new_node;
		new_node->next = next_node;
	}
	self->size++;
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
		free(tmp);
	}
}

char* get_first(List *self)
{
	Node *first = self->start;
	if (first != NULL)
		return first->data;
	else
	{
		fprintf(stderr, "Error: The first node is empty!\n");
		exit(1);
	}
}

char* get_last(List *self)
{
	Node *last = self->end;
	if (last != NULL)
		return last->data;
	else
	{
		fprintf(stderr, "Error: The last node is empty!\n");
		exit(1);
	}
}

char* get(List *self, int index)
{
	if (is_index_out_of_bounds(self, index))
	{
		fprintf(stderr, "Error: linked list out of bounds!\n");
		return NULL;
	}
	int count = 0;
	Node *curr = self->start;
	while (curr != NULL)
	{
		if (count == index)
			return curr->data;
		count++;
		curr = curr->next;
	}
}

void remove_first(List *self)
{
	if (is_empty(self))
		fprintf(stderr, "Error: the list is empty!\n");
	Node *tmp = self->start;
	if (tmp != NULL)
	{
		self->start = self->start->next;
		free(tmp);
	}
	self->size--;
}

void remove_last(List *self)
{
	if (is_empty(self))
		fprintf(stderr, "Error: the list is empty!\n");
	Node* curr = NULL;
	Node *tmp = self->end;
	for (curr = self->start; curr->next != self->end; curr = curr->next); // find the node before end
	self->end = curr;
	self->end->next = NULL;
	free(tmp);
	self->size--;
}

void remove_by_value(List *self, char* val)
{
	// check if the value is in the list
	if (!contains(self, val))
	{
		fprintf(stderr, "Error: The value '%s' isn't in the list!\n", val);
		exit(1);
	}

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
		Node *remove = get_node_by_value(self, val);
		Node *bef_remove = get_the_node_before(self, remove, self->start->next);
		bef_remove->next = remove->next; // linking the node before remove to the node after remove
		free(remove); //freeing remove
	}
	self->size--;
}

int contains(List *self, char* val) // search for a val in the list
{
	return get_node_by_value(self, val) != NULL;
}

int is_empty(List *self)
{
	return self->size == 0;
}

List* reverse(List *self)
{
	Node *prev = NULL;
	Node *curr = self->start;
	Node *next;
	while (curr != NULL)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	self->start = prev;
	self->end = NULL;
	return self;
}

List* clone(List *self)
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
}

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

static Node* create_node(char* val)
{
	Node *new_node = (Node*)malloc(sizeof(Node));
	new_node->data = val;
	new_node->next = NULL;
	return new_node;
}