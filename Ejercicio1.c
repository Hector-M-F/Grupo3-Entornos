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
    char letters[16]; // M�ximo 15 caracteres
    int found; // 0 = no encontrada 1 = encontrada
    tPosition position;
} tWord;

// Estado de la sopa de letras
typedef enum {
    EMPTY,           // Vac�a
    RANDOM_FILLED,   // Rellena con caracteres aleatorios
    READY_TO_PLAY    // Lista para jugar
} tSoupState;

// Tipo para la sopa de letras
typedef struct {
    char grid[50][50]; // Tama�o m�ximo
    int rows;
    int columns;
    tSoupState state;
} tSoup;

// Tipo para las palabras a buscar
typedef struct {
    tWord words[15]; // M�ximo 15 palabras
    int count;
} tSearch;

// Tipo para el juego completo
typedef struct {
    tSoup soup;
    tSearch search;
} tGame;
