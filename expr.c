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
    else if (tok->type == STREDNIK) return 5;
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
    if (tok->type==ID || tok->type==LENGTH || tok->type==SUBSTR || tok->type==ASC || tok->type==CHR)//volani funkce
    {
        if (tok->type==LENGTH) tok->string_hodnota="Length";
        if (tok->type==SUBSTR) tok->string_hodnota="SubStr";
        if (tok->type==ASC) tok->string_hodnota="Asc";
        if (tok->type==CHR) tok->string_hodnota="Chr";

        if (sym_tab_find(GlobalST,tok->string_hodnota)!=NULL)
        {
            char* funid=tok->string_hodnota;
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

                    PushParam(tok);

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

                if (strcmp(funid,"Length")==0)
                {
                    Length();
                }
                else if (strcmp(funid,"SubStr")==0)
                {
                    SubStr();
                }
                else if (strcmp(funid,"Asc")==0)
                {
                    Asc();
                }
                else if (strcmp(funid,"Chr")==0)
                {
                    Chr();
                }
                else
                {
                    Call_fun(funid);
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
    if (index==1)
    {
        PushParam(postfixexp[0]);
        return 1;
    }
    int i=0;
    for (;i<index;i++)
    {
        int typ=ValidType(postfixexp[i]);
        if (typ==1)
        {
            stackPush(postfixexp[i],zasobnik);
        }
        else if (typ==4)
        {
            token* op=postfixexp[i];
            token* op2=stackTop(zasobnik);
            stackPop(zasobnik);
            token* op1=stackTop(zasobnik);
            stackPop(zasobnik);
            Operation(op,op1,op2);
            stackPush(NULL,zasobnik);
        }

    }
    stackPop(zasobnik);
    return 1;
}
