// cs5008 Assignment9
// Author: Nianlong Lin
// Date: 11/5/2023

# Exercises

Discuss and answer the following questions (Make sure to elaborate and justify your responses):

1. What is the Big-O space complexity of an adjacency list?
1. What is the Big-O space complexity of an adjacency matrix?
3. What is the Big-O to search an entire graph using Depth-First Search (DFS)?
4. What is the Big-O to search an entire graph using Breadh-First Search (BFS)?

## Answers

1. the space complexity for an adjacency list is O(V+E).
In an adjacency list, each vertex has a list of adjacent vertices.
The space taken by the adjacency list is proportional to the sum of the sizes of all the adjacency list.
for a graph with V vertices and E edges: we need space for V lists (for each vertex); each edges contribution to 2 entries in the total adjacency
list structure.
so, for an undirected graph, the space complexity is O(V + 2E), which can simplify to O(V+E); for a directed graph is O(V+E).

2. For a graph with V verices, when we draw an adjacency matrix, we need a V * V matrix to represent the edge between all vertices.
each cell in the matrix represents the possible edge between two vertices, so the total number of cells is V^2.
so the space complexity of an adjacency martrix is O(V^2).

3. The space complexity for DFS is 0(V). in the worst case to maintanin in stack used for recursion, we may potentially have to entire
set of vertices in the stack in the case of a path that includes all the vertices.
The time complexity for DFS depends on the representation of the graph.
if the graph is represented using an adjacency list, the complexity if O(V+E), this is because every vertex is explored exactly once and
every edge is considered exactly once (twice if the graph is undirected);if the graph is represented with an adjacency matrix, the time complexity 
would be O(V^2), becuase we need to check every possible vertex-vertex pair to determine if an edge exists between them when we are exploring from
each vertex.

4. The space complexity for BFS is O(V). BFS uses additional space for a queue which at worst case can store all the vertices of the graph.
The time complexity for BFS is O(V+E) when using adjacency list, each vertex is dequeued exactly once in BFS and each edge is considered 
exactly once in an undirected graph and twice in a directed graph. When using adjacency matrix, the time complexity is O(V^2).

## Interview Prep (Optional +1% Bonus on assignment)

> **Rules** 
> 
> This is for bonus--and you may not ask TA's, Professors, or anyone about the question until after the homework is due.
> 
> Stratigically, you should not attempt this problem until you complete the rest of the homework (1% is less than 100% :) )

A bit ago a student asked me about this course, CS 5800, and other courses and how they may prepare you for interviews. I was recently talking to a Google, now Microsoft Engineer who told me that the reality is having a lot of LeetCode practice will help. LeetCode is a website to practice solving algorithmic challenges.

Let's finish off this exercise with a small C programming sample.

### Clone Graph

Solve the following: https://leetcode.com/problems/clone-graph/

**Copy and paste your code into** a file in this directory called [challenge.c](./challenge.c) that solves the following problem.

Given a reference of a node in a connected undirected graph.

Return a deep copy (clone) of the graph.

Each node in the graph contains a val (int) and a list (List[Node]) of its neighbors.
