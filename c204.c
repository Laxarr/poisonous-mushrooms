
#include "c204.h"

int solved;
tStack* stack;
int STACK_SIZE;

/*
** Pomocná funkce untilLeftPar.
** Slouží k vyprázdnění zásobníku až po levou závorku, přičemž levá závorka
** bude také odstraněna. Pokud je zásobník prázdný, provádění funkce se ukončí.
**
** Operátory odstraňované ze zásobníku postupně vkládejte do výstupního pole
** znaků postExpr. Délka převedeného výrazu a též ukazatel na první volné
** místo, na které se má zapisovat, představuje parametr postLen.
**
** Aby se minimalizoval počet přístupů ke struktuře zásobníku, můžete zde
** nadeklarovat a používat pomocnou proměnnou typu char.
*/
void untilLeftPar ( tStack* s, char* postExpr, unsigned* postLen )
{
    char c;
    stackTop(s,&c);
    while (c != '(')
    {
        stackPop(s);
        postExpr[*postLen]=c;
        *postLen=*postLen+1;
        stackTop(s,&c);
    }
    stackPop(s);
}

/*
** Pomocná funkce doOperation.
** Zpracuje operátor, který je předán parametrem c po načtení znaku ze
** vstupního pole znaků.
**
** Dle priority předaného operátoru a případně priority operátoru na
** vrcholu zásobníku rozhodneme o dalším postupu. Délka převedeného
** výrazu a taktéž ukazatel na první volné místo, do kterého se má zapisovat,
** představuje parametr postLen, výstupním polem znaků je opět postExpr.
*/
void doOperation ( tStack* s, char c, char* postExpr, unsigned* postLen )
{
    int done=0;
    while (!done)
    {
        char ch;
        stackTop(s,&ch);
        if (stackEmpty(s))
        {
            stackPush(s,c);
            done++;
        }
        else if (ch == '(')
        {
            stackPush(s,c);
            done++;
        }
        else if ((ch == '-' || ch == '+') && (c == '*' || c == '/'))
        {
            stackPush(s,c);
            done++;
        }
        else
        {
            stackTop(s,&postExpr[*postLen]);
            stackPop(s);
            *postLen=*postLen+1;
        }
    }
}

/*
** Konverzní funkce infix2postfix.
** Čte infixový výraz ze vstupního řetězce infExpr a generuje
** odpovídající postfixový výraz do výstupního řetězce (postup převodu
** hledejte v přednáškách nebo ve studijní opoře). Paměť pro výstupní řetězec
** (o velikosti MAX_LEN) je třeba alokovat. Volající funkce, tedy
** příjemce konvertovaného řetězce, zajistí korektní uvolnění zde alokované
** paměti.
**
** Tvar výrazu:
** 1. Výraz obsahuje operátory + - * / ve významu sčítání, odčítání,
**    násobení a dělení. Sčítání má stejnou prioritu jako odčítání,
**    násobení má stejnou prioritu jako dělení. Priorita násobení je
**    větší než priorita sčítání. Všechny operátory jsou binární
**    (neuvažujte unární mínus).
**
** 2. Hodnoty ve výrazu jsou reprezentovány jednoznakovými identifikátory
**    a číslicemi - 0..9, a..z, A..Z (velikost písmen se rozlišuje).
**
** 3. Ve výrazu může být použit předem neurčený počet dvojic kulatých
**    závorek. Uvažujte, že vstupní výraz je zapsán správně (neošetřujte
**    chybné zadání výrazu).
**
** 4. Každý korektně zapsaný výraz (infixový i postfixový) musí být uzavřen
**    ukončovacím znakem '='.
**
** 5. Při stejné prioritě operátorů se výraz vyhodnocuje zleva doprava.
**
*/
char* infix2postfix (const char* infExpr) {
    STACK_SIZE=MAX_LEN;
	stack = (tStack*) malloc(sizeof(tStack));
    unsigned i=0;
    unsigned j=0;
    stackInit(stack);
    char* postExpr =(char*) malloc(sizeof(char)*MAX_LEN);
    if (postExpr==NULL) return NULL;
    while (infExpr[i] != '\0')
    {
        if ((infExpr[i]>47 && infExpr[i]<58) || (infExpr[i]>64 && infExpr[i]<91) || (infExpr[i]>96 && infExpr[i]<123))
        {
            postExpr[j]=infExpr[i];
            j++;
        }
        else if (infExpr[i] == '(')
        {
            stackPush(stack,infExpr[i]);
        }
        else if (infExpr[i] == ')')
        {
            untilLeftPar(stack,postExpr,&j);
        }
        else if (infExpr[i]== '=')
        {
            while (!stackEmpty(stack))
            {
                stackTop(stack,&postExpr[j]);
                stackPop(stack);
                j++;
            }
            postExpr[j]=infExpr[i];
        }
        else if (infExpr[i] == '+' || infExpr[i] == '-' || infExpr[i] == '*' || infExpr[i] == '/')
        {
            doOperation(stack,infExpr[i],postExpr,&j);
        }
    i++;
    }
    postExpr[i]='\0';
    return postExpr;
}

/* Konec c204.c */
