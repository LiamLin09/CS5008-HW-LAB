// CS5008 Assignment 9
// Author: Nianlong Lin
// Date: 11/5/2023


#ifndef MYDLL_H
#define MYDLL_H

#include <stdlib.h>
// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node{
    void* data;
    struct node* next;
    struct node* previous;
}node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL{
    int count;        // count keeps track of how many items are in the DLL.
    node_t* head;        // head points to the first node in our DLL.
    node_t * tail;          //tail points to the last node in our DLL.
}dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t* create_dll(){
    // Modify the body of this function as needed.
    dll_t* myDLL= malloc(sizeof(dll_t));
    if (myDLL == NULL) {
        return NULL;
    }
    myDLL->count =0;
    myDLL->head = NULL;
    myDLL->tail = NULL;
    return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
// Returns -1 if the dll is NULL.
int dll_empty(dll_t* l){
	if (l == NULL) {
		return -1;
	}
	return l->count == 0;
}

// push a new item to the front of the DLL ( before the first node in the list).
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// Returns -1 if DLL is NULL.
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t* l, void* item){
	if (l == NULL) {
		return -1;
	}
	node_t* new_node = (node_t*)malloc(sizeof(node_t));
	if (new_node == NULL) {
		return 0;
	}
	new_node->data = item;
	new_node->next = l->head;
	new_node->previous = NULL;
	if (l->head != NULL) {
		l->head->previous = new_node;
	} else {
		l->tail = new_node;
	}
	l->head = new_node;
	l->count++;
	return 1;
}
// push a new item to the end of the DLL (after the last node in the list).
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// Returns -1 if DLL is NULL.
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, void* item){
	if (l == NULL) {
		return -1;
	}
	node_t* new_node = (node_t*)malloc(sizeof(node_t));
	if (new_node == NULL) {
		return 0;
	}
	new_node->data = item;
	new_node->next = NULL;
	new_node->previous = l->tail;
	if (l->tail != NULL) {
		l->tail->next = new_node;
	} else {
		l->head = new_node;
	}
	l->tail = new_node;
	l->count++;
	return 1;
}

// Returns the first item in the DLL and also removes it from the list.
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Returns a -1 if the DLL is NULL.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_front(dll_t* l){
	if (l == NULL) {
		return -1;
	}
	if (l->head == NULL) {
        return 0;
	}
	node_t* temp = l->head;
	void* data = temp->data;
	l->head = temp->next;
	if (l->head != NULL) {
		l->head->previous = NULL;
	} else {
		l->tail = NULL;
	}
	free(temp);
	l->count--;
	return data;
}


// Returns the last item in the DLL, and also removes it from the list.
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Returns a -1 if the DLL is NULL.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_back(dll_t* l){
	if (l == NULL || l->tail == NULL) {
		return -1;
	}
	node_t* temp = l->tail;
	void* data = temp->data;
	l->tail = temp->previous;
	if (l->tail != NULL) {
		l->tail->next = NULL;
	} else {
		l->head = NULL;
	}
	free(temp);
	l->count--;
	return data;
}
// Inserts a new node before the node at the specified position.
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
// Returns -1 if the list is NULL
int dll_insert(dll_t* l, int pos, void* item){
	if (l == NULL) {
		return -1;
	}
	if (pos < 0 || pos > l->count) {
		return 0;
	}
	if (pos == 0) {
		return dll_push_front(l, item);
	}
	if (pos == l->count) {
		return dll_push_back(l, item);
	}
	node_t* current = l->head;
	for (int i = 0; i < pos; i++) {
		current = current->next;
	}
	node_t* new_node = (node_t*)malloc(sizeof(node_t));
	if (new_node == NULL) {
		return 0;
	}
	new_node->data = item;
	new_node->next = current;
	new_node->previous = current->previous;
	current->previous->next = new_node;
	current->previous = new_node;
	l->count++;
	return 1;
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
//  (does not remove the item)
// Retruns 0 on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Returns -1 if the list is NULL
// Assume no negative numbers in the list or the number zero.
void* dll_get(dll_t* l, int pos){
	if (l == NULL) {
		return -1;
	}
	if (pos < 0 || pos >= l->count) {
		return 0;
	}
	node_t* current = l->head;
	for (int i = 0; i < pos; i++) {
		current = current->next;
	}
	return current->data;
}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Retruns NULL on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Returns NULL if the list is NULL
// Assume no negative numbers in the list or the number zero.
void* dll_remove(dll_t* l, int pos){
	if (l == NULL) {
		return -1;
	}
	if (pos < 0 || pos >= l->count) {
		return 0;
	}
	if (pos == 0) {
		return dll_pop_front(l);
	}
	if (pos == l->count - 1) {
		return dll_pop_back(l);
	}
	node_t* current = l->head;
	for (int i = 0; i < pos; i++) {
		current = current->next;
	}
	current->previous->next = current->next;
	current->next->previous = current->previous;
	void* data = current->data;
	free(current);
	l->count--;
	return data;
}

// DLL Size
// Queries the current size of a DLL
// Returns -1 if the DLL is NULL.
int dll_size(dll_t* l){
	if (l == NULL) {
		return -1;
	}
	return l->count;
}

// Free DLL
// Removes a DLL and all of its elements from memory.
// This should be called before the proram terminates.
void free_dll(dll_t* l){
	if (l == NULL) {
		return;
	}
	node_t* current = l->head;
	while (current != NULL) {
		node_t* temp = current;
		current = current->next;
		free(temp);
	}
	free(l);
}



#endif

