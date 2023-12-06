// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
//
//
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
// - You should not have any 'printf' statements in your DLL functions.
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
//   - (You may write helper functions to help you debug your code such as print_list etc)
// ==================================================
// CS 5008
// Author: Nianlong Lin
// Assignment 3
// Date: 9/24/2023
// this program is to finish each method to create a working double linked list.


#ifndef MYDLL_H
#define MYDLL_H

#include <stdio.h>
#include <stdlib.h>

// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node{
	int data;
	struct node* next;
  	struct node* previous;
}node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL{
	int count;		// count keeps track of how many items are in the DLL.
	node_t* head;		// head points to the first node in our DLL.
        node_t * tail;          //tail points to the last node in our DLL.
}dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t* create_dll(){
    // creates a new DLL
	dll_t* myDLL = (dll_t*)malloc(sizeof(dll_t));
	if (myDLL == NULL) {
        return NULL;
	}

	myDLL->count = 0;
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
int dll_push_front(dll_t* l, int item){

    // if DLL is null, return -1;
    if (l == NULL) {
        return -1;
    }

    // create a new node
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    // if cannot allocate memory the new node, return 0
    if (new_node == NULL) {
        return 0;
    }

    new_node->data = item;
    // new node next point to head
    new_node->next = l->head;
    // new node previous point to null
    new_node->previous = NULL;
    // if DLL is not null, head's previous points to new node.
    // if it is null, the tail would point to new node.
    if (l->head != NULL) {
        l->head->previous = new_node;
    } else {
        l->tail = new_node;
    }

    l->head = new_node;
    // number of items in dll increases by 1
    l->count++;
    return 1;
}

// push a new item to the end of the DLL (after the last node in the list).
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// Returns -1 if DLL is NULL.
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t* l, int item){

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
int dll_pop_front(dll_t* t){

    if (t == NULL || t->head == NULL) {
        return -1;
    }

    node_t* temp = t->head;
    int data = temp->data;
    t->head = temp->next;
    if (t->head != NULL) {
        t->head->previous = NULL;
    } else {
        t->tail = NULL;
    }
    free(temp);
    t->count--;
    return data;
}

// Returns the last item in the DLL, and also removes it from the list.
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Returns a -1 if the DLL is NULL.
// Assume no negative numbers in the list or the number zero.
int dll_pop_back(dll_t* t){

    if (t == NULL || t->tail == NULL) {
        return -1;
    }

    node_t* temp = t->tail;
    int data = temp->data;
    t->tail = temp->previous;
    if (t->tail != NULL) {
        t->tail->next = NULL;
    } else {
        t->head = NULL;
    }
    free(temp);
    t->count--;
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
int dll_insert(dll_t* l, int pos, int item){
    if (l == NULL) {
        return -1;
    }

    // fail to insert
    if (pos < 0 || pos > l->count) {
        return 0;
    }

    // if pos = 0, we use push front function
    if (pos == 0) {
        return dll_push_front(l, item);
    }

    // if pos == count , we use push back
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
int dll_get(dll_t* l, int pos){
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
// Retruns 0 on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Returns -1 if the list is NULL
// Assume no negative numbers in the list or the number zero.
int dll_remove(dll_t* l, int pos){
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
    int data = current->data;
    free(current);
    l->count--;
    return data;
}

// DLL Size
// Queries the current size of a DLL
// Returns -1 if the DLL is NULL.
int dll_size(dll_t* t){
    if (t = NULL) {
        return -1;
    }
    return t->count;
}

// Free DLL
// Removes a DLL and all of its elements from memory.
// This should be called before the proram terminates.
void free_dll(dll_t* t){
    if (t == NULL) {
        return;
    }
    node_t* current = t->head;
    while (current != NULL) {
        node_t* temp = current;
        current = current->next;
        free(temp);
    }
    free(t);
}

int dll_set(dll_t* dll, int index, int value) {
    if (dll == NULL) {
        return -1;
    }
    if (index < 0) {
        return 0;
    }

    node_t* current = dll->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->data = value;
    return 1;
}

// test function
void test_dll() {
    dll_t* myDLL = create_dll();
    printf("DLL empty: %d\n", dll_empty(myDLL));
    dll_push_front(myDLL, 1);
    dll_push_front(myDLL, 2);
    dll_push_back(myDLL, 3);
    dll_push_back(myDLL, 4);
    printf("DLL size: %d\n", dll_size(myDLL));
    printf("DLL empty: %d\n", dll_empty(myDLL));
    printf("DLL get(0): %d\n", dll_get(myDLL, 0));
    printf("DLL get(1): %d\n", dll_get(myDLL, 1));
    printf("DLL get(2): %d\n", dll_get(myDLL, 2));
    printf("DLL get(3): %d\n", dll_get(myDLL, 3));
    printf("DLL pop front: %d\n", dll_pop_front(myDLL));
    printf("DLL pop back: %d\n", dll_pop_back(myDLL));
    printf("DLL size: %d\n", dll_size(myDLL));
    printf("DLL remove(1): %d\n", dll_remove(myDLL, 1));
    printf("DLL size: %d\n", dll_size(myDLL));
    free_dll(myDLL);

}



#endif
