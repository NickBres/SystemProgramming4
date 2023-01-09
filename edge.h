#ifndef EDGE_H
#define EDGE_H

#include "graph.h"

pedge create_edge(pnode endpoint, int weight);      // create a new edge with endpoint and weight and return a pointer to it
void add_edge(pedge head, pedge new_edge);          // insert a edge to the end of the list
void free_edges(pedge head);                        // free all edges in list
pedge find_edge_to(pedge head, pnode endpoint);     // find an edge with endpoint and return a pointer to it
pedge find_edge_before(pedge head, pnode endpoint); // find the edge before the edge with endpoint and return a pointer to it
void print_edges(pedge head);                       // print all edges in list

#endif