// CS 5008 Assignment 8
// Author: Nianlong Lin
// Date: 10/30/2023

#include "my_bst.h"
#include <stdio.h>
#include <stdlib.h>

// Creates a BST
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values(i.e. size=0).
bst_t* bst_create(){
    bst_t* myBST= (bst_t*)malloc(sizeof(bst_t));
    myBST->root = NULL;
    myBST->size = 0;
    return myBST;
}

// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element)
int bst_empty(bst_t* t){
    return (t->size == 0);
}

// Adds a new node containng item to the BST
// The item is added in the correct position in the BST.
//  - If the data is less than or equal to the current node we traverse left
//  - otherwise we traverse right.
// The bst_function returns '1' upon success
//  - bst_add should increment the 'size' of our BST.
// Returns a -1 if the operation fails.
//      (i.e. the memory allocation for a new node failed).
// Your implementation should should run in O(log(n)) time.
//  - A recursive imlementation is suggested.
int bst_add(bst_t* t, int item){
    bstnode_t* newNode = (bstnode_t*)malloc(sizeof(bstnode_t));
    // memory allocation failed
    if (newNode == NULL) {
        return -1;
    }
    newNode->data = item;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    if (t->root == NULL) {
        t->root = newNode;
    } else {bstnode_t* current = t->root;
        while(1) {
            if (item <= current->data) {
                if (current->leftChild == NULL) {
                    current->leftChild = newNode;
                    break;
                } else {
                    current = current->leftChild;
                }
            } else {
                if (current->rightChild == NULL) {
                    current->rightChild = newNode;
                    break;
                } else {
                    current = current->rightChild;
                }
            }
        }
    }
    t->size++;
    return 1;
}

void print_in_order(bstnode_t* node) {
    if (node == NULL) {
        return;
    }
    print_in_order(node->leftChild);
    printf("%d", node->data);
    print_in_order(node->rightChild);
}

void print_post_order(bstnode_t* node) {
    if (node == NULL) {
        return;
    }
    print_post_order(node->leftChild);
    print_post_order(node->rightChild);
    printf("%d", node->data);
}

// Prints the tree in ascending order if order = 0, otherwise prints in descending order.
// For NULL tree -- print "(NULL)".
// It should run in O(n) time.
void bst_print(bst_t *t, int order){
    if (t = NULL) {
        printf("(NULL)\n");
    } else {
        if (order == 0) {
            print_in_order(t->root);
        } else {
            print_post_order(t->root);
        }
    }
}

int sum(bstnode_t* node) {
    if (node == NULL) {
        return 0;
    }
    return node->data + sum(node->leftChild) + sum(node->rightChild);
}

// Returns the sum of all the nodes in the bst.
// exits the program for a NULL tree.
// It should run in O(n) time.
int bst_sum(bst_t *t){
    if (t == NULL) {
        exit(EXIT_FAILURE);
    }
    return sum(t->root);
}

int find(node_t* node, int value) {
    if (node == NULL) {
        return 0;
    }
    if (node->data == value) {
        return 1;
    }
    if (value < node->data) {
        return find_node(node->leftChild, value);
    } else {
        return find_node(node->rightChild, value);
    }
}

// Returns 1 if value is found in the tree, 0 otherwise.
// For NULL tree it exists the program.
// It should run in O(log(n)) time.
int bst_find(bst_t * t, int value){
    if (t == NULL) {
        exit(EXIT_FAILURE);
    }
    return find(t->root, value);
}

// Returns the size of the BST
// A BST that is NULL exits the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(bst_t* t){
    if (t == NULL) {
        exit(EXIT_FAILURE);
    }
    return t->size;
}

void free_tree(bstnode_t* node) {
    if (node == NULL) {
        return;
    }
    free_tree(node->leftChild);
    free_tree(node->rightChild);
    free(node);
}

// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the proram terminates.
void bst_free(bst_t* t){
    if (t == NULL) {
        exit(EXIT_FAILURE);
    }
    free_tree(t->root);
    free(t);
}
}

