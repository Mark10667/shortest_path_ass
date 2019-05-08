#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// dijkstra.c
// struct vertex{
//   int id;
//   char name[10];
//   int total_distance;
//   struct adj_edge* adj_arr;
//   int adjnum;
//   int previous_id;   // -1 is for source, a real number is its previous_id.
//   int status; // 0 is undiscovered, 1 is discovered, 2 is processed.
// };
//
// struct graph{
//   int N; // number of total vertices
//   struct vertex** ver_arr; // all of the airports
// };
//
struct adj_edge{
  int adj_id;
  int distance;
};

struct min_heap{
  int capacity;
  int size;
  //int position; // be an array
  struct vertex ** min_array;
};


// bellman.case
struct vertex{
  int id;
  char name[10];
  int total_distance;
  struct adj_edge* adj_arr;
  int adjnum;
  int previous_id;   // -1 is for source, a real number is its previous_id.
  int status; // 0 is undiscovered, 1 is discovered, 2 is processed.
};

struct graph{
  int V; // number of total vertices
  int E; // number of total edges
  int table[26*26*26];
  struct vertex** ver_arr; // all of the airports
  struct edge** edge_arr;
};

struct edge{
  int src;
  int dest;
  int distance;
};

//struct min_heap_node* create_heapnode(int v, int d);

struct min_heap* create_minheap(int capacity);

void swap(struct vertex** a, struct vertex** b);

void siftup(struct min_heap* heap, int vindex);

void siftdown(struct min_heap* heap, int vindex);

int ifempty(struct min_heap* heap);

struct vertex* extractmin(struct min_heap* heap);

int insert(struct min_heap* heap, struct vertex* v);

void update_dist(struct min_heap* heap, int v, int d);

void create_graph(char* s1, char* s2, int distance, struct graph g);

int min(int a, int b);

void dijkstra(struct graph* g, int start);

// bellman.c
char* substring(char s[], int start, int length);

void create_bellmangraph(char* s1, char* s2, int distance, struct graph g, int m);

void bellman(struct graph g, int source, int dest);

void freeall(struct graph g);

#endif
