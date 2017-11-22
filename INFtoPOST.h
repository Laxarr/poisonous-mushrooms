
#ifndef _INFIX2POSTFIX_H_
#define _INFIX2POSTFIX_H_

#include <stdio.h>
#include <stdlib.h>

#include "c202.h"                          /* využívá příklad c202 - zásobník */

#define MAX_LEN 64                          /* maximální délka řetězce výrazu */

extern int solved;                      /* Indikuje, zda byla operace řešena. */

/* Konverzní funkce */
char* infix2postfix (const char* infExpr);

#endif

/* Konec hlavičkového souboru c204.h */
