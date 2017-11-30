#include "scanner.h"

void UngetToken(token* tok)
{
    returned=tok;
}

int Is_Keyword(const char *nacteny_text) {
	char *array[35] = {"as", "asc", "declare", "do", "dim", "double", "else", "end", "chr", "function", "if", "input",
	 "length", "loop", "print", "return", "scope", "string", "then", "while", "and", "boolean",
	 "continue", "elseif", "exit", "false", "for", "next", "not", "or", "shared", "static", "true", "substr", "integer"} ;

	for (int n = 0; n < 35; n++) {
		if (strcmp(nacteny_text, array[n]) == 0) {
			return n;
		}
	}
	return 1066;
}

int AllowedNextChar(char znak) {		//funkce overuje, ze nasledujici znak je v mnozine povolenych znaku napr. 123+14 ,zde to plus
	if ((znak==';') || (znak=='/') || (znak=='*') || (znak=='+') || (znak=='-') || (znak==')') || (znak=='=')
		|| (znak=='>') || (znak=='<') || (znak==',') || (isspace(znak)) || (znak == EOF))
		return 0;
	else
		return 1;
}

    token* GetToken(FILE* soubor)
    {
        if (returned!=NULL)
        {
            token* pom=returned;
            returned=NULL;
            return pom;
        }

    buffer* buff = (buffer*) malloc(sizeof(buffer));
   	InitBuffer(buff);
    token* tok = (token*) malloc(sizeof(token));
	//nacitani znaku
	char znak; // jeden nacteny znak

	// pro cela cisla (cc) a desetinna cisla (dc)
	int pouze_jedno_e = 0; 			//v dc bude pouze jedno 'e', pripadne 'E'
	int pouze_jedno_znamenko = 0;	//v dc bude pouze jedno '+', pripadne '-'
	int na_konci_je_cislice = 0;	//zajistuje, ze cc nebo dc bude koncit cislici
	int ne_zac_nula = 0;
	int pocitadlo_nul = 0;
	int zacatek_bezNuly = 0;
	int bylo_E = 0;
	int nenula_za_teckou = 0;
	int nenula_za_E = 0;

    int state = 0; //Konecny automat

	while(42) {

	znak = fgetc(soubor);

		switch (state) {
			case 0:
					if ((isdigit(znak)) && (znak != '0')) {
						AddChar(buff, znak);
						zacatek_bezNuly = 1;
						na_konci_je_cislice = 1;
						state = 1; }

					else if ((isdigit(znak)) && (znak == '0')) {
						pocitadlo_nul = 1;
						na_konci_je_cislice = 1;
						state = 1; }

					else if (znak == EOF) {
						AddChar(buff, znak);
						tok->type = tEOF;
						FreeBuffer(buff);
						free(buff);
						return tok;  }

					else if (isalpha(znak)) {
						state = 5;
						AddChar(buff, tolower(znak)); }

					else if (isspace(znak)) { state = 0;
						if (znak == '\n') {
							AddChar(buff, znak);
							tok->type = tEOL;
							FreeBuffer(buff);
							free(buff);
							return tok;	}
						}

					else if (znak == '+') {
						AddChar(buff, znak);
						tok->type = PLUS;
						FreeBuffer(buff);
						free(buff);
						return tok; }

					else if (znak == '-') {
						AddChar(buff, znak);
						tok->type = MINUS;
						FreeBuffer(buff);
						free(buff);
						return tok; }

					else if (znak == '*') {
						AddChar(buff, znak);
						tok->type = NASOBENI;
						FreeBuffer(buff);
						free(buff);
						return tok;	}

					else if (znak == '/') { state = 12;
						 }

					else if (znak == '@') {
						fprintf(stderr,"error, zadan nepovoleny znak\n");
						FreeBuffer(buff);
						free(buff);
						return tok;
					}

					else if (znak == '#') {
						state = 9;
					}

					else if (znak == '\0') {
						state = 0;
						 }

					else if (znak == 92) {	//jsem zpetne lomitko "\"
 						tok->type = CELO_CIS_DELENI;
 						FreeBuffer(buff);
 						free(buff);
                        return tok;	
						 }

					else if (znak == '\n') {
						state = 0;
						 }
					else if (znak == '!') {
						state = 10;
					}

					else if (znak == '$') {
						fprintf(stderr,"error, zadan nepovoleny znak\n");
						FreeBuffer(buff);
						free(buff);
						return tok;
					}

					else if (znak == '^') {
						fprintf(stderr,"error, zadan nepovoleny znak\n");
						FreeBuffer(buff);
						free(buff);
						return tok;
					}

					else if (znak == '`') {
						fprintf(stderr,"error, zadan nepovoleny znak\n");
						FreeBuffer(buff);
						free(buff);
						return tok;
					}
					else if (znak == '~') {
						fprintf(stderr,"error, zadan nepovoleny znak\n");
						FreeBuffer(buff);
						free(buff);
						return tok;
					}
					else if (znak == '&') {
						fprintf(stderr,"error, zadan nepovoleny znak\n");
						FreeBuffer(buff);
						free(buff);
						return tok;
					}
					else if (znak == '_') {
						state = 6;
						AddChar(buff, znak); }

					else if (znak == '|') {
						fprintf(stderr,"error, zadan nepovoleny znak\n");
						FreeBuffer(buff);
						free(buff);
						return tok;
					}

					else if (znak == '.') {
						tok->type = TECKA;
						FreeBuffer(buff);
						free(buff);
						return tok;
					}

					else if (znak == ',') {
						tok->type = CARKA;
						FreeBuffer(buff);
						free(buff);
						return tok;
					}
					else if (znak == '?') {
						tok->type = OTAZNIK;
						FreeBuffer(buff);
						free(buff);
						return tok;
					}
					else if (znak == ';') {
						tok->type = STREDNIK;
						FreeBuffer(buff);
						free(buff);
						return tok;
					}
					else if (znak == '=') {
						tok->type = ROVNOST;
						FreeBuffer(buff);
						free(buff);
						return tok;

					}

					else if (znak == ':') {
						fprintf(stderr,"error, zadan nepovoleny znak\n");
						FreeBuffer(buff);
						free(buff);
						return tok;
					}

					else if (znak == '"') {
						fprintf(stderr,"error, zadan nepovoleny znak\n");
						FreeBuffer(buff);
						free(buff);
						return tok;
					}

					else if (znak == '%') {
						fprintf(stderr,"error, zadan nepovoleny znak\n");
						FreeBuffer(buff);
						free(buff);
						return tok;
					}

					else if (znak == 39) {   //radkovy komentar
						state = 9;
					}

					else if (znak == '<') {	state = 3; AddChar(buff, znak);	}

					else if (znak == '>') {	state = 4; AddChar(buff, znak); }


					else if (znak == '{') {
						fprintf(stderr,"error, zadan nepovoleny znak\n");
						FreeBuffer(buff);
						free(buff);
						return tok;
					}
					else if (znak == '}') {
						fprintf(stderr,"error, zadan nepovoleny znak\n");
						FreeBuffer(buff);
						free(buff);
						return tok;
					}

					else if (znak == '[') {
						fprintf(stderr,"error, zadan nepovoleny znak\n");
						FreeBuffer(buff);
						free(buff);
						return tok;
					}

					else if (znak == ']') {
						fprintf(stderr,"error, zadan nepovoleny znak\n");
						FreeBuffer(buff);
						free(buff);
						return tok;
					}

					else if (znak == '(') {
						tok->type = KULATA_ZAV_ZAC;
						FreeBuffer(buff);
						free(buff);
						return tok;
					}
					else if (znak == ')') {
						tok->type = KULATA_ZAV_KON;
						FreeBuffer(buff);
						free(buff);
						return tok;
					}

					// chybi zpetne lomitko \ a tohle '
					break;

			case 1: //CELE CISLO
					if (((isdigit(znak)) && (ne_zac_nula == 1)) || (((isdigit(znak)) && (znak != '0')))){ 	//je to cislice
						ne_zac_nula = 1;
						na_konci_je_cislice = 1;		//pokud ted bude konec je cislo v poradku
						AddChar(buff, znak);			//ulozeni do bufferu
					}
					else if ((isdigit(znak)) && (znak == '0')) {
						if (zacatek_bezNuly == 1) {
							AddChar(buff, znak);
						}
						else {
							na_konci_je_cislice = 1;
						}
					}

					else if ((znak == '.') && (na_konci_je_cislice != 0)) {	//je tam tecka -> je to des. cislo; musi pred nim byt cislice
						state = 2;		
						if ((zacatek_bezNuly == 0) && (pocitadlo_nul == 1) && (ne_zac_nula == 0)) {
							AddChar(buff, 48);
						}


						zacatek_bezNuly = 0;								//bude to deset. cislo
						na_konci_je_cislice = 0;		// pokud ted bude konec nejedna se o spravne zapsane cislo
						pocitadlo_nul = 0;
						AddChar(buff, znak);			//ulozeni do bufferu
					}

					else if (((znak == 'e') || (znak == 'E')) && (na_konci_je_cislice != 0)) {  // je to E nebo e ; musi pred nim byt cislice
						state = 2;								// bude to deset. cislo
						if ((zacatek_bezNuly == 0) && (pocitadlo_nul == 1) && (ne_zac_nula == 0)) {
							AddChar(buff, 48);
						}
						pocitadlo_nul = 0;
						bylo_E = 1;

						pouze_jedno_e += 1;						// zajisti pouze jedno e
						na_konci_je_cislice = 0;				// pokud ted bude konec nejedna se o spravne zapsane cislo
						AddChar(buff, znak);					// ulozeni do bufferu
					}

					else if ((na_konci_je_cislice == 1) && (AllowedNextChar(znak) == 0)) {     // && kdyz je znak == ; , } ] )= // `... pak ungec(znak) jine znaky nepoustet
						ungetc(znak, soubor);
						if ((zacatek_bezNuly == 0) && (pocitadlo_nul == 1) && (ne_zac_nula == 0)) {
							AddChar(buff, 48);
						}

						tok->type = NUMBER_INT;
						tok->int_hodnota = atoi(GetStringBuffer(buff));
						FreeBuffer(buff);
						free(buff);
						return tok;
					}


					else {
						fprintf(stderr,"error, chyba pri zpracovani celych cisel\n");
						return tok;
						//zbudou nepovolene znaky hod error
					}

					break;

			case 2: //DESETINNE CISLO
					if (isdigit(znak)) {				//je to cislice
						if ((znak != '0') && (bylo_E == 0)) {
					
							nenula_za_teckou = 1;
							if (pocitadlo_nul != 0) {
								for (pocitadlo_nul; pocitadlo_nul != 0; pocitadlo_nul--)	{
									AddChar(buff, 48); //pridavam nulu
								}
							}
							na_konci_je_cislice = 1;		//pokud ted bude konec je cislo v poradku
							AddChar(buff, znak);			//ulozeni do bufferu
						}
						else if ((znak == '0') && (bylo_E == 0)) {
							na_konci_je_cislice = 1;		//pokud ted bude konec je cislo v poradku
							pocitadlo_nul += 1;
						}
						else if (((znak != '0') || (zacatek_bezNuly == 1)) && (bylo_E == 1)) {

							nenula_za_E = 1;
							na_konci_je_cislice = 1;		//pokud ted bude konec je cislo v poradku
							if ((pocitadlo_nul != 0) && (zacatek_bezNuly == 1)) {

								for (pocitadlo_nul; pocitadlo_nul != 0; pocitadlo_nul--)	{
									AddChar(buff, 48); //pridavam nulu
								}
							}
							else {
								pocitadlo_nul = 0;
							}
							zacatek_bezNuly = 1;
							AddChar(buff, znak);			//ulozeni do bufferu
						}
						else if ((znak == '0') && (bylo_E == 1) && (zacatek_bezNuly == 0)) {
							nenula_za_E = 0;
							na_konci_je_cislice = 1;
							pocitadlo_nul += 1; 
						}
									//ulozeni do bufferu
					}

					else if (((znak == 'e') || (znak == 'E')) && (pouze_jedno_e == 0)) {
						pocitadlo_nul = 0;
						bylo_E = 1;
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
					 if (nenula_za_teckou == 0) {
							AddChar(buff, 48);
						}
						if (nenula_za_E == 0) {
							AddChar(buff, 48);
						}

					ungetc(znak, soubor);
					tok->type = NUMBER_DOUBLE;
					tok->double_hodnota = strtod(GetStringBuffer(buff), NULL);
					FreeBuffer(buff);
					free(buff);
					return tok;

					}

					else{							//neco je spatne
						// nejaky error
						fprintf(stderr,"error, chyba pri zpracovani desetinych cisel\n");
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

					FreeBuffer(buff);
					free(buff);
					return tok;

			case 5: // klicove slovo
					if ((!isalpha(znak)) && (!isdigit(znak)) && (znak != '_')) {
						ungetc (znak, soubor);
                        buff->str[buff->lenght]='\0';
						int neco = Is_Keyword(GetStringBuffer(buff));
						if (neco != 1066) {	// je to keyword

						if (neco==1) { tok->type = ASC;} 		else if (neco==2) { tok->type = DECLARE;}  		else if (neco==3) { tok->type = DO;}
						else if (neco==4) { tok->type = DIM;} 	else if (neco==5) { tok->type = DOUBLE;} 	else if (neco==6) { tok->type = ELSE;}
						else if (neco==7) { tok->type = END;} 	else if (neco==8) { tok->type = CHR;}		else if (neco==9) { tok->type = FUNCTION;}
						else if (neco==10) { tok->type = IF;} 	else if (neco==11) { tok->type = INPUT;} 	else if (neco==12) { tok->type = LENGTH;}
						else if (neco==13) { tok->type = LOOP;} else if (neco==14) { tok->type = PRINT;} 	else if (neco==15) { tok->type = RETURN;}
						else if (neco==16) { tok->type = SCOPE;} else if (neco==17) { tok->type = STRING;} 	else if (neco==18) { tok->type = THEN;}
						else if (neco==19) { tok->type = WHILE;} else if (neco==20) { tok->type = AND;} 	else if (neco==21) { tok->type = tBOOLEAN;}
						else if (neco==22) { tok->type = tCONTINUE;} else if (neco==23) { tok->type = ELSEIF;} else if (neco==24) { tok->type= EXIT;}
						else if (neco==25) { tok->type = tFALSE;} 	else if (neco==26) { tok->type = FOR;} 	  else if (neco==27) { tok->type = NEXT;}
						else if (neco==28) { tok->type = NOT;} 		else if (neco==29) { tok->type = OR;} 	  else if (neco==30) { tok->type = SHARED;}
						else if (neco==31) { tok->type = STATIC;} 	else if (neco==32) { tok->type = tTRUE;}  else if (neco==33) { tok->type = SUBSTR;}
						else if (neco==34) { tok->type = INTEGER;} 	else if (neco== 0) { tok->type = AS;}
							FreeBuffer(buff);
							free(buff);
							return tok;
						}

						else {
							tok->type = ID;
							tok->string_hodnota = realloc(tok->string_hodnota, buff->lenght);
							strcpy(tok->string_hodnota, buff->str);
							tok->string_hodnota[buff->lenght]='\0';
							FreeBuffer(buff);
							free(buff);
							return tok; ;
						}
					}
					else if ((isdigit(znak)) || (znak == '_')) {
						AddChar(buff, znak);
						state = 6; }

					else {
						AddChar(buff, tolower(znak));}
					break;

			case 6: // je to ID
					if ((isalpha(znak)) || (isdigit(znak)) || (znak == '_')) {
						AddChar(buff, tolower(znak));
					}

					else {
							ungetc (znak, soubor);
							tok->type = ID;
							tok->string_hodnota = realloc(tok->string_hodnota, buff->lenght);
							strcpy(tok->string_hodnota, buff->str);
							tok->string_hodnota[buff->lenght]='\0';
							FreeBuffer(buff);
							free(buff);
							return tok; ;
					}
					break;
			case 7:
					fprintf(stderr,"error, chyba konecneho automatu\n");
					state = 0;
					break;
			case 8:

					fprintf(stderr,"error, chyba konecneho automatu\n");
					state = 0;

					break;

			case 9: //jednoradkovy komentar
					if ((znak == '\n') || (znak == EOF)) {
						ungetc (znak, soubor);
						state = 0;
					}
					else {

					}
					break;
			case 10: //stringovy literal 1/2
					 if (znak == '"'){
					 	state = 11;
					 	}
					 else { fprintf(stderr,"error, chyba retezcoveho literalu\n");
						}
					 break;

			case 11: //stringovy literal 2/2
					 if (znak == '"')  {
					 		tok->type = RETEZEC;
							tok->string_hodnota = realloc(tok->string_hodnota, buff->lenght);
							strcpy(tok->string_hodnota, buff->str);
							tok->string_hodnota[buff->lenght]='\0';
							FreeBuffer(buff);
							free(buff);
							return tok;
					 	}

					 else if (znak == '#') {
					 		fprintf(stderr,"error, chyba retezcoveho literalu\n");
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
								state = 0; }

					else {
						fprintf(stderr,"error, chyba blokoveho komentare\n");
						return tok;
					}
					break;


		}

	} //konec while

}
