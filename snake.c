#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h> //http://www.cs.ukzn.ac.za/~hughm/os/notes/ncurses.html
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
void incrementTime();
void initVariables();
int gameOver();
void restart();

//global variables
int foodY,foodX,dy,dx,len,c,timeHorizontal,timeVertical;
bool quit;
char mov;

//main
int main(void)
{
  WINDOW * mainwin;


  //init variables
  initVariables();

  //init ncurses
  if ( (mainwin = initscr()) == NULL ) {
    fprintf(stderr, "Error initialising ncurses.\n");
    exit(EXIT_FAILURE);
  }
  noecho();
  cbreak();
  timeout(timeHorizontal);
  keypad(stdscr, TRUE);


  //init random
  srand(time(NULL));


  //init basic frame and food
  restr:
  createFood();
  frame();
  mvaddstr(21, 0, "score -> ");
  mvaddstr(21, 15, "q -> exit");
  mvaddstr(21, 25, "p -> pause");





  do {

    wayMove(); // thread, sleep 1 s
    changePos();
    printSnake();
    eatFood();
    viewScore();
    refresh();

  } while( ! quit );

  //restart and score
  if(gameOver())
  {
    restart();
    goto restr;
  }

  //clean
  nocbreak();
  echo();
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
incrementTime();
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
      case 'p':
        while(getch()!='p'){}
        break;
      case 'd':
        timeout(timeVertical);
        if(mov!='a') mov='d';
        break;
      case 's':
        timeout(timeHorizontal);
        if(mov!='w')  mov='s';
        break;
      case 'a':
       timeout(timeVertical);
        if(mov!='d') mov='a';
        break;
      case 'w':
       timeout(timeHorizontal);
       if(mov!='s')  mov='w';
        break;
      case KEY_RIGHT:
        timeout(timeVertical);
        if(mov!='a') mov='d';
        break;
      case KEY_DOWN:
        timeout(timeHorizontal);
        if(mov!='w')  mov='s';
        break;
      case KEY_LEFT:
       timeout(timeVertical);
        if(mov!='d') mov='a';
        break;
      case KEY_UP:
       timeout(timeHorizontal);
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
    mvaddstr(21, 9, str);


}

void incrementTime()
{
    timeHorizontal-=10;
    timeVertical-=10;
}

void initVariables()
{

  pushFirst(5,5);
  dy=4;
  dx=4;
  mov = 'd';
  len = 1;
  timeHorizontal = 600;
  timeVertical = 400;
  quit = false;



}

int gameOver()
{
  clear();
  mvaddstr(10,10,"GAME OVER");
  mvaddstr(11,10,"your score ->");
  char str[12];
  sprintf(str, "%d", len);
  mvaddstr(11,25,str);
  mvaddstr(12,10,"press r to restart or anything to exit");
  refresh();

  int chr = getchar();
  if(chr=='r') return 1;
  return 0;
}

void restart()
{

    while(tail!=NULL)
    {
        popEnd();
    }
    initVariables();
    timeout(timeHorizontal);
    clear();
    refresh();
}






