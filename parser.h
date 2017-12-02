/********* parser.h *********
 *
 * FIT VUT, IFJ 119
 * Author: Martin Gajdosik, xgajdo21
 * Summary: Parser.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef PARSER
#define PARSER

#include "scanner.h"
#include "debug.h"
#include "symtable.h"
#include "expr.h"
#include "codegenerator.h"
#include "string.h"
#include "error.h"

int Parse();
void BuildInFunctions();
int Program();
int Main();
int FunDec();
int FunDef();
int FunPars();
int Fun();
int Par();
int ParNext();
int Stat();
int S();
int E();
int Else();
int Out();
void DeleteEOL();
FILE* soubor;
Sym_Tab* GlobalST;
Sym_Tab* CurrentST;
int declared;
char* currentfun;
char* currentvar;
#endif
