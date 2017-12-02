/********* debug.h *********
 *
 * FIT VUT, IFJ 119
 * Author: Ondrej Brekl, xbrekl00
 * Summary: Vypis tokenu.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef DEBUG
#define DEBUG

#include "scanner.h"

void PrintToken(token* tok);

#endif
