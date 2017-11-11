#include "scanner.h"

int AllowedNextChar(char znak) {		//funkce overuje, ze nasledujici znak je v mnozine povolenych znaku napr. 123+14 ,zde to plus
	if ((znak==';') || (znak=='/') || (znak=='*') || (znak=='+') || (znak=='-') || (znak==')') || (znak=='=')
		|| (znak=='>') || (znak=='<') || (znak==',') || (isspace (znak))  )
		return 0;
	else
		return 1;
}

    token* GetToken(FILE* soubor)
    {
    buffer* buff = (buffer*) malloc(sizeof(buffer));
    InitBuffer(buff);
    token* tok = (token*) malloc(sizeof(token));
	//nacitani znaku
	char znak; // jeden nacteny znak

	// pro cela cisla (cc) a desetinna cisla (dc)
	int pouze_jedno_e = 0; 			//v dc bude pouze jedno 'e', pripadne 'E'
	int pouze_jedno_znamenko = 0;	//v dc bude pouze jedno '+', pripadne '-'
	int na_konci_je_cislice = 0;	//zajistuje, ze cc nebo dc bude koncit cislici

    int state = 0;
	while((znak = fgetc(soubor)) != EOF) {  // NEZAPOMENOUT NA EOF VYPISUJE JESTE NEWLINE + mozna jeste neco, nwm jestli je to problem

    if (znak=='\n') break;
					// mozna udelat token i pro znak == eof, to tady teda neni
	printf("%c\n", znak);

		switch (state) {
			case 0:
					if (isdigit(znak)) {
						AddChar(buff, znak);
						state = 1;

					}

					else if (isalpha(znak)) {
						state = 8;
					}


					else if (isspace(znak)) {
						state = 0;
					}

					else if (znak == '+') {
						AddChar(buff, znak);
						state = 0;
					}

					else if (znak == '-') {
						state = 0;
					}

					else if (znak == '*') {
						state = 4;
					}

					else if (znak == '/') {
						state = 0;
					}

					else if (znak == '+') {
						state = 0;
					}

					else if (znak == '@') {
						state = 0;
					}

					else if (znak == '#') {
						state = 0;
					}

					else if (znak == '!') {
						state = 0;
					}

					else if (znak == '$') {
						state = 0;
					}

					else if (znak == '^') {
						state = 0;
					}

					else if (znak == '`') {
						state = 0;
					}
					else if (znak == '~') {
						state = 0;
					}
					else if (znak == '&') {
						state = 0;
					}
					else if (znak == '_') {
						state = 0;
					}

					else if (znak == '|') {
						state = 0;
					}

					else if (znak == '.') {
						state = 0;
					}

					else if (znak == ',') {
						state = 0;
					}
					else if (znak == '?') {
						state = 0;
					}
					else if (znak == ';') {
						state = 0;
					}
					else if (znak == '=') {
						state = 0;
					}

					else if (znak == ':') {
						state = 0;
					}

					else if (znak == '"') {
						state = 0;
					}

					else if (znak == '%') {
						state = 0;
					}


					else if ((znak == '<') || (znak == '>')) {
						state = 0;
					}

					else if ((znak == '{') || (znak == '}')) {
						state = 0;
					}

					else if ((znak == '[') || (znak == ']')) {
						state = 0;
					}

					else if ((znak == '(') || (znak == ')')) {
						state = 0;
					}

					// chybi zpetne lomitko \ a tohle '
					break;

			case 1: //CELE CISLO
					if (isdigit(znak)) { 				//je to cislice
						na_konci_je_cislice = 1;		//pokud ted bude konec je cislo v poradku
						AddChar(buff, znak);			//ulozeni do bufferu
					}

					else if ((znak == '.') && (na_konci_je_cislice != 0)) {	//je tam tecka -> je to des. cislo; musi pred nim byt cislice
						state = 2;						//bude to deset. cislo
						na_konci_je_cislice = 0;		// pokud ted bude konec nejedna se o spravne zapsane cislo
						AddChar(buff, znak);			//ulozeni do bufferu
					}

					else if (((znak == 'e') || (znak == 'E')) && (na_konci_je_cislice != 0)) {  // je to E nebo e ; musi pred nim byt cislice
						state = 2;								// bude to deset. cislo
						pouze_jedno_e += 1;						// zajisti pouze jedno e
						na_konci_je_cislice = 0;				// pokud ted bude konec nejedna se o spravne zapsane cislo
						AddChar(buff, znak);					// ulozeni do bufferu

					}

					else if (na_konci_je_cislice == 1){     // && kdyz je znak == ; , } ] )= // `... pak ungec(znak) jine znaky nepoustet
						pouze_jedno_e == 0;					//ZEPTAT SE JAKE
						pouze_jedno_znamenko == 0;
						na_konci_je_cislice == 0;

						// VYROBIT TOKEN
						// a nejak ukoncit
					}


					else {
						//zbudou nepovolene znaky hod error



					}

					break;

			case 2: //DESETINNE CISLO
					if (isdigit(znak)) {				//je to cislice
						na_konci_je_cislice = 1;		//pokud ted bude konec je cislo v poradku
						AddChar(buff, znak);			//ulozeni do bufferu
					}

					else if (((znak == 'e') || (znak == 'E')) && (pouze_jedno_e == 0)) {
						pouze_jedno_e += 1;				// v dc bude pouze jedno 'e', pripadne 'E'	viz horejsi podminka
						na_konci_je_cislice = 0;		// pokud ted bude konec nejedna se o spravne zapsane cislo
						AddChar(buff, znak);			// ulozeni do bufferu
					}

					else if (((znak == '-') || (znak == '+')) && (pouze_jedno_e == 1) && (pouze_jedno_znamenko == 0)) {
						pouze_jedno_znamenko += 1;		// v dc bude pouze jedno '+', pripadne '-' a musi prednim byt prave jedno e
						na_konci_je_cislice = 0;		// pokud ted bude konec nejedna se o spravne zapsane cislo
						AddChar(buff, znak);			// ulozeni do bufferu
					}

					else if ((na_konci_je_cislice == 1) && (AllowedNextChar(znak) == 0)) {  // znak == ; , } ] )= // `... pak ungec(znak) jine znaky nepoustet

					ungetc(znak, soubor);
					tok->type = NUMBER_DOUBLE;
					tok->double_hodnota = strtod(GetStringBuffer(buff), NULL);

						pouze_jedno_e == 0;					//ZEPTAT SE JAKE
						pouze_jedno_znamenko == 0;
						na_konci_je_cislice == 0;
					}

					else{							//neco je spatne
						// nejaky error

					}
					break;

			case 3: // vykricnik
					printf("state 2\n");
					state = 0;
					break;
			case 4: // operator
					printf("state 4\n");
					state = 0;
					break;
			case 5: // klicove slovo
					printf("state 2\n");
					state = 0;
					break;
			case 6: //pismeno
					printf("state 2\n");
					state = 0;
					break;
			case 7:
					printf("state 2\n");
					state = 0;
					break;
			case 8:
					printf("state 2\n");
					state = 0;
					break;

		}

		//klicova slova
		//As, Asc, Declare, Dim, Do, Double, Else, End, Chr, Function, If, Input, Integer, Length
		//Loop, Print, Return, Scope, String, Substr, Then, While

		//And,Boolean, Continue, Elseif, Exit, False, For, Next, Not, Or, Shared, Static, True
	} //konec while
    FreeBuffer(buff);
	free(buff);
	return tok;
}
