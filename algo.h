#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

#define INT_MIN -2147483648 //integer min value
#define INT_MAX 2147483647 //integer max value

void dijkstra(pnode head,pnode start); // dijkstra algorithm
pnode find_min_not_visited(pnode head); // find the node with the smallest distance that is not visited
int find_best_route(pnode head,int* nodes,int size); // looking for the best route in graph with given nodes
void swap(int *a, int *b); // swap two integers
int **get_permutations(int *arr, int size); // generate all permutations of given array permute function wrapper
void permute(int *arr, int l, int r, int ***result, int *count); // generate all permutations of given array in recursive way
int number_of_permutations(int size); // number of permutations of given size
void free_permutations(int **permutations, int size); // free all permutations