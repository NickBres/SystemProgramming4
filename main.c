#include <stdio.h>
#include "graph.h"

int main(void)
{

    pnode head = NULL;
    char c = 'N';

    while (c != EOF)
    {
        c = getchar();

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
        else if (c != ' ')
        {
            // quit
            break;
        }
    }

    deleteGraph_cmd(&head); // free memory
    return 0;
};