#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}



int obtenerSubmatriz(int fila, int columna) 
{
  return 3 * (fila / 3) + (columna / 3);
}


void fillSubMatriz(Node* n, int k, int subMatriz[3][3]) 
{
    for (int p = 0; p < 9; p++) {
        int i = 3 * (k / 3) + (p / 3);
        int j = 3 * (k % 3) + (p % 3);
        subMatriz[p / 3][p % 3] = n->sudo[i][j];
    }
}

int isValidMatriz(int subMatriz[3][3], int seen[10]) 
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int num = subMatriz[i][j];
            if (num != 0) {
                if (seen[num]) return 0;  
                seen[num] = 1;            
            }
        }
    }
    return 1;  
}


int is_valid(Node* n)
{
  for (int k = 0 ; k < 9 ; k ++)
  {
    int subMatriz[3][3];
    fillSubMatriz(n , k , subMatriz);
    int seen[10] = {0};
    int flag = isValidMatriz(subMatriz , seen );
    if (flag != 1) 
    {
      return 0;  
    }

    for (int i = 0 ; i < 9 ; i ++)
    {
      int seen[10] = {0};
      for(int j = 0 ; j < 9 ; j ++)
      {
        int num = n->sudo[i][j];
        if (num != 0)
        {
          if(seen[num]) return 0;
          seen[num] = 1;

        }
      }
    }

    for (int j = 0 ; j < 9 ; j ++)
    {
      int seen[10] = {0};
      for(int i = 0 ; i < 9 ; i ++)
      {
        int num = n->sudo[i][j];
        if (num != 0)
        {
          if(seen[num]) return 0;
          seen[num] = 1;  

        }
      }
    }

    
  }
  return 1;
}


List* get_adj_nodes(Node* n)
{
    List* list = createList();

    for (int k = 0; k < 9; k++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (n->sudo[k][j] == 0)
            {
                for (int num = 1; num <= 9; num++)
                {
                    Node *newState = copy(n);
                    newState->sudo[k][j] = num;
                    if(!is_valid(newState)) 
                    {
                      free(newState);
                      continue;
                    }
                    pushBack(list, newState);
                } 
            } 
        }
    } 

    return list;
}





int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/