#include "expr.h"

tStack* zasobnik;

int OperatorPriority(token* tok)
{
    if (tok->type == NASOBENI) return 3;
    else if (tok->type == DELENI) return 3;
    else if (tok->type == CELO_CIS_DELENI) return 2;
    else if (tok->type == PLUS) return 1;
    else if (tok->type == MINUS) return 1;
    else if (tok->type == NEROVNOST) return 0;
    else if (tok->type == VETSI) return 0;
    else if (tok->type == MENSI_ROVNO) return 0;
    else if (tok->type == VETSI_ROVNO) return 0;
    else if (tok->type == ROVNOST) return 0;
    else if (tok->type == MENSI) return 0;
    return -1;
}

int ValidType(token* tok)
{
    if (tok->type == PLUS) return 4;
    else if (tok->type == MINUS) return 4;
    else if (tok->type == NASOBENI) return 4;
    else if (tok->type == DELENI) return 4;
    else if (tok->type == MENSI) return 4;
    else if (tok->type == NEROVNOST) return 4;
    else if (tok->type == VETSI) return 4;
    else if (tok->type == MENSI_ROVNO) return 4;
    else if (tok->type == VETSI_ROVNO) return 4;
    else if (tok->type == ROVNOST) return 4;
    else if (tok->type == ID) return 1;
    else if (tok->type == NUMBER_INT) return 1;
    else if (tok->type == NUMBER_DOUBLE) return 1;
    else if (tok->type == KULATA_ZAV_ZAC) return 2;
    else if (tok->type == KULATA_ZAV_KON) return 3;
    else if (tok->type == RETEZEC) return 1;
    else if (tok->type == CELO_CIS_DELENI) return 4;
    else if (tok->type == tEOL) return 5;
    else if (tok->type == tEOF) return 5;
    else if (tok->type == THEN) return 5;
    else return 0;
}

void untilLeftPar (int* index )
{
    token* pom=stackTop(zasobnik);
    while (pom->type != KULATA_ZAV_ZAC)
    {
        stackPop(zasobnik);
        postfixexp[*index]=pom;
        *index=*index+1;
        pom=stackTop(zasobnik);
    }
    stackPop(zasobnik);
}

void doOperation (token* tok,int* index )
{
    int done=0;
    while (!done)
    {
        token* pom=stackTop(zasobnik);
        if (stackEmpty(zasobnik))
        {
            stackPush(tok,zasobnik);
            done++;
        }
        else if (pom->type == KULATA_ZAV_ZAC)
        {
            stackPush(tok,zasobnik);
            done++;
        }
        else if (OperatorPriority(tok)>OperatorPriority(pom))
        {
            stackPush(tok,zasobnik);
            done++;
        }
        else
        {
            postfixexp[*index]=stackTop(zasobnik);
            stackPop(zasobnik);
            *index=*index+1;
        }
    }
}

int Expr_Analysis()
{

    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type==ID)//volani funkce
    {
        if (sym_tab_find(GlobalST,tok->string_hodnota)!=NULL)
        {
            tok=GetToken(soubor);
            PrintToken(tok);
            if (tok->type==KULATA_ZAV_ZAC)
            {
                tok=GetToken(soubor);
                PrintToken(tok);
                while(tok->type!=KULATA_ZAV_KON)
                {
                    if (!(tok->type==RETEZEC || tok->type==NUMBER_DOUBLE || tok->type==NUMBER_INT || tok->type==ID))
                    {
                    return 0;
                    }
                    tok=GetToken(soubor);
                    PrintToken(tok);
                    if (tok->type==KULATA_ZAV_KON)
                    {
                        break;
                    }
                    if (tok->type!=CARKA)
                    {
                    return 0;
                    }
                    tok=GetToken(soubor);
                    PrintToken(tok);
                }

                if (tok->type!=KULATA_ZAV_KON)
                {
                    return 0;
                }
                tok=GetToken(soubor);
                PrintToken(tok);
                if (tok->type!=tEOL)
                {
                    return 0;
                }
            }
        }
    }

    zasobnik = (tStack*) malloc(sizeof(tStack));
    stackInit(zasobnik);
    int index=0;

    while (1)
    {
        int i = ValidType(tok);
        if (i==1)
        {
            postfixexp[index]=tok;
            index++;
        }
        else if (i==2)
        {
            stackPush(tok,zasobnik);
        }
        else if (i==3)
        {
            untilLeftPar(&index);
        }
        else if (i==4)
        {
            doOperation(tok,&index);
        }
        else if (i==5)
        {
            break;
        }
        else
        {
            return 0;
        }
        tok=GetToken(soubor);
        PrintToken(tok);
    }

    UngetToken(tok);

    while (!stackEmpty(zasobnik))
    {
        postfixexp[index]=stackTop(zasobnik);
        stackPop(zasobnik);
        index++;
    }
    //generuj kod
    return 1;
}
