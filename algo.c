#include "algo.h"


int find_best_route(pnode head,int* nodes,int size){
    int ** possible_routes = get_permutations(nodes,size);
    int number_of_routes = number_of_permutations(size);
    int best_route = INT_MAX;

    for(int i = 0; i < number_of_routes; i++){
        if(i % (number_of_routes/size) == 0){ // routes that starts with the same node
            dijkstra(head,find_node(head,nodes[i]));
        }
        if(find_node(head,possible_routes[i][size - 1])->d != INT_MAX){ // if there is a route to the last node
            int route = 0;
            for(int j = 0;j < size - 1;j++){
                pnode from = find_node(head,possible_routes[i][j]);
                dijkstra(head,from);
                pnode to = find_node(head,possible_routes[i][j + 1]);
                if(to->d == INT_MAX){ // if there is no route to the next node
                    route = INT_MAX;
                    break;
                }
                route += to->d;
            }
            if(route < best_route){
                best_route = route;
            }
        }
    }
    return best_route;
}

int number_of_permutations(int size){
    int result = 1;
    for(int i = 1; i <= size; i++){
        result *= i;
    }
    return result;
}

void dijkstra(pnode head,pnode start)
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

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void permute(int *arr, int l, int r, int ***result, int *count) {
  if (l == r) {
    // Allocate space for a new permutation
    *result = (int **)realloc(*result, sizeof(int *) * (*count + 1));
    (*result)[*count] = (int *)malloc(sizeof(int) * (r + 1));

    // Add the permutation to the result
    for (int i = 0; i <= r; i++) {
      (*result)[*count][i] = arr[i];
    }
    (*count)++;
  } else {
    for (int i = l; i <= r; i++) {
      swap(&arr[l], &arr[i]);
      permute(arr, l + 1, r, result, count);
      swap(&arr[l], &arr[i]);
    }
  }
}

int **get_permutations(int *arr, int size) {
  int **result = NULL;
  int count = 0;
  permute(arr, 0, size - 1, &result, &count);
  return result;
}



