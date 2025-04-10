Tipo tOrientation = (HORIZONTAL, VERTICAL, DIAGONAL)

Tipo tSoupState = (EMPTY, RANDOM_FILLED, READY_TO_PLAY)
Registro tPosition
    entero horizontal
    entero vertical
    tOrientation orientation
FinRegistro
Registro tWord
    cadena letters[16]     // Cadena de máximo 15 caracteres + '\0'
    entero found           // 0 = no encontrada, 1 = encontrada
    tPosition position     // Posición donde se encuentra la palabra
FinRegistro
Registro tSoup
    caracter grid[50][50]  // Matriz de caracteres de 50x50
    entero rows            // Número de filas
    entero columns         // Número de columnas
    tSoupState state       // Estado de la sopa
FinRegistro
Registro tSearch
    tWord words[15]        // Lista de hasta 15 palabras
    entero count           // Número de palabras añadidas
FinRegistro
Registro tGame
    tSoup soup             // La sopa de letras completa
    tSearch search         // Palabras que hay que buscar
FinRegistro
