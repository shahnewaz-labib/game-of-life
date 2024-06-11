#include <stdio.h>
#include <unistd.h>

#define ROWS 8
#define COLS 16

int grid[ROWS][COLS] = {0};

void display() {
    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLS; ++x) {
            if (grid[y][x]) {
                printf("#");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

int mod(int a, int b) { return (a % b + b) % b; }

int count_nbors(int cx, int cy) {
    int nbors = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (!(dx == 0 && dy == 0)) {
                int x = mod(cx + dx, COLS);
                int y = mod(cy + dy, ROWS);
                if (grid[y][x] & 1) {
                    nbors += 1;
                }
            }
        }
    }
    return nbors;
}

void next(void) {
    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLS; ++x) {
            int nbors = count_nbors(x, y);

            if (grid[y][x]) {
                if (nbors < 2 || nbors > 3) {
                    grid[y][x] = 1;
                } else {
                    grid[y][x] = 3;
                }
            } else {
                if (nbors == 3) {
                    grid[y][x] = 2;
                }
            }
        }
    }
    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLS; ++x) {
            grid[y][x] >>= 1;
        }
    }
}

void init() {
    grid[0][1] = 1;
    grid[1][2] = 1;
    grid[2][0] = 1;
    grid[2][1] = 1;
    grid[2][2] = 1;
}

int main() {
    init();
    for (;;) {
        display();
        next();
        printf("\033[%dA\033[%dD", ROWS, COLS);
        usleep(100 * 1000);
    }
    return 0;
}
