#include <stdio.h>
#include "graph.h"
#include "algo.h"

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
        char c;
        scanf(" %c", &c); // get command n to add data to node
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
        pnode new_node = create_node(i, NULL, INT_MAX, NULL, INT_MAX); // create node with no edges
        insert_node(head, new_node);                                   // insert node to graph
    }
};

pnode create_node(int node_num, pnode to1, int edge1_w, pnode to2, int edge2_w)
{
    pnode new_node = (pnode)malloc(sizeof(node));
    new_node->node_num = node_num;

    pedge pedges = malloc(2 * sizeof(edge)); // allocate space for 2 edges
    pedges[0].endpoint = to1;                // set the first edge
    pedges[0].weight = edge1_w;
    pedges[0].next = pedges + 1;
    pedges[1].endpoint = to2; // set the second edge
    pedges[1].weight = edge2_w;
    pedges[1].next = NULL;
    new_node->edges = pedges;

    new_node->next = NULL;

    new_node->d = -1; // used for dijkstra
    new_node->isVisited = -1;

    return new_node;
};

void insert_node_cmd(pnode *head)
{
    int node_num;
    int to1, edge1_w, to2, edge2_w;
    scanf("%d %d %d %d %d", &node_num, &to1, &edge1_w, &to2, &edge2_w); // read input
    pnode first = find_node(*head, to1);                                // find the nodes to connect to
    pnode second = find_node(*head, to2);
    if (first == NULL || second == NULL)
    {
        printf("0.Error: node %d or %d does not exist\n", to1, to2);
        exit(1);
    }

    pnode curr = find_node(*head, node_num); // find the node to connect
    if (curr != NULL)                        // node already exists - update edges
    {
        curr->edges[0].endpoint = first;
        curr->edges[0].weight = edge1_w;
        curr->edges[1].endpoint = second;
        curr->edges[1].weight = edge2_w;
    }
    else
    { // node does not exist - create new node
        curr = create_node(node_num, first, edge1_w, second, edge2_w);
        insert_node(head, curr); // insert new node to graph
    }
};

void insert_node(pnode *head, pnode new_node)
{
    if (*head == NULL) // empty list
    {
        *head = new_node;
    }
    else
    {
        pnode temp = *head;
        while (temp->next != NULL) // find last node
        {
            temp = temp->next;
        }
        temp->next = new_node; // insert new node
    }
};

pnode find_node(pnode head, int node_num)
{
    if (head == NULL)
    { // empty list
        return NULL;
    }
    if (head->node_num == node_num) // node is head
    {
        return head;
    }
    pnode before = find_node_before(head, node_num); // node is not head
    if (before == NULL)                              // node not found
    {
        return NULL;
    }
    return before->next; // node found
};

pnode find_node_before(pnode head, int node_num)
{
    if (head == NULL)
    { // empty list
        return NULL;
    }
    pnode temp = head;
    while (temp->next != NULL)
    {
        if (temp->next->node_num == node_num)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
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

void free_node(pnode *head, pnode node)
{
    if (node == *head) // node is head
    {
        *head = node->next;
    }
    else // node is not head
    {
        pnode before = find_node_before(*head, node->node_num);
        before->next = node->next;
    }
    disconnect_node(*head, node->node_num); // find nodes with edges to node and disconnect them
    free(node->edges);
    free(node);
};
void disconnect_node(pnode head, int node_num)
{
    pnode temp = head;
    while (temp != NULL && temp->edges != NULL) // look for nodes with edges to node_num
    {
        for (int i = 0; i < 2; i++)
        {
            if (temp->edges[i].endpoint != NULL && temp->edges[i].endpoint->node_num == node_num)
            { // disconnect node
                temp->edges[i].endpoint = NULL;
                temp->edges[i].weight = 0;
            }
        }
        temp = temp->next;
    }
};
void printGraph_cmd(pnode head)
{
    pnode temp = head;
    while (temp != NULL)
    {
        printf("Node %d: ", temp->node_num);
        for (int i = 0; i < 2; i++)
        {
            if (temp->edges[i].endpoint != NULL)
            {
                printf("Edge to %d (%d), ", temp->edges[i].endpoint->node_num, temp->edges[i].weight);
            }
        }
        printf("\n");
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