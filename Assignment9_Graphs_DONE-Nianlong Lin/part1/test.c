#include "my_graph.h"
#include <stdio.h>

void unit_1() {
    printf("Running Unit Test 1...\n");
    graph_t* graph = create_graph();
    if (graph != NULL) {
        printf("Graph creation successful.\n");
    } else {
        printf("Graph creation failed.\n");
    }
    free_graph(graph);
    printf("Unit Test 1 completed.\n\n");
}

void unit_2() {
    printf("Running Unit Test 2...\n");
    graph_t* graph = create_graph();
    int result = graph_add_node(graph, 1);
    if (result == 1) {
        printf("Node addition successful.\n");
    } else {
        printf("Node addition failed.\n");
    }
    free_graph(graph);
    printf("Unit Test 2 completed.\n\n");
}

void unit_3() {
    printf("Running Unit Test 3...\n");
    graph_t* graph = create_graph();
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    int result = graph_add_edge(graph, 1, 2);
    if (result == 1) {
        printf("Edge addition successful.\n");
    } else {
        printf("Edge addition failed.\n");
    }
    free_graph(graph);
    printf("Unit Test 3 completed.\n\n");
}

void unit_4() {
    printf("Running Unit Test 4...\n");
    graph_t* graph = create_graph();
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    graph_add_edge(graph, 1, 2);
    int result = graph_remove_edge(graph, 1, 2);
    if (result == 1) {
        printf("Edge removal successful.\n");
    } else {
        printf("Edge removal failed.\n");
    }
    free_graph(graph);
    printf("Unit Test 4 completed.\n\n");
}

void unit_5() {
    printf("Running Unit Test 5...\n");
    graph_t* graph = create_graph();
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    graph_add_edge(graph, 1, 2);
    int result = graph_remove_node(graph, 1);
    if (result == 1) {
        printf("Node removal successful.\n");
    } else {
        printf("Node removal failed.\n");
    }
    free_graph(graph);
    printf("Unit Test 5 completed.\n\n");
}

int main() {
    unit_1();
    unit_2();
    unit_3();
    unit_4();
    unit_5();
    return 0;
}