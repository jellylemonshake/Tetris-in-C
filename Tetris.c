#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 10
#define HEIGHT 20

// Shapes for Tetrimino (simplified for example)
int shapes[7][4][4] = {
    {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // I
    {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // O
    {{1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // T
    {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // S
    {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // Z
    {{1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // L
    {{1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}  // J
};

typedef struct {
    int x, y;
} Point;

typedef struct {
    int grid[HEIGHT][WIDTH];
    int currentShape[4][4];
    Point position;
    int currentShapeIndex;
} Tetris;

void copyShape(int dest[4][4], int src[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

void copyShapeFromArray(int dest[4][4], int shapeIndex) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            dest[i][j] = shapes[shapeIndex][i][j];
        }
    }
}

void spawnNewPiece(Tetris *game) {
    game->currentShapeIndex = rand() % 7;
    game->position.x = WIDTH / 2 - 2;
    game->position.y = 0;
    copyShapeFromArray(game->currentShape, game->currentShapeIndex);
}

int isColliding(Tetris *game) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (game->currentShape[i][j] == 1) {
                int x = game->position.x + j;
                int y = game->position.y + i;
                if (x < 0 || x >= WIDTH || y >= HEIGHT || game->grid[y][x] == 1) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void rotatePiece(Tetris *game) {
    int rotatedShape[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            rotatedShape[j][3 - i] = game->currentShape[i][j];
        }
    }

    int previousShape[4][4];
    copyShape(previousShape, game->currentShape);

    copyShape(game->currentShape, rotatedShape);
    if (isColliding(game)) {
        copyShape(game->currentShape, previousShape); // Revert if the rotation collides
    }
}

void moveLeft(Tetris *game) {
    game->position.x--;
    if (isColliding(game)) game->position.x++; // Revert if collision
}

void moveRight(Tetris *game) {
    game->position.x++;
    if (isColliding(game)) game->position.x--; // Revert if collision
}

void moveDown(Tetris *game) {
    game->position.y++;
    if (isColliding(game)) {
        game->position.y--;
        // Place the piece in the grid
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (game->currentShape[i][j] == 1) {
                    game->grid[game->position.y + i][game->position.x + j] = 1;
                }
            }
        }
        spawnNewPiece(game); // Spawn new piece after placing the current one
    }
}

void clearLine(Tetris *game, int line) {
    for (int i = line; i > 0; i--) {
        for (int j = 0; j < WIDTH; j++) {
            game->grid[i][j] = game->grid[i - 1][j];
        }
    }
    for (int j = 0; j < WIDTH; j++) {
        game->grid[0][j] = 0;
    }
}

void checkLines(Tetris *game) {
    for (int i = 0; i < HEIGHT; i++) {
        int isFull = 1;
        for (int j = 0; j < WIDTH; j++) {
            if (game->grid[i][j] == 0) {
                isFull = 0;
                break;
            }
        }
        if (isFull) {
            clearLine(game, i);
        }
    }
}

void draw(Tetris *game) {
    system("CLS");

    // Top border
    printf("+");
    for (int i = 0; i < WIDTH; i++) {
        printf("--");
    }
    printf("+\n");

    // Draw grid and falling piece
    for (int i = 0; i < HEIGHT; i++) {
        printf("|"); // Left border
        for (int j = 0; j < WIDTH; j++) {
            int isPartOfPiece = 0;
            // Check if the current position is part of the falling piece
            for (int pI = 0; pI < 4; pI++) {
                for (int pJ = 0; pJ < 4; pJ++) {
                    int x = game->position.x + pJ;
                    int y = game->position.y + pI;
                    if (y == i && x == j && game->currentShape[pI][pJ] == 1) {
                        isPartOfPiece = 1;
                        break;
                    }
                }
            }
            if (isPartOfPiece || game->grid[i][j] == 1) {
                printf("[]"); // Filled cell
            } else {
                printf("  "); // Empty cell
            }
        }
        printf("|\n"); // Right border
    }

    // Bottom border
    printf("+");
    for (int i = 0; i < WIDTH; i++) {
        printf("--");
    }
    printf("+\n");

    printf("\033[%d;%dH", HEIGHT + 2, 0); // Move cursor below game
}


void handleInput(Tetris *game) {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'a') moveLeft(game);
        if (key == 'd') moveRight(game);
        if (key == 's') moveDown(game);
        if (key == 'w') rotatePiece(game);
    }
}

int main() {
    srand(time(0));
    Tetris game = {0};

    spawnNewPiece(&game);

    while (1) {
        handleInput(&game);
        moveDown(&game);
        checkLines(&game);
        draw(&game);
        Sleep(500); // Control game speed
    }

    return 0;
}

//To run enter in terminal: 
// gcc ./Tetris.c -o ./a.exe
// ./a.exe
