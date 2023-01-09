#include <stdio.h>
#include "graph.h"
#include "edge.h"
#include "node.h"


void build_graph_cmd(pnode *head)
{
    if (*head != NULL) // if graph already exists
    {
        deleteGraph_cmd(head);
    }
    int size;
    scanf("%d", &size); // get number of nodes

    build_empty_graph(head, size); // create size nodes with no edges

    while (1)
    {
        char c; // get command n to add data to node
        scanf(" %c", &c);
        printf(":%c\n",c);
        if (c != 'n')
        {
            break;
        }
        insert_node_cmd(head); // add data to node, if node doesn't exist, create it
    }
};

void build_empty_graph(pnode *head, int size)
{
    for (int i = 0; i < size; i++)
    {
        pnode new_node = create_node(i); 
        insert_node(head, new_node);                                  
    }
};

void insert_node_cmd(pnode *head)
{
    int node_num;
    scanf("%d", &node_num); // get node number

    pnode curr = find_node(*head, node_num); // find the node to connect
    if (curr == NULL)                        // node already exists - update edges
    {
        curr = create_node(node_num);
        insert_node(head, curr); // insert new node to graph
    }

    int endpoint_num, weight;
    // get endpoint and weight
    printf("Enter endpoint and weight (EOF to stop): \n");
    while(scanf(" %d %d", &endpoint_num, &weight) != EOF){
        pnode endpoint = find_node(*head, endpoint_num); // find endpoint node
        if (endpoint == NULL)                           // endpoint node does not exist
        {
            endpoint = create_node(endpoint_num);
            insert_node(head, endpoint); // insert new node to graph
        }
        pedge edge = find_edge_to(curr->edges, endpoint); // find edge to endpoint
        if (edge != NULL)                                // edge already exists
        {
            edge->weight = weight; // update weight
            continue;
        }
        edge = create_edge(endpoint, weight); // create edge
        add_edge(curr->edges, edge);               // add edge to node
        printf("Enter endpoint and weight (EOF to stop): \n");
    }
};



void delete_node_cmd(pnode *head)
{
    int node_num;
    scanf("%d", &node_num); // get node number to delete

    pnode node = find_node(*head, node_num);
    if (node == NULL) // node does not exist
    {
        printf("0.Error: node %d does not exist\n", node_num);
        exit(1);
    }
    free_node(head, node); // delete node
};



void printGraph_cmd(pnode head)
{
    pnode temp = head;
    while (temp != NULL)
    {
        printf("Node %d: \n     ", temp->node_num);
        print_edges(temp->edges);
        printf("d : %d , isVisited: %d\n", temp->d, temp->isVisited);
        temp = temp->next;
    }
};
void deleteGraph_cmd(pnode *head)
{
    pnode temp = *head;
    while (temp != NULL) // delete all nodes
    {
        pnode next = temp->next;
        free_node(head, temp);
        temp = next;
    }
    *head = NULL;
};
void shortsPath_cmd(pnode head)
{
    int node1, node2;
    scanf("%d %d", &node1, &node2);

    pnode first = find_node(head, node1);
    pnode second = find_node(head, node2);
    if (first == NULL || second == NULL) // node does not exist
    {
        printf("2.Error: node %d or %d does not exist\n", node1, node2);
        exit(1);
    }
    dijkstra(head, first); // find shortest path from first to all nodes. data saved in nodes
    printf("Dijsktra shortest path: %d \n", second->d == INT_MAX ? -1 : second->d);
};
void TSP_cmd(pnode head)
{
    int num;
    scanf("%d", &num); // get number of nodes to visit
    int *nodes = (int *)malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) // get nodes to visit
    {
        scanf("%d", &nodes[i]);
        if (find_node(head, nodes[i]) == NULL) // node does not exist
        {
            printf("3.Error: node %d does not exist\n", nodes[i]);
            exit(1);
        }
    }
    int bestRoute = find_best_route(head, nodes, num); // find best routes weight
    printf("TSP shortest path: %d \n", bestRoute == INT_MAX ? -1 : bestRoute);
    free(nodes); // free memory
};
