#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAXROWS 50
#define MAXCOLUMNS 50
#define MAXLENGTH 15
#define MAXWORDS 15
#define POINT '.'  // Carácter para rellenar la sopa de salida

// Estructura para representar la sopa de letras
typedef struct {
    char letters[MAXROWS][MAXCOLUMNS];
    int nRows;
    int nColumns;
} tLetterSoup;

// Estructura para representar una palabra
typedef struct {
    char letters[MAXLENGTH];
    int length;
} tString;

// Comprueba si un carácter es una letra mayúscula
bool isUpperCaseLetter(char c) {
    return c >= 'A' && c <= 'Z';
}

// Devuelve una letra mayúscula aleatoria
char getRandomUpperCase() {
    return 'A' + rand() % 26;
}

// Lee una palabra desde la entrada, la convierte a mayúsculas y la guarda
tString readWordFromInput() {
    tString word;
    word.length = 0;
    char temp[MAXLENGTH + 1];
    int i;

    scanf("%s", temp);
    i = 0;
    while (temp[i] != '\0' && i < MAXLENGTH) {
        word.letters[i] = toupper(temp[i]);  
        i++;
    }
    word.length = i;
    return word;
}

// Rellena la sopa con letras aleatorias
void fillSoupWithRandom(tLetterSoup *soup) {
    int i, j;
    for (i = 0; i < soup->nRows; i++) {
        for (j = 0; j < soup->nColumns; j++) {
            soup->letters[i][j] = getRandomUpperCase();
        }
    }
}

// Inicializa la sopa de salida con puntos
void initOutputSoup(tLetterSoup *soup) {
    int i, j;
    for (i = 0; i < soup->nRows; i++) {
        for (j = 0; j < soup->nColumns; j++) {
            soup->letters[i][j] = POINT;
        }
    }
}

// Imprime la sopa por pantalla
void printSoup(tLetterSoup soup) {
    int i, j;
    for (i = 0; i < soup.nRows; i++) {
        for (j = 0; j < soup.nColumns; j++) {
            printf("%c ", soup.letters[i][j]);
        }
        printf("\n");
    }
}

// Intenta colocar una palabra en una dirección aleatoria
bool placeWord(tLetterSoup *soup, tString word) {
    int tries = 100;
    while (tries--) {
        int dx = rand() % 3 - 1;  // Dirección X (-1, 0, 1)
        int dy = rand() % 3 - 1;  // Dirección Y (-1, 0, 1)
        if (dx == 0 && dy == 0) continue;  // Evita dirección (0,0)

        int x = rand() % soup->nRows;
        int y = rand() % soup->nColumns;

        int ok = 1;
        int nx = x, ny = y;
        int i;

        // Comprueba si cabe la palabra en esa dirección
        for (i = 0; i < word.length; i++) {
            if (nx < 0 || ny < 0 || nx >= soup->nRows || ny >= soup->nColumns) {
                ok = 0;
                break;
            }
            nx += dx;
            ny += dy;
        }

        if (!ok) continue;

        // Coloca la palabra en la sopa
        nx = x;
        ny = y;
        for (i = 0; i < word.length; i++) {
            soup->letters[nx][ny] = word.letters[i];
            nx += dx;
            ny += dy;
        }
        return true;
    }
    return false;  // No se pudo colocar la palabra
}

// Comprueba si la palabra existe desde una posición y en una dirección
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

// Busca una palabra en la sopa en todas las direcciones posibles
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
    return false;  // No se encontró la palabra
}

// Copia la palabra encontrada en la sopa de salida
void putWord(tLetterSoup *soup, tString word, int x, int y, int dx, int dy) {
    int i;
    for (i = 0; i < word.length; i++) {
        soup->letters[x][y] = word.letters[i];
        x += dx;
        y += dy;
    }
}

// Función principal
int main() {
    srand(time(NULL));  // Inicializa semilla aleatoria

    tLetterSoup inputSoup, outputSoup;
    tString words[MAXWORDS];
    int numWords;
    int i;

    // Pide el tamaño de la sopa al usuario
    printf("Introduce el numero de filas y columnas (ej: 10 10): ");
    scanf("%d %d", &inputSoup.nRows, &inputSoup.nColumns);

    // Pide cuántas palabras se quieren añadir
    printf("Cuantas palabras quieres añadir? (max %d): ", MAXWORDS);
    scanf("%d", &numWords);

    // Lee todas las palabras del usuario
    for (i = 0; i < numWords; i++) {
        printf("Palabra #%d: ", i + 1);
        words[i] = readWordFromInput();
    }

    // Rellena la sopa con letras aleatorias
    fillSoupWithRandom(&inputSoup);

    // Intenta colocar cada palabra en la sopa
    for (i = 0; i < numWords; i++) {
        if (!placeWord(&inputSoup, words[i])) {
            printf("¡No se pudo colocar la palabra %s!\n", words[i].letters);
        }
    }

    // Muestra la sopa con las palabras escondidas
    printf("\nSopa de letras:\n");
    printSoup(inputSoup);

    // Prepara la sopa vacía donde se marcarán las palabras encontradas
    outputSoup.nRows = inputSoup.nRows;
    outputSoup.nColumns = inputSoup.nColumns;
    initOutputSoup(&outputSoup);

    // El usuario trata de adivinar las palabras
    for (i = 0; i < numWords; i++) {
        tString guess;
        int x, y, dx, dy;
        bool found;

        printf("\nAdivina la palabra #%d: ", i + 1);
        guess = readWordFromInput();

        found = findWord(inputSoup, guess, &x, &y, &dx, &dy);
        if (found) {
            printf("Correcto! Palabra encontrada.\n");
            putWord(&outputSoup, guess, x, y, dx, dy);
        } else {
            printf("Palabra no encontrada.\n");
        }
    }

    // Muestra la sopa final con las palabras que el usuario encontró
    printf("\nResultado final:\n");
    printSoup(outputSoup);  

    return 0;
}
