#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef PARSER
#define PARSER

#include "scanner.h"
#include "debug.h"

int Parse();
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
int I();
int E();
int Else();
int Out();
void DeleteEOL();
FILE* soubor;
#endif
