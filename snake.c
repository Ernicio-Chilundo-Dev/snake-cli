#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define HEIGHT 20
#define WIDTH 20

int x, y,foodX, foodY, score;
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
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
    score = 0;

}

void Draw()
{
    for (int i = 0; i < WIDTH + 2; i++)
        mvprintw(0, i, "#");

    // Desenha área do jogo
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                mvprintw(i + 1, j, "#");

            if (i == y && j == x)
                mvprintw(i + 1, j + 1, "*"); // Cabeça da cobra
            else if (i == foodY && j == foodX)
                mvprintw(i + 1, j + 1, "@"); // Comida
            else {
                int printTail = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        mvprintw(i + 1, j + 1, "*");
                        printTail = 1;
                    }
                }
                if (!printTail)
                    mvprintw(i + 1, j + 1, " ");
            }

            if (j == WIDTH - 1)
                mvprintw(i + 1, j + 2, "#");
        }
    }

    // Desenha borda inferior
    for (int i = 0; i < WIDTH + 2; i++)
        mvprintw(HEIGHT + 1, i, "#");

    mvprintw(HEIGHT + 3, 0, "Score: %d", score);
    refresh();
}