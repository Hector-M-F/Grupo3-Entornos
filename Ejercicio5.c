#include <stdio.h>
#include <stdbool.h>

#define MAXROWS 50
#define MAXCOLUMNS 50
#define MAXLENGTH 15
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

void readInputSoup(tLetterSoup *soup);
void initOutputSoup(tLetterSoup *soup);
bool isUpperCaseLetter(char c);
tString readString();
void lookForWord(tLetterSoup inputSoup, tString word, int *x, int *y, int *dirX, int *dirY, bool *found);
void checkWord(tLetterSoup soup, tString currentWord, int x, int y, int dirX, int dirY, bool *found);
void putWord(tLetterSoup *soup, tString currentWord, int x, int y, int dirX, int dirY);
void writeSoup(tLetterSoup soup);

int main() {
    int i, n, m, w, x, y, dirX, dirY;
    tLetterSoup inputSoup;
    tLetterSoup outputSoup;
    tString currentWord;
    bool found;
    
    // Leer dimensiones
    scanf("%d %d", &inputSoup.nRows, &inputSoup.nColumns);
    
    // Leer sopa de entrada
    readInputSoup(&inputSoup);
    
    // Inicializar sopa
    outputSoup.nRows = inputSoup.nRows;
    outputSoup.nColumns = inputSoup.nColumns;
    initOutputSoup(&outputSoup);
    
    // Leer el numero de palabras
    scanf("%d", &w);
    
    // Encontrar cada palabra
    for (i = 1; i <= w; i++) {
        currentWord = readString();
        found = false;
        x = 1;
        
        while (x <= inputSoup.nRows && !found) {
            y = 1;
            while (y <= inputSoup.nColumns && !found) {
                lookForWord(inputSoup, currentWord, &x, &y, &dirX, &dirY, &found);
                y++;
            }
            x++;
        }
        
        if (found) {
            putWord(&outputSoup, currentWord, x-1, y-1, dirX, dirY);
        }
    }
    
    // Escribe la sopa
    writeSoup(outputSoup);
    
    return 0;
}
