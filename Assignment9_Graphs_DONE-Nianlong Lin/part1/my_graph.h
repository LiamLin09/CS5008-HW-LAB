// CS5008 Assignment 9
// Author: Nianlong Lin
// Date: 11/5/2023


// =================== Support Code =================
// Graph.
//
//
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
#include <stdlib.h>
#include <assert.h>
// Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes;     //an array of nodes storing all of our nodes.
}graph_t;

typedef struct graph_node{
    int data;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
}graph_node_t;

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Returns NULL if we cannot allocate memory.
graph_t* create_graph(){
    // Modify the body of this function as needed.
    graph_t* myGraph= malloc(sizeof(graph_t));
    myGraph->nodes = create_dll();
    myGraph->numEdges = 0;
    myGraph->numNodes = 0;
    return myGraph;
}

// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node(graph_t * g, int value){

    node_t* node = g->nodes->head;
    while (node != NULL) {
        graph_node_t* graph_node = (graph_node_t*)node->data;
        if (graph_node->data == value) {
            return graph_node;
        }
        node = node->next;
    }
    return NULL;
}
// Creates a graph node
// Note: This relies on your dll implementation.
graph_node_t * create_graph_node(int value){
    graph_node_t * graph_node = malloc(sizeof(graph_node_t));

    if ( graph_node == NULL ) return NULL;

    graph_node->data = value;
    graph_node->inNeighbors = create_dll();
    graph_node->outNeighbors = create_dll();

    return graph_node;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node already exists )
// Returns -1 if the graph is NULL.
int graph_add_node(graph_t* g, int value){
    if ( g == NULL ) return -1;

    if (find_node(g, value) != NULL) return -1;

    graph_node_t * newNode = create_graph_node(value);
    if ( newNode == NULL ) return -1;

    assert(g->nodes);
    dll_push_back(g->nodes, newNode);
    g->numNodes++;

    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node doesn't exist )
// Returns -1 if the graph is NULL.
int graph_remove_node(graph_t* g, int value){
    graph_node_t* node = find_node(g, value);
    if (node == NULL) {
        return 0;
    }

    node_t* dll_node = g->nodes->head;
    while (dll_node != NULL) {
        if (dll_node->data == node) {
            if (dll_node->previous != NULL) {
                dll_node->previous->next = dll_node->next;
            } else {
                g->nodes->head = dll_node->next;
            }
            if (dll_node->next != NULL) {
                dll_node->next->previous = dll_node->previous;
            } else {
                g->nodes->tail = dll_node->previous;
            }
            free_dll(node->inNeighbors);
            free_dll(node->outNeighbors);
            free(node);
            free(dll_node);
            g->numNodes--;
            return 1;
        }
        dll_node = dll_node->next;
    }
    return 0;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
// Returns -1 if the graph is NULL.
int graph_add_edge(graph_t * g, int source, int destination){
    if (g == NULL) {
        return -1;
    }
    graph_node_t* source_node = find_node(g, source);
    graph_node_t* destination_node = find_node(g, destination);
    if (source_node == NULL || destination_node == NULL) {
        return 0;
    }
    dll_push_back(source_node->outNeighbors, destination_node);
    dll_push_back(destination_node->inNeighbors, source_node);
    g->numEdges++;
    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge doesn't exists )
// Returns -1 if the graph is NULL.
int graph_remove_edge(graph_t * g, int source, int destination){
    if (g == NULL) {
        return -1;
    }
    graph_node_t* source_node = find_node(g, source);
    graph_node_t* destination_node = find_node(g, destination);
    if (source_node == NULL || destination_node == NULL) {
        return 0;
    }
    dll_remove(source_node->outNeighbors, destination_node->data);
    dll_remove(destination_node->inNeighbors, source_node->data);
    g->numEdges--;
    return 1;
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist )
// Returns -1 if the graph is NULL.
int contains_edge(graph_t * g, int source, int destination){
    if (g == NULL) {
        return -1;
    }
    graph_node_t* source_node = find_node(g, source);
    graph_node_t* destination_node = find_node(g, destination);
    if (source_node == NULL || destination_node == NULL) {
        return 0;
    }

    node_t* node = source_node->outNeighbors->head;
    while (node != NULL) {
        if (node->data == destination_node) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}
// Returns dll_t* of all the in neighbors of this node.
// Returns NULL if the node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors(graph_t * g, int value){
    graph_node_t* node = find_node(g, value);
    if (node == NULL || g == NULL) {
        return NULL;
    }
    return node->inNeighbors;
}

// Returns the number of in neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumInNeighbors(graph_t * g, int value){
    dll_t* neighbors = getInNeighbors(g, value);
    if (neighbors == NULL || g == NULL) {
        return -1;
    }
    return neighbors->count;
}

// Returns dll_t* of all the out neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getOutNeighbors(graph_t * g, int value){
    graph_node_t* node = find_node(g, value);
    if (node == NULL || g == NULL) {
        return NULL;
    }
    return node->outNeighbors;
}

// Returns the number of out neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumOutNeighbors(graph_t * g, int value){
    dll_t* neighbors = getOutNeighbors(g, value);
    if (neighbors == NULL || g == NULL) {
        return -1;
    }
    return neighbors->count;
}

// Returns the number of edges in the graph,
// Returns -1 on if the graph is NULL
int graph_num_nodes(graph_t* g){g
    if (g == NULL) {
        return -1;
    }
    return g->numNodes;
}


int graph_num_edges(graph_t* g){
    if (g == NULL) {
        return -1;
    }
    return g->numEdges;
}

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the program terminates.
// Make sure you free all the dll's too.
void free_graph(graph_t* g){

    node_t* node = g->nodes->head;
    while (node != NULL) {

        node_t* next_node = node->next;
        graph_node_t* graph_node = (graph_node_t*)node->data;
        free_dll(graph_node->inNeighbors);
        free_dll(graph_node->outNeighbors);
        free(graph_node);
        free(node);
        node = next_node;
    }
    free(g->nodes);
    free(g);
}



#endif
