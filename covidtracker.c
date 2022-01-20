#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct patient{
  char *name;
  struct patient *infected1;
  struct patient *infected2;
  struct patient *next;
};

struct patient *head;
struct patient *first;

patient* findNode(patient *start, char*name);
void sortNode(patient *start, patient *previous, patient*node);
void printList(patient *node);
void freeList(patient *node);
		  
int main(int argc, char *argv[]){
  struct patient *current;
  head = (struct patient*)malloc(sizeof(struct patient));
  head->name = strdup("BlueDevil");
  head->infected1 = NULL;
  head->infected2 = NULL;
  head->next = NULL;  
  first = head;
  
  FILE *file =  fopen(argv[1], "r");
  
  char* name1;
  char* name2;
  int size;
  
  while(true){
 
    name1 = (char*)malloc(30*sizeof(char));
    name2 = (char*)malloc(30*sizeof(char));
    
    fscanf(file, "%s", name1);
    fscanf(file, "%s", name2);
    
    if(strcmp(name1, "DONE") == 0){
      free(name1);
      free(name2);
      break;
    }
    
    current = findNode(head, name2);
    
    struct patient *node;
    node = (struct patient*)malloc(sizeof(struct patient));
    node->name = name1;
    node->infected1 = NULL;
    node->infected2 = NULL;
    node->next = NULL;
    
    if(current->infected1 == NULL)
      current->infected1 = node;
    else
       current->infected2 = node;

    sortNode(first, NULL, node);
    free(name2);
  } 
  printList(first);
  freeList(first);
  fclose(file);
}

patient* findNode(patient *start, char *name){ 
  if(strcmp(start->name, name) == 0)
    return start;
  
  if(start->infected1 != NULL){
     struct patient* node = findNode(start->infected1, name);
    if(node != NULL)
      return node;
  }
  if(start->infected2 != NULL)
    return findNode(start->infected2, name);

  return NULL;
}

void sortNode(patient* start, patient* previous,  patient* node){
  if(strcmp(start->name, node->name) > 0){
    node->next = start;
    if(previous == NULL)
      first = node;
    else
      previous->next = node;
  }
  else if(start->next != NULL)
    sortNode(start->next, start, node);
  else if(start->next == NULL)
    start->next = node;
}

void printList(patient* node){
  
  printf("%s ", node->name);
  patient* temp;
 
  if(node->infected2 != NULL){
    if(strcmp(node->infected2->name, node->infected1->name) > 0){
      temp = node->infected1;
      node->infected1 = node->infected2;
      node->infected2 = temp;
    }
    printf("%s ", node->infected2->name);
  }
  
  if(node->infected1 != NULL)
    printf("%s\n", node->infected1->name);
  else
    printf("\n");

  if(node->next!=NULL)
    printList(node->next);
}

void freeList(patient* node){
  if(node->next != NULL)
    freeList(node->next);
  free(node->name);
  free(node);      
}
