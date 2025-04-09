// Inverte una palabra
void reverseWord(tWord *word) {
    int i, len;
    char temp;
    
    len = getWordLength(*word);
    
    for (i = 0; i < len / 2; i++) {
        temp = word->letters[i];
        word->letters[i] = word->letters[len - i - 1];
        word->letters[len - i - 1] = temp;
    }
}

// Modificacion de hideWordIntoSoup para usar palabras invertidas
void hideWordIntoSoup(tWord *word, int n, int m, tSoup *soup) {
    int i, j, ori, len, reverse;
    int k;
    tWord tempWord = *word;
    
    len = getWordLength(tempWord);
    ori = getRandomNumber(1, 3);
    reverse = getRandomNumber(0, 1); // 0 = normal, 1 = invertida
    
    if (reverse == 1) {
        reverseWord(&tempWord);
    }

}
