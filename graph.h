#ifndef GRAPH_
#define GRAPH_

#define INT_MIN -2147483648 //integer min value
#define INT_MAX 2147483647 //integer max value

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

void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);

// ---------- helper functions ----------
void free_node(pnode node); // free node memory
pnode find_node_before(pnode head, int node_num); // find node before node_num
pnode find_node(pnode head, int node_num); // find node with node_num
void insert_node(pnode *head, pnode new_node); // insert node into graph
pnode create_node(int node_num, pnode to1, int edge1_w, pnode to2, int edge2_w); 
void build_empty_graph(pnode *head, int size); // build graph with size nodes. each node has no edges
void disconnect_node(pnode head, int node_num); // disconnect node from graph


#endif
