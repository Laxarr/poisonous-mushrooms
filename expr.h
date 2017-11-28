#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef EXPR
#define EXPR

#define POSTEXPSIZE 100
#include "parser.h"
#include "stack.h"

int Expr_Analysis();
token* postfixexp[POSTEXPSIZE];
#endif
