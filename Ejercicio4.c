Procedimiento reverseWord(REF palabra: tWord)
    Definir i, len como entero
    Definir temp como caracter

    len ← longitud de palabra.letters

    Para i ← 0 Hasta (len / 2) - 1 Hacer
        temp ← palabra.letters[i]
        palabra.letters[i] ← palabra.letters[len - i - 1]
        palabra.letters[len - i - 1] ← temp
    FinPara
FinProcedimiento
Procedimiento hideWordIntoSoup(REF palabra: tWord, n: entero, m: entero, REF sopa: tSoup)
    Definir i, j, ori, len, reverse, k como entero
    Definir palabraTemp como tWord

    palabraTemp ← palabra
    len ← longitud de palabraTemp.letters
    ori ← getRandomNumber(1, 3)      // 1 = VERTICAL, 2 = HORIZONTAL, 3 = DIAGONAL
    reverse ← getRandomNumber(0, 1)  // 0 = normal, 1 = invertida

    Si reverse = 1 Entonces
        reverseWord(palabraTemp)
    FinSi

    Si ori = 1 Entonces  // VERTICAL
        i ← getRandomNumber(1, n - len + 1)
        j ← getRandomNumber(1, m)
        palabra.position.horizontal ← j
        palabra.position.vertical ← i
        palabra.position.orientation ← VERTICAL

        Para k ← 0 Hasta len - 1 Hacer
            setCharacter(sopa, i + k, j, palabraTemp.letters[k])
        FinPara

    Sino Si ori = 2 Entonces  // HORIZONTAL
        i ← getRandomNumber(1, n)
        j ← getRandomNumber(1, m - len + 1)
        palabra.position.horizontal ← j
        palabra.position.vertical ← i
        palabra.position.orientation ← HORIZONTAL

        Para k ← 0 Hasta len - 1 Hacer
            setCharacter(sopa, i, j + k, palabraTemp.letters[k])
        FinPara

    Sino  // DIAGONAL
        i ← getRandomNumber(1, n - len + 1)
        j ← getRandomNumber(1, m - len + 1)
        palabra.position.horizontal ← j
        palabra.position.vertical ← i
        palabra.position.orientation ← DIAGONAL

        Para k ← 0 Hasta len - 1 Hacer
            setCharacter(sopa, i + k, j + k, palabraTemp.letters[k])
        FinPara
    FinSi
FinProcedimiento

