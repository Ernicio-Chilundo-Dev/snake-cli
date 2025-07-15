#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define HEIGHT 20
#define WIDTH 20

int x, y,foodx, foody, score;
int tailX[100], tailY[100];
int nTail;
int gamaOver;

enum Direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
enum Direction dir;

void Setup(){
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(false);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    gamaOver = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    srand(time(0));
    foodx = rand() % WIDTH;
    foodx = rand() % HEIGHT;
    score = 0;

}

// void Draw(){
    
// }