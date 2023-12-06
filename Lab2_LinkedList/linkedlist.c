// Modify this file
// compile with: gcc linkedlist.c -o linkedlist

#include <stdio.h>
#include <stdlib.h> // contains the functions free/malloc

// Create your node_t type here


typedef struct node {
    int year;
    int wins;
    struct node* next;
} node_t;

//create a node on heap and return its pointer
node_t* create_node(int year, int wins, node_t* next) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->year = year;
    new_node->wins = wins;
    new_node->next = next;
    return new_node;
}

//create the linked list
node_t* create_list() {
    node_t* head = NULL;
    head = create_node(2022, 78, head);
    head = create_node(2021, 92, head);
    head = create_node(2020, 24, head);
    head = create_node(2019, 84, head);
    head = create_node(2018, 108, head);
    head = create_node(2017, 93, head);
    head = create_node(2016, 93, head);
    head = create_node(2015, 78, head);
    head = create_node(2014, 71, head);
    return head;
}


//iterate through the linked list and print the data
void print_list(node_t* head) {
    node_t* itr = head;
    while (itr != NULL) {
        printf("%d, %d wins.\n", itr->year, itr->wins);
        itr = itr->next;
    }
}

// free the memory
void free_list(node_t* head) {
    node_t* current = head;
    node_t* next_node;
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

int main()
{
    node_t* head = create_list();
    print_list(head);
    free_list(head);
    return 0;
}
