// Obtiene un caracter aleatorio en mayusculas
char getRandomCharacter() {
    int min = 'A';
    int max = 'Z';
    int code = getRandomNumber(min, max);
    return (char)code;
}

// Llenaa la sopa con caracteres aleatorios
void fillWithRandomCharacters(int n, int m, tSoup *soup) {
    char c;
    int i, j;
    
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            c = getRandomCharacter();
            setCharacter(soup, i, j, c);
        }
    }
}

// Escribie la sopa 
void writeSoup(int n, int m, tSoup soup) {
    int i, j;
    
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            writeChar(getCharacter(soup, i, j));
        }
    }
}

// Inicializa la estructura de busqueda
void initSearch(tSearch *search) {
    search->count = 0;
}

// Añade una palabra a la estructura de busqueda
void addWordToSearch(tSearch *search, tWord word) {
    if (search->count < 15) {
        search->words[search->count] = word;
        search->count++;
    }
}

// Inicializaa una sopa con dimensiones dadas
void initSoup(int n, int m, tSoup *soup) {
    soup->rows = n;
    soup->columns = m;
    soup->state = EMPTY;
}

// Coloca una palabra en la sopa en una posicion aleatoria
void hideWordIntoSoup(tWord *word, int n, int m, tSoup *soup) {
    int i, j, ori, len;
    int k;
    
    len = getWordLength(*word);
    ori = getRandomNumber(1, 3);
    
    if (ori == 1) { // Vertical
        i = getRandomNumber(1, n - len + 1);
        j = getRandomNumber(1, m);
        word->position.horizontal = j;
        word->position.vertical = i;
        word->position.orientation = VERTICAL;
        
        for (k = 0; k < len; k++) {
            setCharacter(soup, i + k, j, word->letters[k]);
        }
    } else if (ori == 2) { // Horizontal
        i = getRandomNumber(1, n);
        j = getRandomNumber(1, m - len + 1);
        word->position.horizontal = j;
        word->position.vertical = i;
        word->position.orientation = HORIZONTAL;
        
        for (k = 0; k < len; k++) {
            setCharacter(soup, i, j + k, word->letters[k]);
        }
    } else { // Diagonal
        i = getRandomNumber(1, n - len + 1);
        j = getRandomNumber(1, m - len + 1);
        word->position.horizontal = j;
        word->position.vertical = i;
        word->position.orientation = DIAGONAL;
        
        for (k = 0; k < len; k++) {
            setCharacter(soup, i + k, j + k, word->letters[k]);
        }
    }
}
