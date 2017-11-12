#include "scanner.h"

int AllowedNextChar(char znak) {		//funkce overuje, ze nasledujici znak je v mnozine povolenych znaku napr. 123+14 ,zde to plus
	if ((znak==';') || (znak=='/') || (znak=='*') || (znak=='+') || (znak=='-') || (znak==')') || (znak=='=')
		|| (znak=='>') || (znak=='<') || (znak==',') || (isspace (znak)) || (znak == EOF))
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

	while(42) {  

	znak = fgetc(soubor);

    if (znak=='\n') break;
					// mozna udelat token i pro znak == eof, to tady teda neni ; ted tady je
	//printf("%c\n", znak);

		switch (state) {
			case 0:
					if (isdigit(znak)) {
						AddChar(buff, znak);
						state = 1;

					}

					else if (znak == EOF) {
						tok->type = tEOF;
						tok->string_hodnota = GetStringBuffer(buff);
						FreeBuffer(buff);
						free(buff);
						return tok;  }

					else if (isalpha(znak)) {
						state = 5;
						AddChar(buff, znak); }


					else if (isspace(znak)) { state = 0; }

					else if (znak == '+') {
						tok->type = PLUS;
						tok->string_hodnota = GetStringBuffer(buff);
						FreeBuffer(buff);
						free(buff);
						return tok; }

					else if (znak == '-') {
						tok->type = MINUS;
						tok->string_hodnota =GetStringBuffer(buff);
						FreeBuffer(buff);
						free(buff);
						return tok; }

					else if (znak == '*') {
						tok->type = NASOBENI;
						tok->string_hodnota =GetStringBuffer(buff);
						FreeBuffer(buff);
						free(buff);
						return tok;	}

					else if (znak == '/') {
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

					else if (znak == '<') {	state = 3;}

					else if (znak == '>') {	state = 4;}
					

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

					else if ((na_konci_je_cislice == 1) && (AllowedNextChar(znak) == 0)) {     // && kdyz je znak == ; , } ] )= // `... pak ungec(znak) jine znaky nepoustet
						ungetc(znak, soubor);
						tok->type = NUMBER_INT;
						tok->int_hodnota = atoi(GetStringBuffer(buff));
						printf("%s\n",buff->str);
						printf("kunda\n");
					FreeBuffer(buff);
					free(buff);
					return tok;
						// VYROBIT TOKEN
						// a nejak ukoncit
					}


					else {
						printf("error2\n");
						return tok;
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

					else if ((na_konci_je_cislice == 1) && (AllowedNextChar(znak) == 0)) {

					ungetc(znak, soubor);
					tok->type = NUMBER_DOUBLE;
					tok->double_hodnota = strtod(GetStringBuffer(buff), NULL);

						 printf("%s\n",buff->str);
					FreeBuffer(buff);
					free(buff);
					return tok;

					}

					else{							//neco je spatne
						// nejaky error
						printf("error\n");
						return tok;
					}
					break;

			case 3: // <= nebo <> nebo <
					if (znak == '=') {
						tok->type = MENSI_ROVNO;
					}
					else if (znak == '>') {
						tok->type = NEROVNOST;
					}
					else {
						ungetc (znak, soubor);
						tok->type = MENSI;
					}
					tok->string_hodnota = GetStringBuffer(buff);
					FreeBuffer(buff);
					free(buff);	
					return tok;

			case 4: // >= nebo >
					if (znak == '=') {
						tok->type = VETSI_ROVNO;
					}

					else {
						ungetc (znak, soubor);
						tok->type = VETSI;
					}
					tok->string_hodnota = GetStringBuffer(buff);
					FreeBuffer(buff);
					free(buff);				
					return tok;
					
			case 5: // klicove slovo
					if (!isalpha(znak)) {
						//ugetc ()
					//	int neco = Is_Keyword(buff);
						int neco;
						if (neco = 0) {
							// neni to key word 
							break;
						}
				/*		else if (neco==1) { tok.type = VETSI;} else if (neco==2) { tok.type = VETSI;} else if (neco==3) { tok.type = VETSI;} 
						else if (neco==4) { tok.type = VETSI;} else if (neco==5) { tok.type = VETSI;} else if (neco==6) { tok.type = VETSI;} 
						else if (neco==7) { tok.type = VETSI;} else if (neco==8) { tok.type = VETSI;} else if (neco==9) { tok.type = VETSI;} 
						else if (neco==10) { tok.type = VETSI;} else if (neco==11) { tok.type = VETSI;} else if (neco==12) { tok.type = VETSI;} 
						else if (neco==13) { tok.type = VETSI;} else if (neco==14) { tok.type = VETSI;} else if (neco==15) { tok.type = VETSI;} 
						else if (neco==16) { tok.type = VETSI;} else if (neco==17) { tok.type = VETSI;} else if (neco==18) { tok.type = VETSI;} 
						else if (neco==19) { tok.type = VETSI;} else if (neco==20) { tok.type = VETSI;} else if (neco==21) { tok.type = VETSI;}
						else if (neco==22) { tok.type = VETSI;} else if (neco==23) { tok.type = VETSI;} else if (neco==24) { tok.type = VETSI;} 
						else if (neco==25) { tok.type = VETSI;} else if (neco==26) { tok.type = VETSI;} else if (neco==27) { tok.type = VETSI;} 
						else if (neco==28) { tok.type = VETSI;} else if (neco==29) { tok.type = VETSI;} else if (neco==30) { tok.type = VETSI;}
						else if (neco==31) { tok.type = VETSI;} else if (neco==32) { tok.type = VETSI;} else if (neco==33) { tok.type = VETSI;} 
						else if (neco==34) { tok.type = VETSI;} else if (neco==35) { tok.type = VETSI;} */
					} 
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
    
}
