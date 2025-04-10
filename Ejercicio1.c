//Declareu un tipus dades tPosition, que conté un parell de coordenades enteres (horitzontal i vertical). Aquestes coordenades serviran per saber on està col·locada una paraula dins la “sopa”. Acompanyant les coordenades, caldrà indicar també en quina d’aquestes tres orientacions està col·locada la paraula: HORITZONTAL, VERTICAL o DIAGONAL.

tipus
	tLugar { HORIZONTAL, VERTICAL, DIAGONAL}
	tPosition: tupla 
			horizontal:  entero
			vertical:  entero 
			diagonal: tLugar 
		ftupla
ftipus


//Declareu un tipus de dades tWord per representar una paraula de la “sopa de lletres”. Una paraula no tindrà més de 15 caràcters. A més, caldrà saber si la paraula ha estat trobada o no durant el joc i la seva posició.

const
	CARACTERS: char= 15;
fconst
tipus
	tWord: tupla
			paraula: taula [CARACTERS] de tPosition;
			posicion: tPosition
			encontrar: boolean
ftupla
ftipus


//Declareu un tipus tSoup per representar una sopa de lletres. Sabem que la quadrícula de la “sopa” tindrà unes dimensions de, com a mínim, 15x15 i, com a màxim, 50x50 lletres. També necessitarem saber en quin “estat” està la sopa: buida, omplerta amb caràcters aleatoris o omplerta amb les paraules a cercar. Aquest darrer estat és el que deixa la “sopa” llesta per començar a cercar les paraules.

tipus
	tEstat {BUIDA, OMPLERTA, PARAULA};
	tSoup: tupla
		sopa: tEstat
		paraula: tWord
		ftupla
ftipus

//Declareu un tipus de dades tSearch per emmagatzemar les paraules que haurem de buscar dins la sopa. No buscarem mai més de 15 paraules.

const 
	PARAULES: char[] = 15;
fconst
tipus 
	tSearch:  taula[PARAULES] de tWord;
ftipus


//Declareu un tipus de dades tGame per guardar tota la informació relativa a una partida de “sopa de lletres”: la sopa en si mateixa i les paraules a buscar.

tipus 
	tGame: tupla
			sopa: tSoup
			paraula_cercar: tWord
		ftupla
ftipus
