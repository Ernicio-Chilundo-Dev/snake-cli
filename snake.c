#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 20
#define HEIGHT 20

int x, y, foodX, foodY, score;
int tailX[100], tailY[100];
int nTail;
int gameOver;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum Direction dir;

void Setup() {
    initscr();          // Inicializa ncurses
    clear();
    noecho();           // Não mostrar teclas pressionadas
    cbreak();           // Linha por linha sem buffer
    curs_set(FALSE);    // Esconde o cursor
    keypad(stdscr, TRUE); // Captura teclas especiais (setas)
    nodelay(stdscr, TRUE); // getch não bloqueia

    gameOver = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    srand(time(NULL));
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
    score = 0;
}

void Draw() {
    clear();
    // Desenha borda superior
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

void Input() {
    int ch = getch();
    switch (ch) {
        case KEY_LEFT:
            if (dir != RIGHT) dir = LEFT;
            break;
        case KEY_RIGHT:
            if (dir != LEFT) dir = RIGHT;
            break;
        case KEY_UP:
            if (dir != DOWN) dir = UP;
            break;
        case KEY_DOWN:
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
        case 'X':
            gameOver = 1;
            break;
        default:
            break;
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    // Verifica colisão com paredes
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameOver = 1;

    // Verifica colisão com cauda
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }

    // Come a comida
    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
        nTail++;
    }
}

void End() {
    nodelay(stdscr, FALSE);
    mvprintw(HEIGHT / 2, (WIDTH / 2) - 5, "GAME OVER");
    mvprintw(HEIGHT / 2 + 1, (WIDTH / 2) - 9, "Score final: %d", score);
    mvprintw(HEIGHT / 2 + 3, (WIDTH / 2) - 12, "Pressione qualquer tecla para sair...");
    refresh();
    getch();
    endwin();
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        usleep(100000); // 100ms
    }
    End();
    return 0;
}
