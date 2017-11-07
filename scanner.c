#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "string.h"


int main (int argc, char **argv) {
	//argument bude název souboru
		//podminky kdyz bude spatnej pocet argumentu
	// mozna se muze brat vice argumentu, nebo jeste nejaky, NUTNO DODELAT
	//EXIT SE MUSI NECIM NAHRADIT
	if ((argc != 2) || (argv[1] == NULL)) {
		fprintf(stderr, "nespravne argumenty\n");
		exit(2);
	}

	//otevreni souboru
	FILE *soubor;

	char *nazev = argv[1];
	int state = 0;
	soubor = fopen(nazev,"rt");
		if (soubor == NULL) {
		    fprintf(stderr, "soubor nelze otevrit!\n");
		    exit(1);
		}

	typedef struct token_t {
    int token;
    char *buffer;
    struct token_t *next;
	} token_t;

	//nacitani znaku
		//bude to v cyklu (az po konec vstupu - NWM JAK HO POZNam) -slovo END SCOPE ukocuje prekladany program
	char znak; // jeden nacteny znak
	
	//while((znak = fgetc(soubor))) {

	int i = 10;			
	//tohle predelat na while, ale nwm kdy ma skoncit
	for (int n = 0; n<=i; n++) {
	
	znak = fgetc(soubor); 
	
	printf("%c\n", znak);
	
		switch (state) {

			case 0: 
					if (isdigit(znak)) {
						AddChar(buffer, znak);
						state = 1;
						
					}

					else if (isalpha(znak)) {
						printf("jsem pismeno\n");
						state = 2;
					}
					
					
					else if (isspace(znak)) {
						state = 0;
					}

					else if (znak == '+') { 
						//AddChar(buffer, znak);
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

			case 1: //cislo
					if (isdigit(znak)) {
						//AddChar(buffer, znak);
					}

					else if (znak == '.') {
					//	AddChar(buffer, znak);
					}

					else if ((znak == 'e') || (znak == 'E')) {
					//	AddChar(buffer, znak);
					}

					else {
						//prirazeni do tokenu
					}
					state = 0;
					break;

			case 2: //pismeno
					printf("state 2\n");
					state = 0;
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
			case 6: 
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
	}

	printf("\n");
	//zavreni souboru
	fclose (soubor);

	return 1;
}
