#include <stdio.h>
#include <stdlib.h>
#define memoryExit -1

typedef struct node {
  int x;
  int y;
  struct node *next;
  struct node *prev;
} Node;

Node *head = NULL;
Node *tail = NULL;





/**********************************************************/

void pushEnd(int x, int y) {

  Node* element;

  if( (element = (Node*)malloc(sizeof(Node))) == NULL ) {
    fprintf(stderr, "To small memory\n");
    exit(memoryExit);
  }
    element->x = x;
    element->y = y;


    if (head == NULL){

        element->next = head;
        element->prev = tail;
        head = element;
        tail = element;

        return;
    }



    element -> next = head;
    element->prev = tail;
    tail->next = element;
    head->prev = element;
    tail = element;

}

/**********************************************************/


void pushFirst(int x, int y) {

  Node* element;

  if( (element = (Node*)malloc(sizeof(Node))) == NULL ) {
    fprintf(stderr, "To small memory\n");
    exit(memoryExit);
  }
    element->x = x;
    element->y = y;


    if (head == NULL){

        element->next = head;
        element->prev = tail;
        head = element;
        tail = element;

        return;
    }



    element -> next = head;
    element->prev = tail;
    tail->next = element;
    head->prev = element;
    head = element;


}

/**********************************************************/

int popEnd(){
  int defaultVaule = -1;

  if(head == NULL || tail == NULL){
    return defaultVaule;
  }



  if(head==tail)
  {
        head = NULL;
        tail = NULL;
        return defaultVaule;
  }

  head->prev = tail->prev;
  tail->prev->next = head;
  free(tail);
  tail = head->prev;
  return defaultVaule;


}

