#include "shortest_path.h"

int min(int a, int b){
  if(a<b){
    return a;
  }else{
    return b;
  }
}

void dijkstra(struct graph* g, int start){
  // the distance to all of the vertices have already been set to INT_MAX
  struct min_heap* heap = create_minheap(400);
  heap-> capacity = 400;
  heap-> size = 0;
  g->ver_arr[start]->total_distance = 0;
  g->ver_arr[start]->previous_id = -1;
  insert(heap, g->ver_arr[start]);
  //heap->size++;
  while(heap->size != 0){
    struct vertex* v = extractmin(heap);
    v->status = 2; // processed
    printf("in dijkstra, extract %s\n", v->name);
    for(int i = 0; i < v->adjnum; i++){
      if(g->ver_arr[v->adj_arr[i].adj_id]->status != 2){
        (g->ver_arr[v->adj_arr[i].adj_id])->total_distance = min((g->ver_arr[v->adj_arr[i].adj_id])->total_distance, v->total_distance + v->adj_arr[i].distance);
        printf("between %s and %s, distance is %d\n", v->name, (g->ver_arr[v->adj_arr[i].adj_id])->name, (g->ver_arr[v->adj_arr[i].adj_id])->total_distance);
      }
      if(g->ver_arr[v->adj_arr[i].adj_id] -> status != 1 && g->ver_arr[v->adj_arr[i].adj_id] -> status != 2){
        insert(heap, g->ver_arr[v->adj_arr[i].adj_id]);
        printf("nodes near our extraction %s\n", g->ver_arr[v->adj_arr[i].adj_id]->name);
        //update_dist(heap, int v, v->total_distance + v->adj_arr[i]->distance);
        (g->ver_arr[v->adj_arr[i].adj_id])->status = 1; // discovered
        (g->ver_arr[v->adj_arr[i].adj_id])->previous_id = v->id;
      }
    }
  }
}
