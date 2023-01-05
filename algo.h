#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int find_best_route(pnode head,int* nodes,int size); // looking for the best route in graph with given nodes
int **get_permutations(int *arr, int size); // generate all permutations of given array
int number_of_permutations(int size); // number of permutations of given size
void dijkstra(pnode head,pnode start); // dijkstra algorithm
pnode find_min_not_visited(pnode head); // find the node with the smallest distance that is not visited
void swap(int *a, int *b); // swap two integers
void permute(int *arr, int l, int r, int ***result, int *count); // generate all permutations of given array