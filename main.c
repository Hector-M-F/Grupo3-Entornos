#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAXROWS 50
#define MAXCOLUMNS 50
#define MAXLENGTH 15
#define MAXWORDS 15
#define POINT '.'

typedef struct {
    char letters[MAXROWS][MAXCOLUMNS];
    int nRows;
    int nColumns;
} tLetterSoup;

typedef struct {
    char letters[MAXLENGTH];
    int length;
} tString;

// Funciones auxiliares
bool isUpperCaseLetter(char c) {
    return c >= 'A' && c <= 'Z';
}

char getRandomUpperCase() {
    return 'A' + rand() % 26;
}

tString readWordFromInput() {
    tString word;
    word.length = 0;
    char temp[MAXLENGTH + 1];
    int i;

    scanf("%s", temp);
    i = 0;
    while (temp[i] != '\0' && i < MAXLENGTH) {
        word.letters[i] = toupper(temp[i]);  // ? aquí convertimos a mayúscula
        i++;
    }
    word.length = i;
    return word;
}

void fillSoupWithRandom(tLetterSoup *soup) {
    int i, j;
    for (i = 0; i < soup->nRows; i++) {
        for (j = 0; j < soup->nColumns; j++) {
            soup->letters[i][j] = getRandomUpperCase();
        }
    }
}

void initOutputSoup(tLetterSoup *soup) {
    int i, j;
    for (i = 0; i < soup->nRows; i++) {
        for (j = 0; j < soup->nColumns; j++) {
            soup->letters[i][j] = POINT;
        }
    }
}

void printSoup(tLetterSoup soup) {
    int i, j;
    for (i = 0; i < soup.nRows; i++) {
        for (j = 0; j < soup.nColumns; j++) {
            printf("%c ", soup.letters[i][j]);
        }
        printf("\n");
    }
}


bool placeWord(tLetterSoup *soup, tString word) {
    int tries = 100;
    while (tries--) {
        int dx = rand() % 3 - 1;
        int dy = rand() % 3 - 1;
        if (dx == 0 && dy == 0) continue;

        int x = rand() % soup->nRows;
        int y = rand() % soup->nColumns;

        int ok = 1;
        int nx = x, ny = y;
        int i;

        for (i = 0; i < word.length; i++) {
            if (nx < 0 || ny < 0 || nx >= soup->nRows || ny >= soup->nColumns) {
                ok = 0;
                break;
            }
            nx += dx;
            ny += dy;
        }

        if (!ok) continue;

        nx = x;
        ny = y;
        for (i = 0; i < word.length; i++) {
            soup->letters[nx][ny] = word.letters[i];
            nx += dx;
            ny += dy;
        }
        return true;
    }
    return false;
}

bool checkDirection(tLetterSoup soup, tString word, int x, int y, int dx, int dy) {
    int i;
    for (i = 0; i < word.length; i++) {
        if (x < 0 || y < 0 || x >= soup.nRows || y >= soup.nColumns) return false;
        if (soup.letters[x][y] != word.letters[i]) return false;
        x += dx;
        y += dy;
    }
    return true;
}

bool findWord(tLetterSoup soup, tString word, int *fx, int *fy, int *dx, int *dy) {
    int i, j, ddx, ddy;
    for (i = 0; i < soup.nRows; i++) {
        for (j = 0; j < soup.nColumns; j++) {
            for (ddx = -1; ddx <= 1; ddx++) {
                for (ddy = -1; ddy <= 1; ddy++) {
                    if (ddx == 0 && ddy == 0) continue;
                    if (checkDirection(soup, word, i, j, ddx, ddy)) {
                        *fx = i;
                        *fy = j;
                        *dx = ddx;
                        *dy = ddy;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void putWord(tLetterSoup *soup, tString word, int x, int y, int dx, int dy) {
    int i;
    for (i = 0; i < word.length; i++) {
        soup->letters[x][y] = word.letters[i];
        x += dx;
        y += dy;
    }
}

int main() {
    srand(time(NULL));

    tLetterSoup inputSoup, outputSoup;
    tString words[MAXWORDS];
    int numWords;
    int i;

    printf("Introduce el número de filas y columnas (ej: 10 10): ");
    scanf("%d %d", &inputSoup.nRows, &inputSoup.nColumns);

    printf("¿Cuántas palabras quieres añadir? (max %d): ", MAXWORDS);
    scanf("%d", &numWords);

    for (i = 0; i < numWords; i++) {
        printf("Palabra #%d: ", i + 1);
        words[i] = readWordFromInput();
    }

    fillSoupWithRandom(&inputSoup);

    for (i = 0; i < numWords; i++) {
        if (!placeWord(&inputSoup, words[i])) {
            printf("¡No se pudo colocar la palabra %s!\n", words[i].letters);
        }
    }

    printf("\nSopa de letras:\n");
    printSoup(inputSoup);

    // Inicializamos la sopa vacía con puntos
    outputSoup.nRows = inputSoup.nRows;
    outputSoup.nColumns = inputSoup.nColumns;
    initOutputSoup(&outputSoup);

    for (i = 0; i < numWords; i++) {
        tString guess;
        int x, y, dx, dy;
        bool found;

        printf("\nAdivina la palabra #%d: ", i + 1);
        guess = readWordFromInput();

        found = findWord(inputSoup, guess, &x, &y, &dx, &dy);
        if (found) {
            printf("¡Correcto! Palabra encontrada.\n");
            putWord(&outputSoup, guess, x, y, dx, dy);
        } else {
            printf("Palabra no encontrada.\n");
        }
    }

    printf("\nResultado final:\n");
    printSoup(outputSoup);  
    return 0;
}


