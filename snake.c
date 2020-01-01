#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "linkedList.h" //https://github.com/xkondix/LinkedList-PYTHON-C-JAVA/blob/master/doublyLinkedList.c
#include <time.h>

//function
int checkConcactFood(int x, int y);
void createFood();
void eatFood();
void frame();
void printSnake();
int concatWithBody();
void wayMove();
void changePos();
void viewScore();

//global variables
int foodY,foodX,dy,dx,len,c;
bool quit;
char mov;

//main
int main(void)
{
  WINDOW * mainwin;

  //init ncurses
  if ( (mainwin = initscr()) == NULL ) {
    fprintf(stderr, "Error initialising ncurses.\n");
    exit(EXIT_FAILURE);
  }
  srand(time(NULL));
  noecho();         // nie pokazuj wpisywanych danych
  cbreak();         // disables line buffering and erase/kill character-processing
  timeout(400);     // wait 500ms for key press
  keypad(stdscr, TRUE);

  //init
  pushFirst(5,5);
  dy=4;
  dx=4;
  mov = 'd';
  len = 1;
  quit = false;
  mvaddstr(22, 0, "wynik");
  createFood();
  frame();

  do {

    wayMove();
    changePos();
    printSnake();
    eatFood();
    viewScore();
    refresh();

  } while( ! quit );


  // clean
  nocbreak();
  echo();
  mvaddstr(10,10,"GAME OVER");
  mvaddstr(11,10,"your score ->");
  char str[12];
  sprintf(str, "%d", len);
  mvaddstr(11,16,str);
  getchar();
  delwin(mainwin);
  endwin();
  return EXIT_SUCCESS;
}



void frame()
{

int columns=20;
int rows=40;
int i = 0;


    for(int j = i;j<rows+1;j++ )
    {
        mvaddstr(i, j, "=");
    }


    for(int j = i+1;j<columns-i-1;j++ )
    {
        mvaddstr(j, rows-1-i, "||");
    }


   for(int j = i;j<rows+1;j++ )
    {
        mvaddstr(columns-1, j, "=");
    }




    for(int j = columns-2-i;j>i;j-- )
    {
        mvaddstr(j,i,"||");
    }

}

int checkConcactFood(int x, int y) {
  Node *curr = head;


  if(curr == NULL){
    return;
  }

  while (curr) {
    if(curr->x==x && curr->y==y) return 1;
    curr = curr->next;
    if(curr == head)
    {
        return 0;
    }
  }

  return 0;
}

void createFood()
{
int x;
int y;

while(true)
{
 foodX = rand()%36+2;
 foodY = rand()%16+2;

    if(!checkConcactFood(x,y))
    {
    mvaddstr(foodY,foodX,"*");
    break;
    }

}

}

void eatFood()
{

if(head->x==foodX && head->y==foodY)
{
createFood();
len+=1;
}
else{
popEnd();
}
mvaddstr(dy, dx, " ");
dx=tail->x;
dy=tail->y;




}

void printSnake()
{
    Node *curr = head;
    mvaddstr(curr->y, curr->x, "0");
    curr=curr->next;
    for(int w = 1; w<len; w++)
    {
        mvaddstr(curr->y, curr->x, "o");
        curr = curr->next;
    }
}




int concatWithBody(int x, int y)
{
    Node *curr = head->next;


    for(int w = 1; w<len; w++)
        {

            if(curr->x==x && curr->y==y) return 1;
            curr = curr->next;

        }

        return 0;


}


void changePos()
{

    pushFirst(head->x,head->y);

    switch(mov)
    {
    case 'w':
        {
            head->y--;
            if(head->y<0 || concatWithBody(head->x,head->y)) quit=true;
            break;
        }
    case 'd':
        {
            head->x++;
            if(head->x>=40 || concatWithBody(head->x,head->y)) quit=true;
            break;
        }
    case 's':
        {
            head->y++;
            if(head->y>=20 || concatWithBody(head->x,head->y))  quit=true;
            break;
        }
    case 'a':
        {
            head->x--;
            if(head->x<=0 || concatWithBody(head->x,head->y)) quit=true;
            break;
        }
    default:
        {
            break;
        }

    }

}


void wayMove()
{

    c = getch();
    switch (c)
    {
      case 'q':
        quit = true;
        break;
      case 'd':
        timeout(400);
        if(mov!='a') mov='d';
        break;
      case 's':
        timeout(600);
        if(mov!='w')  mov='s';
        break;
      case 'a':
       timeout(400);
        if(mov!='d') mov='a';
        break;
      case 'w':
       timeout(600);
       if(mov!='s')  mov='w';
        break;
      case KEY_RIGHT:
        timeout(400);
        if(mov!='a') mov='d';
        break;
      case KEY_DOWN:
        timeout(600);
        if(mov!='w')  mov='s';
        break;
      case KEY_LEFT:
       timeout(400);
        if(mov!='d') mov='a';
        break;
      case KEY_UP:
       timeout(600);
       if(mov!='s')  mov='w';
        break;
      default:
        break;
        }
}

void viewScore()
{

    char str[12];
    sprintf(str, "%d", len);
    mvaddstr(22, 6, str);

}






