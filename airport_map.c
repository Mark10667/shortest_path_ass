// #include "shortest_path.h"
//
//
//
// void create_graph(char* s1, char* s2, int distance, struct graph g){
//   struct vertex* v1 = g.ver_arr[(s1[0]-65)*1 + (s1[1]-65)*26 + (s1[2]-65)*26*26];
//   //struct vertex v2 = g.ver_arr[(s2[0]-65)*1 + (s2[1]-65)*26 + (s2[2]-65)*26*26];
//   struct adj_edge* n = malloc(sizeof(struct adj_edge));
//   n-> distance = distance;
//   n-> adj_id = (s2[0]-65)*1 + (s2[1]-65)*26 + (s2[2]-65)*26*26;
//   v1->adj_arr[v1->adjnum] = *n;
//   v1->adjnum++;
//   printf("adjum is %d\n", v1->adjnum);
// }
//
// struct min_heap_node* create_heapnode(int v, int d){
//   struct min_heap_node* newnode = malloc(sizeof(struct min_heap_node));
//   newnode->vindex = v;
//   newnode->dist = d;
//   return newnode;
// }
//
// struct min_heap* create_minheap(int capacity){
//   struct min_heap* newheap = malloc(sizeof(struct min_heap));
//   newheap->capacity = capacity;
//   newheap->size = 0;
//   newheap->min_array = malloc(sizeof(struct min_heap_node* )*capacity);
//   return newheap;
// }
//
// void swap(struct min_heap_node** a, struct min_heap_node** b){
//   struct min_heap_node* t = *a;
//   *a = *b;
//   *b = t;
//   int n = (*a) -> vindex;
//   (*a) -> vindex = (*b) -> vindex;
//   (*b) -> vindex = n;     // not sure if changing the index would work, or do I need to create another position array;
// }
//
// void siftup(struct min_heap* heap, int vindex){
//   int i = vindex;
//   while(vindex > 0 && heap->min_array[(i-1)/2] > heap->min_array[i]){
//     swap(&heap->min_array[(i-1)/2], &heap->min_array[i]);
//     i = (i-1)/2;
//   }
// }
//
// void siftdown(struct min_heap* heap, int vindex){
//   int minindex = vindex;
//   int leftchild = 2*vindex;
//   int rightchild = 2*vindex;
//   if(leftchild<=(heap->size) && (heap->min_array[minindex]->dist) > (heap->min_array[leftchild]->dist)){
//     minindex = leftchild;
//   }
//   if(rightchild<=(heap->size) && (heap->min_array[minindex]->dist) > (heap->min_array[rightchild]->dist)){
//     minindex = rightchild;
//   }
//   if(minindex != vindex){
//     swap(&heap->min_array[minindex], &heap->min_array[vindex]);
//     siftdown(heap, minindex);
//   }
// }
//
// int ifempty(struct min_heap* heap){
//   return 0 == heap->size;
// }
//
// struct min_heap_node* extractmin(struct min_heap* heap){
//   struct min_heap_node* result = heap->min_array[(heap->size)-1];
//   swap(&heap->min_array[0], &heap->min_array[(heap->size)-1]);
//   heap->size--;
//   siftdown(heap, 0);
//   return result;
// }
//
// void update_dist(struct min_heap* heap, int v, int d){
//   int old = heap->min_array[v]->dist;
//   heap->min_array[v]->dist = d;
//   if(old>d){
//     siftup(heap, v);
//   }else{
//     siftdown(heap, v);
//   }
// }


#include "shortest_path.h"

void create_graph(char* s1, char* s2, int distance, struct graph g){
  struct vertex* v1 = g.ver_arr[(s1[0]-65)*1 + (s1[1]-65)*26 + (s1[2]-65)*26*26];
  //struct vertex v2 = g.ver_arr[(s2[0]-65)*1 + (s2[1]-65)*26 + (s2[2]-65)*26*26];
  struct adj_edge* n = malloc(sizeof(struct adj_edge));
  n-> distance = distance;
  n-> adj_id = (s2[0]-65)*1 + (s2[1]-65)*26 + (s2[2]-65)*26*26;
  v1->adj_arr[v1->adjnum] = *n;
  v1->adjnum++;
  printf("name of depart is %s, name of destination is %s, distance between is %d", v1->name, g.ver_arr[n-> adj_id]->name, distance);
  printf("adjum is %d\n", v1->adjnum);
}

struct min_heap* create_minheap(int capacity){
  struct min_heap* newheap = malloc(sizeof(struct min_heap));
  newheap->capacity = capacity;
  newheap->size = 0;
  newheap->min_array = malloc(sizeof(struct vertex*)*capacity);
  return newheap;
}

void swap(struct vertex** a, struct vertex** b){
  struct vertex* t = *a;
  *a = *b;
  *b = t;
}

void siftup(struct min_heap* heap, int index){
  //printf("index in siftup is %d\n", index);
  int i = index;
  //printf("inside siftup, vertex parent total_distance is %d\n", (heap->min_array[(i-1)/2])->id);
  //printf("inside siftup, vertex child total_distance is %d\n", (heap->min_array[i])->total_distance);

  while(i > 0 && (heap->min_array[(i-1)/2]->total_distance) > (heap->min_array[i]->total_distance)){
    //puts("inside siftup while loop");
    swap(&heap->min_array[(i-1)/2], &heap->min_array[i]);
    i = (i-1)/2;
  }
}

void siftdown(struct min_heap* heap, int vindex){
  int minindex = vindex;
  int leftchild = 2*vindex+1;
  int rightchild = 2*vindex+2;
  //printf("%d %d %d", minindex, leftchild, rightchild);
  if(leftchild<(heap->size) && ((heap->min_array[minindex]->total_distance) > (heap->min_array[leftchild]->total_distance))){
    minindex = leftchild;
  }
  if(rightchild<(heap->size) && ((heap->min_array[minindex]->total_distance) > (heap->min_array[rightchild]->total_distance))){
    minindex = rightchild;
  }
  if(minindex != vindex){
    swap(&heap->min_array[minindex], &heap->min_array[vindex]);
    siftdown(heap, minindex);
  }
}

int ifempty(struct min_heap* heap){
  return 0 == heap->size;
}

struct vertex* extractmin(struct min_heap* heap){
  struct vertex* result = heap->min_array[0];
  swap(&heap->min_array[0], &heap->min_array[(heap->size)-1]);
  heap->size--;
  siftdown(heap, 0);
  //puts("inside extractmin");
  //printf("inside extractmin, %d\n", result->id);
  return result;
}

int insert(struct min_heap* heap, struct vertex* v){
  if(heap->size == heap->capacity){
    return 1;
  }
  heap->min_array[heap->size] = v;
  heap->size++;
  // printf("the size of heap is %d\n", heap->size);
  // printf("id of my first v is %d\n", v->id);
  // printf("adjum of my first v is %d\n", v->adjnum);
  // printf("total_distance of my first v is %d\n", heap->min_array[heap->size-1]->total_distance);
  siftup(heap, heap->size-1);
  return 0;
}

void update_dist(struct min_heap* heap, int v, int d){
  int old = heap->min_array[v]->total_distance;
  heap->min_array[v]->total_distance = d;
  if(old>d){
    siftup(heap, v);
  }else{
    siftdown(heap, v);
  }
}
