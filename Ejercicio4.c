//Dissenyeu una acció reverseWord que inverteixi l’ordre dels caràcters d’una paraula donada.

accio reverseWord(entsor word: tWord)
var
    i, j: enter;
    tmp: caracter;
fvar
    i := 1;
    j := getWordLength(word);
    mentre i < j fer
        tmp := getCharacterAt(word, i);
        setCharacterAt(word, i, getCharacterAt(word, j));
        setCharacterAt(word, j, tmp);
        i := i + 1;
        j := j - 1;
    fmentre
faccio


//Modifiqueu l’algorisme de l’exercici 3 per aconseguir l’efecte descrit, utilitzant l’acció reverseWord.

per i:= 1 fins w fer
    word := readWord();

    si getRandomNumber(0,1) = 1 llavors
        reverseWord(word); 
    fsi

    addWordToSearch(search, word);
    hideWordIntoSoup(word, n, m, soup);
fper
