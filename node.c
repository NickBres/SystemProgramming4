#include <stdlib.h>
#include "node.h"
#include "edge.h"

pnode create_node(int node_num)
{
    pnode new_node = (pnode)malloc(sizeof(node));
    new_node->node_num = node_num;

    new_node->edges = NULL;
    new_node->next = NULL;

    new_node->d = -1; // used for dijkstra
    new_node->isVisited = -1;

    return new_node;
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

void disconnect_node(pnode head, pnode nodeToDisconnect)
{
    pnode temp = head;
    while (temp != NULL) // look for nodes with edges to node_num
    {
        if (temp->edges != NULL)
        {
            pedge edge = find_edge_to(temp->edges, nodeToDisconnect);
            if (edge != NULL) // node has edge to nodeToDisconnect
            {
                if (edge == temp->edges) // edge is head
                {
                    temp->edges = edge->next;
                }
                else // edge is not head
                {
                    pedge before = find_edge_before(temp->edges, edge->endpoint);
                    before->next = edge->next;
                }
                free(edge);
            }
        }
        temp = temp->next;
    }
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
    disconnect_node(*head, node); // find nodes with edges to node and disconnect them
    free_edges(node->edges);
    free(node);
};