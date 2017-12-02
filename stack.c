/********* stack.c *********
 *
 * FIT VUT, IFJ 119
 * Author: Ondrej Brekl, xbrekl00
 * Summary: Zasobnik.
 *
 */
#include "stack.h"

void stackInit (tStack* zasobnik)
{
    zasobnik->top=-1;
}

int stackEmpty (tStack* zasobnik)
{
    return (zasobnik->top==-1) ? 1 : 0;
}

int stackFull (tStack* zasobnik)
{
    return (zasobnik->top==STACKSIZE-1) ? 1 : 0;
}

token* stackTop (tStack* zasobnik)
{
    return zasobnik->arr[zasobnik->top];
}

void stackPop (tStack* zasobnik)
{
    zasobnik->top--;
}

void stackPush (token* tok,tStack* zasobnik)
{
    zasobnik->top++;
    zasobnik->arr[zasobnik->top]=tok;
}

