#include "parser.h"

int main (int argc, char **argv) {
	//argument bude název souboru
		//podminky kdyz bude spatnej pocet argumentu
	// mozna se muze brat vice argumentu, nebo jeste nejaky, NUTNO DODELAT
	//EXIT SE MUSI NECIM NAHRADIT
	if ((argc != 2) || (argv[1] == "")) {
		fprintf(stderr, "nespravne argumenty\n");
		exit(2);
	}

	//otevreni souboru
	static FILE *soubor;

	char *nazev = argv[1];
	soubor = fopen(nazev,"rt");
		if (soubor == NULL) {
		    fprintf(stderr, "soubor nelze otevrit!\n");
		    exit(1);
		}

    token* tok=GetToken(soubor);

	fclose (soubor);
	return 1;
}
