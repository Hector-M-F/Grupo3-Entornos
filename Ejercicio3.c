//Obtenir lletra aleatoria:

 funcio getRandomCharacter(): caracter
var
  min, max, code: enter;
fvar
  min := 65;       // A
  max := 90;       // Z
  code := getRandomNumber(min, max);
  retorna chr(code);
ffuncio

//Omplir la sopa lletres aleatòries:

accio fillWithRandomCharacters(ent n: enter, ent m: enter, entsor soup: tSoup)
var
  c: caracter;
  i, j: enter;
fvar
  per i := 1 fins n fer
    per j := 1 fins m fer
      c := getRandomCharacter();
      soup[i][j] := c; 
    fper
  fper
faccio

//Escriure la sopa:

accio writeSoup(ent n, m: enter, ent soup: tSoup)
var
  i, j: enter;
fvar
  writeInteger(n);
  writeInteger(m);
  per i := 1 fins n fer
    per j := 1 fins m fer
      writeChar(soup[i][j]);
    fper
  fper
faccio


//Inserir paraula:

accio hideWordIntoSoup(entsor word: tWord, ent n: enter, ent m: enter, entsor soup: tSoup)
var
  i, j, k, ori, len: enter;
fvar
  len := getWordLength(word);
  ori := getRandomNumber(1, 3);
  
  si ori = 1 llavors {VERTICAL}
    i := getRandomNumber(1, n - len + 1);
    j := getRandomNumber(1, m);
    per k := 1 fins len fer
      soup[i + k - 1][j] := word[k];
    fper
  sino si ori = 2 llavors {HORIZONTAL}
    i := getRandomNumber(1, n);
    j := getRandomNumber(1, m - len + 1);
    per k := 1 fins len fer
      soup[i][j + k - 1] := word[k];
    fper
  sino {DIAGONAL}
    i := getRandomNumber(1, n - len + 1);
    j := getRandomNumber(1, m - len + 1);
    per k := 1 fins len fer
      soup[i + k - 1][j + k - 1] := word[k];
    fper
  fsi
faccio
