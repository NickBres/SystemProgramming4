#include "graph.h"
#include <stdio.h>
pnode find_min_not_visited(pnode head);
void *dijkstra(pnode head,pnode start)
{
    if (start == NULL)
    {
        return;
    }
    // initialize nodes
    pnode temp = head;
    while (temp != NULL)
    {
        int flag = 1;
        pedge temp_edge = start->edges;
        while (temp_edge != NULL)
        {
            if (temp_edge->endpoint != NULL && temp_edge->endpoint->node_num == temp->node_num)
            {
                temp->d = temp_edge->weight;
                flag = 0;
                break;
            }
            temp_edge = temp_edge->next;
        }
        if (flag){
            temp->d = INT_MAX;
        }
    
        temp->isVisited = 0;
        temp = temp->next;
    }
    start->d = 0;
    start->isVisited = 1;
    while(1){
        pnode min = find_min_not_visited(head);
       
        if (min == NULL)
        {
            break;
        }
        min->isVisited = 1;
        pedge temp_edge = min->edges;
        
        while (temp_edge != NULL)
        {
            if (temp_edge->endpoint != NULL)
            { 
                int weight = min->d == INT_MAX ? INT_MAX : min->d + temp_edge->weight;
                if (temp_edge->endpoint->d > weight)
                {
                    temp_edge->endpoint->d = weight;
                }
            }
            temp_edge = temp_edge->next;
        }
    }

}

pnode find_min_not_visited(pnode head)
{
    pnode min = NULL;
    pnode temp = head;
    while (temp != NULL)
    {
        if (temp->isVisited == 0)
        {
            if (min == NULL)
            {
                min = temp;
            }
            else if (temp->d < min->d)
            {
                min = temp;
            }
        }
        temp = temp->next;
    }
    return min;
}


