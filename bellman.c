#include "shortest_path.h"

void create_bellmangraph(char* s1, char* s2, int distance, struct graph g, int m){
  int v1 = g.table[(s1[0]-65)*1 + (s1[1]-65)*26 + (s1[2]-65)*26*26];
  int v2 = g.table[(s2[0]-65)*1 + (s2[1]-65)*26 + (s2[2]-65)*26*26];
  struct edge* n = malloc(sizeof(struct edge));
  n-> distance = distance;
  n-> src = v1;
  n-> dest = v2;
  g.edge_arr[m] = n;
}

void bellman(struct graph g, int source, int dest){
  int V = g.V;
  int E = g.E;
  int dist[V];
  int totald = 0;
  for(int i = 0; i < V; i++){
    dist[i] = INT_MAX;
  }
  dist[source] = 0;

  int pathv[V];
  for(int i = 0; i < V; i++){
    pathv[i] = -1;
  }

  int pathd[V];
  for(int i = 0; i < V; i++){
    pathd[i] = -1;
  }

  for(int i = 0; i < V; i++){
    for(int j = 0; j < E; j++){
      int s = g.edge_arr[j]->src;
      int d = g.edge_arr[j]->dest;
      int distance = g.edge_arr[j]->distance;
      if(dist[s] != INT_MAX && dist[s]+distance < dist[d]){
        dist[d] = dist[s]+distance;
        pathv[d] = s;
        pathd[d] = distance;
      }
    }
  }

  int i = dest;
  printf("The path from %s to %s is: ", g.ver_arr[dest]->name, g.ver_arr[source]->name);
  while(pathv[i] != -1){
    printf("%s ", g.ver_arr[i]->name);
    printf("%d ", pathd[i]);
    totald += pathd[i];
    i = pathv[i];
  }
  printf("%s \n", g.ver_arr[source]->name);
  printf("shortest total_distance is %d\n", totald);
}

void freeall(struct graph g){
  for(int i = 0; i < g.V; i++){
    free(g.ver_arr[i]);
  }
  free(g.ver_arr);
  for(int j = 0; j < g.E; j++){
    free(g.edge_arr[j]);
  }
  free(g.edge_arr);
}
