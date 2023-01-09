#include <stdio.h>
#include <stdlib.h>
#include "algo.h"
#include "node.h"

int find_best_route(pnode head, int *nodes, int size)
{
    int **possible_routes = get_permutations(nodes, size); // get all possible routes
    int number_of_routes = number_of_permutations(size);   // number of possible routes
    int best_route = INT_MAX;                              // best route weight

    for (int i = 0; i < number_of_routes; i++)
    { // for each route
        if (i % (number_of_routes / size) == 0)
        { // routes that starts with the same node
            dijkstra(head, find_node(head, possible_routes[i][0]));
        }
        if (find_node(head, possible_routes[i][size - 1])->d != INT_MAX)
        { // if there is a route from first to the last node, check the routes between them
            int route = 0;
            for (int j = 0; j < size - 1; j++)
            {
                pnode from = find_node(head, possible_routes[i][j]);
                dijkstra(head, from); // find routes from the current node
                pnode to = find_node(head, possible_routes[i][j + 1]);
                if (to->d == INT_MAX)
                { // if there is no route to the next node
                    route = INT_MAX;
                    break;
                }
                route += to->d; // add the weight of the route
            }
            if (route < best_route) // if the route is better than the best route
            {
                best_route = route;
            }
        }
    }
    free_permutations(possible_routes, number_of_routes); // free memory
    return best_route;
}

int number_of_permutations(int size) // nuber of permutations is n!
{
    int result = 1;
    for (int i = 1; i <= size; i++)
    {
        result *= i;
    }
    return result;
}

void dijkstra(pnode head, pnode start)
{
    if (start == NULL) // if start node does not exist
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
            if (temp_edge->endpoint != NULL && temp_edge->endpoint->node_num == temp->node_num) // if there is an edge from start node to the current node
            {
                temp->d = temp_edge->weight; // set the weight of the route
                flag = 0;                    // do not set the weight to INT_MAX
                break;
            }
            temp_edge = temp_edge->next; // check the next edge
        }
        if (flag)
        {
            temp->d = INT_MAX;
        }

        temp->isVisited = 0; // set the node as not visited
        temp = temp->next;   // check the next node
    }
    start->d = 0;         // set the weight of the start node to 0
    start->isVisited = 1; // set the start node as visited
    while (1)
    {
        pnode min = find_min_not_visited(head); // find the node with the smallest weight

        if (min == NULL) // if there is no node with the smallest weight (all nodes are visited)
        {
            break;
        }
        min->isVisited = 1;           // set the node as visited
        pedge temp_edge = min->edges; // check the edges of the node

        while (temp_edge != NULL)
        {
            if (temp_edge->endpoint != NULL)
            {
                int weight = min->d == INT_MAX ? INT_MAX : min->d + temp_edge->weight; // calculate the weight of the route
                if (temp_edge->endpoint->d > weight)                                   // if the weight of the route is smaller than the current weight
                {
                    temp_edge->endpoint->d = weight;
                }
            }
            temp_edge = temp_edge->next; // check the next edge
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

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void permute(int *arr, int l, int r, int ***result, int *count)
{
    if (l == r)
    {
        // Allocate space for a new permutation
        *result = (int **)realloc(*result, sizeof(int *) * (*count + 1));
        (*result)[*count] = (int *)malloc(sizeof(int) * (r + 1));

        // Add the permutation to the result
        for (int i = 0; i <= r; i++)
        {
            (*result)[*count][i] = arr[i];
        }
        (*count)++;
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            swap(&arr[l], &arr[i]);
            permute(arr, l + 1, r, result, count);
            swap(&arr[l], &arr[i]);
        }
    }
}

int **get_permutations(int *arr, int size)
{
    int **result = NULL;
    int count = 0; // number of permutations
    permute(arr, 0, size - 1, &result, &count);
    return result;
}

void free_permutations(int **permutations, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(permutations[i]);
    }
    free(permutations);
}
