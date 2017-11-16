#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef SCANNER
#define SCANNER

#include "string.h"

typedef enum {
        tEOL,
		tEOF,
		ID,
		RETEZEC,
		PLUS,
		MINUS,
		NASOBENI,
		DELENI,
		MENSI,
		VETSI,
		VETSI_ROVNO,
		MENSI_ROVNO,
		NEROVNOST,
		ROVNOST,
		CARKA,
		STREDNIK,
		LEVA_ZAV,
		PRAVA_ZAV,
		KEYWORD,
		NUMBER_DOUBLE,
		NUMBER_INT
	} Ttoken;

	typedef struct {
		Ttoken type;
		union {
			int int_hodnota;
			double double_hodnota;
			char* string_hodnota;
		};
	} token;

	token* GetToken(FILE* soubor);
	int AllowedNextChar(char znak);
    void UngetToken(token* tok);
#endif
