#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL
} tOrientation;

typedef struct {
    int horizontal;
    int vertical;
    tOrientation orientation;
} tPosition;

typedef struct {
    char letters[16]; // Max 15 letras + '\0'
    int found;
    tPosition position;
} tWord;

typedef enum {
    EMPTY,
    RANDOM_FILLED,
    READY_TO_PLAY
} tSoupState;

typedef struct {
    char grid[50][50];
    int rows;
    int columns;
    tSoupState state;
} tSoup;

typedef struct {
    tWord words[15];
    int count;
} tSearch;

typedef struct {
    tSoup soup;
    tSearch search;
} tGame;

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

char getRandomCharacter() {
    int min = 'A';
    int max = 'Z';
    int code = getRandomNumber(min, max);
    return (char)code;
}

char getCharacter(tSoup soup, int row, int col) {
    return soup.grid[row - 1][col - 1];
}

void setCharacter(tSoup *soup, int row, int col, char c) {
    soup->grid[row - 1][col - 1] = c;
}

int getWordLength(tWord word) {
    return strlen(word.letters);
}

void reverseWord(tWord *word) {
    int i;
    int len = getWordLength(*word);
    char temp;

    for (i = 0; i < len / 2; i++) {
        temp = word->letters[i];
        word->letters[i] = word->letters[len - i - 1];
        word->letters[len - i - 1] = temp;
    }
}

void initSoup(tSoup *soup, int rows, int cols) {
    soup->rows = rows;
    soup->columns = cols;
    soup->state = EMPTY;
}

void initSearch(tSearch *search) {
    search->count = 0;
}

void addWordToSearch(tSearch *search, tWord word) {
    if (search->count < 15) {
        search->words[search->count] = word;
        search->count++;
    }
}

void fillWithRandomCharacters(int n, int m, tSoup *soup) {
    int i, j;
    char c;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            c = getRandomCharacter();
            setCharacter(soup, i, j, c);
        }
    }
}

void writeSoup(int n, int m, tSoup soup) {
    int i, j;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            printf("%c ", getCharacter(soup, i, j));
        }
        printf("\n");
    }
}

void setWord(tSoup *soup, tWord *word, tPosition position) {
    int k;
    int len = getWordLength(*word);

    for (k = 0; k < len; k++) {
        int row = position.vertical;
        int col = position.horizontal;

        if (position.orientation == HORIZONTAL) {
            setCharacter(soup, row, col + k, word->letters[k]);
        } else if (position.orientation == VERTICAL) {
            setCharacter(soup, row + k, col, word->letters[k]);
        } else if (position.orientation == DIAGONAL) {
            setCharacter(soup, row + k, col + k, word->letters[k]);
        }
    }

    word->position = position;
}

void hideWordIntoSoup(tWord *word, int n, int m, tSoup *soup) {
    int i, j, ori, len, reverse;
    tWord tempWord;
    int k;

    len = getWordLength(*word);
    ori = getRandomNumber(0, 2); // 0 = H, 1 = V, 2 = D
    reverse = getRandomNumber(0, 1); // 0 = normal, 1 = invertida
    tempWord = *word;

    if (reverse == 1) {
        reverseWord(&tempWord);
    }

    if (ori == VERTICAL) {
        i = getRandomNumber(1, n - len + 1);
        j = getRandomNumber(1, m);
        tempWord.position.orientation = VERTICAL;
    } else if (ori == HORIZONTAL) {
        i = getRandomNumber(1, n);
        j = getRandomNumber(1, m - len + 1);
        tempWord.position.orientation = HORIZONTAL;
    } else {
        i = getRandomNumber(1, n - len + 1);
        j = getRandomNumber(1, m - len + 1);
        tempWord.position.orientation = DIAGONAL;
    }

    tempWord.position.vertical = i;
    tempWord.position.horizontal = j;

    setWord(soup, &tempWord, tempWord.position);

    *word = tempWord; // Guardamos la posición y orientación
}

tWord readWord() {
    tWord word;
    printf("Introduce una palabra (max 15 letras): ");
    scanf("%15s", word.letters);
    word.found = 0;
    return word;
}

int main() {
    tGame game;
    int numWords;
    int i;
    int rows, cols;

    srand(time(NULL));

    printf("Introduce el numero de filas de la sopa: ");
    scanf("%d", &rows);
    printf("Introduce el numero de columnas de la sopa: ");
    scanf("%d", &cols);

    initSoup(&game.soup, rows, cols);
    initSearch(&game.search);

    printf("Cuantas palabras quieres introducir (max 15): ");
    scanf("%d", &numWords);

    for (i = 0; i < numWords && i < 15; i++) {
        tWord w = readWord();
        addWordToSearch(&game.search, w);
    }

    fillWithRandomCharacters(rows, cols, &game.soup);

    for (i = 0; i < game.search.count; i++) {
        hideWordIntoSoup(&game.search.words[i], rows, cols, &game.soup);
    }

    printf("\n--- Sopa de letras generada ---\n");
    writeSoup(rows, cols, game.soup);

    return 0;
}
