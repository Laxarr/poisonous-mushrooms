#include <stdio.h>
#include <stdlib.h>
//#include <string.h>


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

	soubor = fopen(nazev,"rt");
		if (soubor == NULL) {
		    fprintf(stderr, "soubor nelze otevrit!\n");
		    exit(1);
		}

	//nacitani znaku
		//bude to v cyklu (az po konec vstupu - NWM JAK HO POZNam) -slovo END SCOPE ukocuje prekladany program
	char znak = (fgetc(soubor));

		//tady je obrovsky if, urcuju co to je za znak
	printf("%c\n", znak);

	//zavreni souboru
	fclose (soubor);

	return 1;
}
