Funcion getRandomCharacter() : caracter
    Definir min, max, codigo como entero
    min ← CodigoCaracter('A')
    max ← CodigoCaracter('Z')
    codigo ← getRandomNumber(min, max)
    Retornar CaracterDeCodigo(codigo)
FinFuncion
Procedimiento fillWithRandomCharacters(n: entero, m: entero, REF sopa: tSoup)
    Definir i, j como entero
    Definir c como caracter

    Para i ← 1 Hasta n Hacer
        Para j ← 1 Hasta m Hacer
            c ← getRandomCharacter()
            setCharacter(sopa, i, j, c)
        FinPara
    FinPara
FinProcedimiento
Procedimiento writeSoup(n: entero, m: entero, sopa: tSoup)
    Definir i, j como entero

    Para i ← 1 Hasta n Hacer
        Para j ← 1 Hasta m Hacer
            EscribirSinSalto getCharacter(sopa, i, j) & " "
        FinPara
        Escribir ""  // Salto de línea
    FinPara
FinProcedimiento
Procedimiento initSearch(REF search: tSearch)
    search.count ← 0
FinProcedimiento
Procedimiento addWordToSearch(REF search: tSearch, palabra: tWord)
    Si search.count < 15 Entonces
        search.words[search.count] ← palabra
        search.count ← search.count + 1
    FinSi
FinProcedimiento
Procedimiento initSoup(n: entero, m: entero, REF sopa: tSoup)
    sopa.rows ← n
    sopa.columns ← m
    sopa.state ← EMPTY
FinProcedimiento
Procedimiento hideWordIntoSoup(REF palabra: tWord, n: entero, m: entero, REF sopa: tSoup)
    Definir i, j, ori, len, k como entero

    len ← longitud de palabra.letters
    ori ← getRandomNumber(1, 3)  // 1 = VERTICAL, 2 = HORIZONTAL, 3 = DIAGONAL

    Si ori = 1 Entonces  // VERTICAL
        i ← getRandomNumber(1, n - len + 1)
        j ← getRandomNumber(1, m)
        palabra.position.horizontal ← j
        palabra.position.vertical ← i
        palabra.position.orientation ← VERTICAL

        Para k ← 0 Hasta len - 1 Hacer
            setCharacter(sopa, i + k, j, palabra.letters[k])
        FinPara

    Sino Si ori = 2 Entonces  // HORIZONTAL
        i ← getRandomNumber(1, n)
        j ← getRandomNumber(1, m - len + 1)
        palabra.position.horizontal ← j
        palabra.position.vertical ← i
        palabra.position.orientation ← HORIZONTAL

        Para k ← 0 Hasta len - 1 Hacer
            setCharacter(sopa, i, j + k, palabra.letters[k])
        FinPara

    Sino  // DIAGONAL
        i ← getRandomNumber(1, n - len + 1)
        j ← getRandomNumber(1, m - len + 1)
        palabra.position.horizontal ← j
        palabra.position.vertical ← i
        palabra.position.orientation ← DIAGONAL

        Para k ← 0 Hasta len - 1 Hacer
            setCharacter(sopa, i + k, j + k, palabra.letters[k])
        FinPara
    FinSi
FinProcedimiento

