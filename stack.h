/********* stack.h *********
 *
 * FIT VUT, IFJ 119
 * Author: Ondrej Brekl, xbrekl00
 * Summary: Zasobnik.
 *
 */
#ifndef STACK
#define STACK

#include "scanner.h"
#include "parser.h"
#include "error.h"

#define STACKSIZE 100

typedef struct {
	token* arr[STACKSIZE];
	int top;
	int allocsize;
} tStack;


void stackInit (tStack* zasobnik);
int stackEmpty (tStack* zasobnik);
int stackFull (tStack* zasobnik);
token* stackTop (tStack* zasobnik);
void stackPop (tStack* zasobnik);
void stackPush (token* tok,tStack* zasobnik);
#endif
