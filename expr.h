/********* expr.c *********
 *
 * FIT VUT, IFJ 119
 * Author: Ondrej Brekl, xbrekl00
 * Summary: Precedencni analyza.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef EXPR
#define EXPR

#define POSTEXPSIZE 100
#include "parser.h"
#include "stack.h"
#include "error.h"

int Expr_Analysis();
token* postfixexp[POSTEXPSIZE];
int SameType(SymTab_Element* par,token* tok);
void doOperation (token* tok,int* index );
void untilLeftPar (int* index );
int ValidType(token* tok);
int OperatorPriority(token* tok);
#endif
