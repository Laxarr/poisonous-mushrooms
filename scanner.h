#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "str.h"

typedef enum {

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
