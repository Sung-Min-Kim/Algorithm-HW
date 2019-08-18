#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _Node* Nptr;
typedef struct _Node{
  int node; // indicate which node it is.
  Nptr next; // a pointer to the next node in the array of adjacency list.
}Node;

int orig_arr[7][7];
int trans_arr[7][7];

int main(void){
    FILE *fp = fopen("hw4.data", "r");
    char buf[128];
    int node_num = 0;

    /* Parsing Firstline -> Figure out the number of nodes */
    fgets(buf, sizeof(buf), fp);
    char *token;

    token = strtok(buf, "\t");
    node_num++;

    while( token != NULL ) {
        token = strtok(NULL, "\t");
        if(token == NULL)
          break;

        node_num++;
    }


    int row_cnt = 0;
    int col_cnt = 0;
    while(1){
        fgets(buf, sizeof(buf), fp); // Reading data from the input file line by line

        token = strtok(buf, "\t");

        char present_node;
        char temp[32];
        strcpy(temp, token);
        present_node = temp[0];
        present_node = toupper(present_node);
        int idx = present_node - 'A';

        col_cnt = 0;
        /* To save relation of the node in the adj list */
        for(int i = 0; i < node_num; i++) {
            token = strtok(NULL, "\t");

            strcpy(temp, token);
            int num = atoi(temp);
            orig_arr[row_cnt][col_cnt] = num;
            col_cnt++;

        }
        row_cnt++;

        if(feof(fp))
            break;
    }


    for(int i = 0; i < 7; i++){
      for(int j = 0; j < 7; j++){
        trans_arr[j][i] = orig_arr[i][j];
      }
    }

    Nptr orig_list[7];
    Nptr trans_list[7];

    for(int i = 0; i < 7; i++){
      orig_list[i] = NULL;
      trans_list[i] = NULL;
    }

    /* 원래 그래프 adjacency list */
    Nptr ptr = NULL;
    for(int i = 0; i < 7; i++){
      for(int j = 0; j < 7; j++){
        if(orig_arr[i][j] == 1){
          Nptr temp = (Nptr)malloc(sizeof(Node));
          if(temp == NULL){
            perror("Memory Allocation Failed");
            exit(0);
          }
          temp->node = j;
          temp->next = NULL;

          if(orig_list[i] == NULL){ // 리스트가 비어있는 경우
            orig_list[i] = temp;
            ptr = temp;
          }else{ //리스트에 이미 있는 경우
            ptr->next = temp;
            ptr = temp;
          }
        }
      }
    }

    printf("***** Array of adjacency list of original graph *****\n\n");
    for(int i = 0; i < 7; i++){
      ptr = orig_list[i];
      if(ptr != NULL)
        printf("%c -> ", i + 'A');
      else
        printf("%c", i + 'A');

      while(ptr != NULL){
        if(ptr->next != NULL)
          printf("%c -> ", ptr->node + 'A');
        else
          printf("%c", ptr->node + 'A');
        ptr = ptr->next;
      }
      printf("\n");
    }

    /* Transpose 그래프 adjacency list */
    for(int i = 0; i < 7; i++){
      for(int j = 0; j < 7; j++){
        if(trans_arr[i][j] == 1){
          Nptr temp = (Nptr)malloc(sizeof(Node));
          if(temp == NULL){
            perror("Memory Allocation Failed");
            exit(0);
          }
          temp->node = j;
          temp->next = NULL;

          if(trans_list[i] == NULL){ // 리스트가 비어있는 경우
            trans_list[i] = temp;
            ptr = temp;
          }else{ //리스트에 이미 있는 경우
            ptr->next = temp;
            ptr = temp;
          }
        }
      }
      printf("\n");
    }

    printf("***** Array of adjacency list of transpose graph *****\n\n");
    for(int i = 0; i < 7; i++){
      ptr = trans_list[i];
      if(ptr != NULL)
        printf("%c -> ", i + 'A');
      else
        printf("%c", i + 'A');

      while(ptr != NULL){
        if(ptr->next != NULL)
          printf("%c -> ", ptr->node + 'A');
        else
          printf("%c", ptr->node + 'A');
        ptr = ptr->next;
      }
      printf("\n");
    }

    /* Free the nodes */
    Nptr orig1, orig2, trans1, trans2;
    for(int i = 0; i < 7; i++){
      orig1 = orig_list[i];
      trans1 = trans_list[i];

      while(orig1 != NULL && trans1 != NULL){
        orig2 = orig1->next;
        trans2 = trans1->next;
        free(orig1);
        free(trans1);
        orig1 = orig2;
        trans1 = trans2;
      }
    }


    fclose(fp);

    return 0;
}
