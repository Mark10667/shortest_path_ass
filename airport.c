#include "shortest_path.h"

// char* substring(char s[], int start, int length){
//   int c = 0;
//   char b[50];
//   while(c < length){
//     b[c] = s[start-1+c];
//     c++;
//   }
//   b[c] = '\0';
//   return b;
// }

int main(int argc, char **argv){
  puts("There are 4 commands to use this program.\n 1)help: prints out a help message on how to use your system.\n 2)quit: quits the program.\n 3)airports: prints all airports serviced by FTA.\n 4)distance <airport1> <airport2>: prints the shortest path from one airport to another\n");

  struct graph g;
  g.ver_arr = malloc(sizeof(struct vertex*)*500);
  g.edge_arr = malloc(sizeof(struct edge*)*6000);

  FILE* f1 = fopen("large-airports.txt", "r");
  if(f1 == NULL){
    printf("Error opening file. \n");
    return 1;
  }
  char s1[100];
  char s2[100];
  int d3;
  int i = 0;

// read airports info in small-airports
  while(fscanf(f1, "%s %[^\n]s", s1, s2)!=EOF){
    //printf("%s: %s", s1, s2);
    struct vertex* v = malloc(sizeof(struct vertex));
    strcpy(v->name, s1);
    v->id = (s1[0]-65)*1 + (s1[1]-65)*26 + (s1[2]-65)*26*26;
    //printf("  id is %d\n", v->id);
    //v->adj_arr = malloc(sizeof(struct adj_edge) * 399);
    v->adjnum = 0;
    v->previous_id = -1;
    v->total_distance = INT_MAX;
    v->status = 0; //undiscovered
    g.table[v->id] = i;
    g.ver_arr[i] = v;
    i++;
  }
  //printf("the total number of airports is %d\n ", i);
  g.V = i;
  fclose(f1);
// create the graph using small-dists.txt
  FILE* f2 = fopen("large-dists.txt", "r");
  if(f2 == NULL){
    printf("Error opening file. \n");
    return 1;
  }

  int m = 0;
  while(fscanf(f2, "%s %s %d", s1, s2, &d3)!=EOF){
    //printf("%s %s %d\n", s1, s2, d3);
    create_bellmangraph(s1, s2, d3, g, m);
    m++;
    create_bellmangraph(s2, s1, d3, g, m);
    m++;
  }
  //printf("The total number of connections between airports is %d\n", m);
  g.E = m;

  fclose(f2);

  char s3[100];
  char s4[100];

  while(1){

    char input[50];
    puts("Please input your command:");
    fgets(input, 100, stdin);
    //printf("My input is %s\n", input);
    int length = strlen(input);
    //printf("input length is %d\n", length);
    input[length-1] = '\0';
    if(strcmp(input, "help") == 0){
      puts("There are 4 commands to use this program.\n 1)help: prints out a help message on how to use your system.\n 2)quit: quits the program.\n 3)airports: prints all airports serviced by FTA.\n 4)distance <airport1> <airport2>: prints the shortest path from one airport to another\n");
    }
    else if(!strcmp(input, "quit")){
      puts("See you :) \n");
      break;
    }
    else if(!strcmp(input, "airports")){
      FILE* f3 = fopen("large-airports.txt", "r");
      while(fscanf(f3, "%s %[^\n]s", s3, s4)!=EOF){
        printf("%s: %s\n", s3, s4);
      }
      fclose(f3);
    }else if(length > 12){
      char* tok1;
      tok1 = strtok(input, " ");
      char* tok2;
      tok2 = strtok(0, " ");
      char* tok3;
      tok3 = strtok(0, " ");

      int a = (tok2[0]-65)*1 + (tok2[1]-65)*26 + (tok2[2]-65)*26*26;
      int b = (tok3[0]-65)*1 + (tok3[1]-65)*26 + (tok3[2]-65)*26*26;
      //printf("a and b are %d and %d", a, b);

      bellman(g, g.table[b], g.table[a]);
    }
    //dijkstra(&g, 0*1 + 11*26 + 1*26*26);
    // void print_arr(g, 0*1 + 11*26 + 1*26*26){
    // }
  }
  freeall(g);
  return 0;
}
