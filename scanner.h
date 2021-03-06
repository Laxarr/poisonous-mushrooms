/********* scanner.h *********
 *
 * FIT VUT, IFJ 119
 * Author: Ondrej Brekl, xbrekl00
 * Author: Martin Gajdosik, xgajdo21
 * Summary: Lexical scanner.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef SCANNER
#define SCANNER

#include "string.h"
#include "error.h"

// nazvy typu tokenu

typedef enum {
        tEOF,
		tEOL,
		CELO_CIS_DELENI,
		TECKA,
		CARKA,
		MRIZKA,
		STREDNIK,
		KULATA_ZAV_KON,
		KULATA_ZAV_ZAC,
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
		NUMBER_DOUBLE,
		NUMBER_INT,
		TEMP,
		ASC,		//KLICOVA SLOVA
		DECLARE,
		DIM,
		DOUBLE,
		END,
		CHR,
		IF,
		INPUT,
		LOOP,
		PRINT,
		SCOPE,
		STRING,
		WHILE,
		AND,
		tCONTINUE,
		ELSEIF,
		tFALSE,
		FOR,
		NOT,
		OR,
		STATIC,
		tTRUE,
		INTEGER,
		AS,
		DO,
		ELSE,
		FUNCTION,
		LENGTH,
		RETURN,
		THEN,
		tBOOLEAN,
		EXIT,
		NEXT,
		SHARED,
		SUBSTR,
	} Ttoken;

	typedef struct {		//struktura tokenu
		Ttoken type;
		union {
			int int_hodnota;
			double double_hodnota;
			char* string_hodnota;
		};
	} token;

    token* returned;

	token* GetToken();
	int AllowedNextChar(char znak);
    void UngetToken(token* tok);
#endif
