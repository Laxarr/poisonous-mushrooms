/********* stack.c *********
 *
 * FIT VUT, IFJ 119
 * Author: Ondrej Brekl, xbrekl00
 * Summary: Zasobnik.
 *
 */
#include "stack.h"

void stackInit (tStack* zasobnik)//Inicializace zasobniku
{
    zasobnik->top=-1;
    zasobnik->allocsize=STACKSIZE;
}

int stackEmpty (tStack* zasobnik)//Kontola prazdnoty zasobniku
{
    return (zasobnik->top==-1) ? 1 : 0;
}

int stackFull (tStack* zasobnik)//Kontola plnosti zasobniku
{
    return (zasobnik->top==STACKSIZE-1) ? 1 : 0;
}

token* stackTop (tStack* zasobnik)//Vraci prvek na vrcholu zasobniku
{
    return zasobnik->arr[zasobnik->top];
}

void stackPop (tStack* zasobnik)//Odstrani prvek na vrcholu zasobniku
{
    zasobnik->top--;
}

void stackPush (token* tok,tStack* zasobnik)//Vlozi prvek na vrchol zasobnikuu
{
    if (stackFull(zasobnik))
    {
        Error(99);
    }
    zasobnik->top++;
    zasobnik->arr[zasobnik->top]=tok;
}
