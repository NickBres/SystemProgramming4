#include <stdio.h>
#include <stdlib.h>
#include "edge.h"

pedge create_edge(pnode endpoint, int weight)
{
    pedge new_edge = (pedge)malloc(sizeof(edge));
    new_edge->endpoint = endpoint;
    new_edge->weight = weight;
    new_edge->next = NULL;
    return new_edge;
};

pedge add_edge(pedge head, pedge new_edge)
{
    if(head == NULL) // empty list
    {
        head = new_edge;
        return head;
    }
    pedge temp = head;
    while (temp->next != NULL) // find last edge
    {
        temp = temp->next;
    }
    temp->next = new_edge; // insert new edge
    return head;
};

void free_edges(pedge head){
    if(head == NULL) // empty list
    {
        return;
    }
    pedge temp = head;
    while (temp->next != NULL) // go over all edges in list
    {
        pedge temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
    free(temp);
};

pedge find_edge_to(pedge head, pnode endpoint)
{
    if(head == NULL) // empty list
    {
        return NULL;
    }
    if(head->endpoint == endpoint) // edge is head
    {
        return head;
    }
    pedge before = find_edge_before(head, endpoint); // edge is not head
    return before != NULL ? before->next : NULL; // edge found
};

pedge find_edge_before(pedge head, pnode endpoint)
{
    if(head == NULL) // empty list
    {
        return NULL;
    }
    pedge temp = head;
    while (temp->next != NULL) 
    {
        if(temp->next->endpoint == endpoint)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
};

void print_edges(pedge head)
{
    pedge temp = head;
    while (temp != NULL) // go over all edges in list
    {
        printf("--> %d w: %d, ", temp->endpoint->node_num, temp->weight);
        temp = temp->next;
    }
    printf("\n");
};
