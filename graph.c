#include <stdio.h>
#include "graph.h"
#include "algo.h"

void build_graph_cmd(pnode *head)
{
    if (*head != NULL)
    {
        deleteGraph_cmd(head);
    }
    int size;
    //printf("Enter number of nodes: ");
    scanf("%d", &size);

    build_empty_graph(head, size);

    while (1)
    {
        char c;
        //printf("Enter n to add node, any other key to quit: ");
        scanf(" %c", &c);
        if (c != 'n')
        {
            break;
        }
        insert_node_cmd(head);
    }
};

void build_empty_graph(pnode *head, int size)
{
    //printf("Building empty graph with %d nodes\n", size);
    for (int i = 0; i < size; i++)
    {
        pnode new_node = create_node(i, NULL, 0, NULL, 0);
        insert_node(head, new_node);
    }
};

pnode create_node(int node_num, pnode to1, int edge1_w, pnode to2, int edge2_w)
{
    pnode new_node = (pnode)malloc(sizeof(node));
    new_node->node_num = node_num;

    pedge pedges = malloc(2 * sizeof(edge));
    pedges[0].endpoint = to1;
    pedges[0].weight = edge1_w;
    pedges[0].next = pedges + 1;
    pedges[1].endpoint = to2;
    pedges[1].weight = edge2_w;
    pedges[1].next = NULL;
    new_node->edges = pedges;

    new_node->next = NULL;
    new_node->d = -1;
    new_node->isVisited = -1;
    return new_node;
};

void insert_node_cmd(pnode *head)
{
    //printf("Inserting node\n");
    int node_num;
    int to1, edge1_w, to2, edge2_w;
   // printf("Enter node number: ");
    scanf("%d", &node_num);
   // printf("Enter node to 1: ");
    scanf("%d", &to1);
   // printf("Enter edge 1 weight: ");
    scanf("%d", &edge1_w);
    //printf("Enter node to 2: ");
    scanf("%d", &to2);
    //printf("Enter edge 2 weight: ");
    scanf("%d", &edge2_w);
    //printf("Inserting node %d with edges to %d (%d) and %d (%d)\n", node_num, to1, edge1_w, to2, edge2_w);
    pnode first = find_node(*head, to1);
    pnode second = find_node(*head, to2);
    if (first == NULL || second == NULL)
    {
        printf("0.Error: node %d or %d does not exist\n", to1, to2);
        exit(1);
    }
    pnode curr = find_node(*head, node_num);
    if (curr != NULL)
    {
        curr->edges[0].endpoint = first;
        curr->edges[0].weight = edge1_w;
        curr->edges[1].endpoint = second;
        curr->edges[1].weight = edge2_w;
    }
    else
    {
        curr = create_node(node_num, first, edge1_w, second, edge2_w);
        insert_node(head, curr);
    }
};

void insert_node(pnode *head, pnode new_node)
{
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        pnode temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
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
    //printf("Deleting node\n");
    int node_num;
    //printf("Enter node number: ");
    scanf("%d", &node_num);

    if ((*head)->node_num == node_num)
    { // node is head
        pnode temp = *head;
        *head = (*head)->next;
        free_node(temp);
        return;
    }
    pnode before = find_node_before(*head, node_num);
    if (before == NULL)
    { // node not found
        printf("1.Error: node %d does not exist\n", node_num);
        exit(1);
    }
    // node is not head
    pnode temp = before->next;
    before->next = temp->next;
    free_node(temp);
    return;
};

void free_node(pnode node)
{
    disconnect_node(node, node->node_num);
    free(node->edges);
    free(node);
};
void disconnect_node(pnode head, int node_num)
{
    pnode temp = head;
    while (temp != NULL) // look for nodes with edges to node_num
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
    //printf("Printing graph\n");
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
}; // for self debug
void deleteGraph_cmd(pnode *head)
{
    pnode temp = *head;
    while (temp != NULL)
    {
        pnode next = temp->next;
        free_node(temp);
        temp = next;
    }
    *head = NULL;
};
void shortsPath_cmd(pnode head)
{
    //printf("Enter first node: ");
    int node1;
    scanf("%d", &node1);
    //printf("Enter second node: ");
    int node2;
    scanf("%d", &node2);

    pnode first = find_node(head, node1);
    pnode second = find_node(head, node2);
    if (first == NULL || second == NULL)
    {
        printf("2.Error: node %d or %d does not exist\n", node1, node2);
        exit(1);
    }
    dijkstra(head, first);
    printf("Dijsktra shortest path: %d \n", second->d == INT_MAX ? -1 : second->d);

};
void TSP_cmd(pnode head){
    //printf("Enter number of nodes to visit: ");
    int num;
    scanf("%d", &num);
    int *nodes = (int *)malloc(sizeof(int) * num);
    //printf("Enter nodes to visit: ");
    for (int i = 0; i < num; i++)
    {
        scanf("%d", &nodes[i]);
    }
    int bestRoute = find_best_route(head, nodes, num);
    printf("TSP shortest path: %d \n", bestRoute == INT_MAX ? -1 : bestRoute);
};