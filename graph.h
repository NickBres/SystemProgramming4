#ifndef GRAPH_H
#define GRAPH_H

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;

    //for dijsktra
    int d;
    int isVisited;
} node, *pnode;

#define INT_MIN -2147483648 //integer min value
#define INT_MAX 2147483647 //integer max value

char build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);

// ---------- helper functions ----------
void build_empty_graph(pnode *head, int size); // build graph with size nodes. each node has no edges
void disconnect_node(pnode head, pnode nodeToDisconnect); // disconnect all edges to nodeToDisconnect


#endif
