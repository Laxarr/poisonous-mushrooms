#include "scanner.h"

int Is_Keyword(const char *nacteny_text) {
	char *array[35] = {"as", "asc", "declare", "do", "dim", "double", "else", "end", "chr", "function", "if", "input",
	 "integer", "lenght", "loop", "print", "return", "scope", "string", "substr", "then", "while", "and", "boolean", 
	 "continue", "elseif", "exit", "false", "for", "next", "not", "or", "shared", "static", "true" } ;

	for (int n = 0; n < 35; n++) {
		if (strcmp(nacteny_text, array[n]) == 0) {
			return 1;
		}
	}
}

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

    int state = 0; //Konecny automat

	while(42) {  

	znak = fgetc(soubor);

    if (znak=='\n') break;
					// mozna udelat token i pro znak == eof, to tady teda neni ; ted tady je
	//printf("%c\n", znak);

		switch (state) {
			case 0:
					if (isdigit(znak)) {
						AddChar(buff, znak);
						state = 1; }

					else if (znak == EOF) {
						tok->type = tEOF;
						tok->string_hodnota = GetStringBuffer(buff);
						FreeBuffer(buff);
						free(buff);
						return tok;  }

					else if (isalpha(znak)) {
						state = 5;
						AddChar(buff, znak); }

					else if (isspace(znak)) { state = 0;
						printf("jejda\n"); }

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

					else if (znak == '/') { state = 12;
						 }

					else if (znak == '@') {
						state = 0;
					}

					else if (znak == '#') {
						state = 0;
					}

					else if (znak == '\0') { 
						printf("zaddscccek\n");
						state = 0;
						 }

					else if (znak == 92) { 
						printf("zaddseeeek\n");
						state = 0;
						 }	 

					else if (znak == '\n') { 
						printf("zaddaasek\n");
						state = 0;
						 }
					else if (znak == '!') {
						printf("staaaate 2\n");
						state = 10;
						AddChar(buff, znak);
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
						state = 6;
						AddChar(buff, znak); }

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

					else if (znak == 39) {   
						state = 9;
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
					if ((!isalpha(znak)) && (!isdigit(znak)) && (znak != '_')) {
						ungetc (znak, soubor);

						int neco = Is_Keyword(GetStringBuffer(buff));
						if (neco == 1) {	// je to keyword 

							tok->type = KEYWORD;
							tok->string_hodnota = GetStringBuffer(buff);
							FreeBuffer(buff);
							free(buff);				
							return tok;
						}

						else {
							tok->type = ID;
							tok->string_hodnota = GetStringBuffer(buff);
							FreeBuffer(buff);
							free(buff);				
							return tok; ;
						}
					}
					else if ((isdigit(znak)) || (znak == '_')) {
						AddChar(buff, znak);
						state = 6; }

					else {
						AddChar(buff, znak);}
					break;

			case 6: // je to ID 
					if ((isalpha(znak)) || (isdigit(znak)) || (znak == '_')) {
						AddChar(buff, znak);
					}

					else {	
							ungetc (znak, soubor);
							tok->type = ID;
							tok->string_hodnota = GetStringBuffer(buff);
							FreeBuffer(buff);
							free(buff);				
							return tok; ;
					}
					break;
			case 7:
					printf("state 2\n");
					state = 0;
					break;
			case 8: 
			

						
					break;

			case 9: //jednoradkovy komentar
					printf("%c\n",znak );
					if (znak == '\n') {
						printf("sstate 2\n");
						state = 0;
					}
					else if (znak == '\0') {
						printf("swwtate 2\n");
						state = 0;
					}
					else {
						printf("staaaate 2\n");
					}
					break;
			case 10: //stringovy literal 1/2
					 if (znak == '"'){
					 	state = 11;
					 	AddChar(buff, znak);
					 	}
					 else { printf("tohle neni retezec\n");}
					
					 break;

			case 11: //stringovy literal 2/2
					 if (znak == '"')  {
					 		AddChar(buff, znak);

					 		printf("%s\n",buff->str);

					 		tok->type = RETEZEC;
							tok->string_hodnota = GetStringBuffer(buff);
							FreeBuffer(buff);
							free(buff);	
							return tok;
					 	}

					 else if (znak == '#') {
					 		printf("tohle neni retezec\n");
					 		 return tok; }
					 else {	
					 		AddChar(buff, znak);
					 } 

					 break;

			case 12: //komentar nebo deleni		
					if (znak == 39) {  //JE TO KOMENTAR
						state = 13;
					}

					else {		// je to deleni
						ungetc (znak, soubor);
						tok->type = DELENI;
						tok->string_hodnota = GetStringBuffer(buff);
						FreeBuffer(buff);
						free(buff);	
						return tok;
					}
					break;

			case 13: if (znak == 39) {
					state = 14; }
					break;

			case 14: 
					if (znak == '/') {
								printf("modrin\n");
								state = 0; }

					else {
						printf("erroeeer\n");
						return tok;
					}
					break;				


		}

	} //konec while
    
}
