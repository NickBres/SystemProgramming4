#ifndef NODE_H
#define NODE_H

#include "graph.h"

pnode create_node(int node_num);                          // create a new node with node_num and return a pointer to it
void insert_node(pnode *head, pnode new_node);            // insert a node to the end of the list
pnode find_node(pnode head, int node_num);                // find a node with node_num and return a pointer to it
pnode find_node_before(pnode head, int node_num);         // find the node before the node with node_num and return a pointer to it
void free_node(pnode *head, pnode node);                  // free a node and all its edges

#endif