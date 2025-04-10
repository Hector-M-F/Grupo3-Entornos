Funcion getCharacter(sopa: tSoup, fila: entero, columna: entero) : caracter
    Retornar sopa.grid[fila][columna]
FinFuncion
Procedimiento setCharacter(REF sopa: tSoup, fila: entero, columna: entero, c: caracter)
    sopa.grid[fila][columna] ← c
FinProcedimiento
Procedimiento setWord(REF sopa: tSoup, REF palabra: tWord, posicion: tPosition)
    Definir i, longitud como entero
    longitud ← longitud de palabra.letters

    palabra.position ← posicion

    Si posicion.orientation = HORIZONTAL Entonces
        Para i ← 0 Hasta longitud - 1 Hacer
            sopa.grid[posicion.vertical][posicion.horizontal + i] ← palabra.letters[i]
        FinPara

    Sino Si posicion.orientation = VERTICAL Entonces
        Para i ← 0 Hasta longitud - 1 Hacer
            sopa.grid[posicion.vertical + i][posicion.horizontal] ← palabra.letters[i]
        FinPara

    Sino Si posicion.orientation = DIAGONAL Entonces
        Para i ← 0 Hasta longitud - 1 Hacer
            sopa.grid[posicion.vertical + i][posicion.horizontal + i] ← palabra.letters[i]
        FinPara
    FinSi
FinProcedimiento
Procedimiento initSoup(REF sopa: tSoup, filas: entero, columnas: entero)
    sopa.rows ← filas
    sopa.columns ← columnas
    sopa.state ← EMPTY
FinProcedimiento
Funcion readWord() : tWord
    Definir w como tWord
    Escribir "Introduce una palabra (max 15 letras):"
    Leer w.letters
    w.found ← 0
    // La posición se inicializará más adelante
    Retornar w
FinFuncion
