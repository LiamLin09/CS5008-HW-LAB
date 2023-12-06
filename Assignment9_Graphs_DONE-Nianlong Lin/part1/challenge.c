#include <stdio.h>
#include <stdlib.h>
#define HASH_SIZE 101

struct Node {
    int val;
    int numNeighbors;
    struct Node** neighbors;
};


struct HashNode {
    int key;
    struct Node* value;
    struct HashNode* next;
};


struct HashNode* hashTable[HASH_SIZE];

int hash(int key) {
    return key % HASH_SIZE;
}

void insert(int key, struct Node* value) {
    struct HashNode* newNode = malloc(sizeof(struct HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    int index = hash(key);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

struct Node* search(int key) {
    int index = hash(key);
    struct HashNode* node = hashTable[index];
    while (node != NULL) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

struct Node* cloneGraph(struct Node* node) {
    if (node == NULL) {
        return NULL;
    }
    struct Node* clone = search(node->val);
    if (clone != NULL) {
        return clone;
    }
    clone = malloc(sizeof(struct Node));
    clone->val = node->val;
    clone->numNeighbors = node->numNeighbors;
    clone->neighbors = malloc(clone->numNeighbors * sizeof(struct Node*));
    insert(clone->val, clone);
    for (int i = 0; i < node->numNeighbors; i++) {
        clone->neighbors[i] = cloneGraph(node->neighbors[i]);
    }
    return clone;
}

void printGraph(struct Node* node) {
    if (node == NULL) {
        printf("Graph is empty.\n");
        return;
    }
    printf("Node value: %d, Number of neighbors: %d\n", node->val, node->numNeighbors);
    for (int i = 0; i < node->numNeighbors; i++) {
        printf("Neighbor %d: Node value: %d\n", i+1, node->neighbors[i]->val);
    }
}

int main() {
    struct Node* node1 = malloc(sizeof(struct Node));
    struct Node* node2 = malloc(sizeof(struct Node));
    struct Node* node3 = malloc(sizeof(struct Node));
    node1->val = 1;
    node2->val = 2;
    node3->val = 3;
    node1->numNeighbors = 2;
    node2->numNeighbors = 2;
    node3->numNeighbors = 2;
    node1->neighbors = malloc(2 * sizeof(struct Node*));
    node2->neighbors = malloc(2 * sizeof(struct Node*));
    node3->neighbors = malloc(2 * sizeof(struct Node*));
    node1->neighbors[0] = node2;
    node1->neighbors[1] = node3;
    node2->neighbors[0] = node1;
    node2->neighbors[1] = node3;
    node3->neighbors[0] = node1;
    node3->neighbors[1] = node2;

    printf("Original Graph:\n");
    printGraph(node1);
    printGraph(node2);
    printGraph(node3);

    struct Node* clone1 = cloneGraph(node1);
    struct Node* clone2 = cloneGraph(node2);
    struct Node* clone3 = cloneGraph(node3);

    printf("\nCloned Graph:\n");
    printGraph(clone1);
    printGraph(clone2);
    printGraph(clone3);

    return 0;
}