#include <stdio.h>
#include "graph.h"

int main(void)
{

    pnode head = NULL;

    while (1)
    {
        char c;
        printf("Enter command: ");
        scanf(" %c", &c);

        if (c == 'A')
        {
            // create graph
            build_graph_cmd(&head);
        }
        else if (c == 'B')
        {
            // add new node to graph
            insert_node_cmd(&head);
        }
        else if (c == 'D')
        {
            // delete node from graph
            delete_node_cmd(&head);
        }
        else if (c == 'S')
        {
            // shortest path
            shortsPath_cmd(head);
        }
        else if (c == 'T')
        {
            // travelling salesman problem
            TSP_cmd(head);
        }
        else if (c == 'P')
        {
            // print graph
            printGraph_cmd(head);
        }
        else
        {
            // quit
            break;
        }
    }

    return 0;
};