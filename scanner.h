#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "string.h"

typedef enum {
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
