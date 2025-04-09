// Obtiene un caracter de la posicion (fila, columna) de la sopa
char getCharacter(tSoup soup, int row, int col);

// Establece un caracter en la posicion (fila, columna) de la sopa
void setCharacter(tSoup *soup, int row, int col, char c);

// Coloca una palabra en la sopa en una posicion y orientacion dada
void setWord(tSoup *soup, tWord *word, tPosition position);

// Inicializa la sopa con dimensiones dadas
void initSoup(tSoup *soup, int rows, int cols);

// Lee una palabra de la entrada
tWord readWord();
