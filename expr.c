/********* expr.c *********
 *
 * FIT VUT, IFJ 119
 * Author: Ondrej Brekl, xbrekl00
 * Summary: Precedencni analyza.
 *
 */
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
    else if (tok->type == ID)
    {
        if (sym_tab_find(CurrentST,tok->string_hodnota)==NULL)
        {
            Error(3);
        }
        return 1;
    }
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

int SameType(SymTab_Element* par,token* tok)
{
    if (tok->type==RETEZEC && par->data_type==SymTab_DataType_String)
        return 1;
    if (tok->type==NUMBER_DOUBLE && par->data_type==SymTab_DataType_Double)
        return 1;
    if (tok->type==NUMBER_INT && par->data_type==SymTab_DataType_Integer)
        return 1;
    if (tok->type==ID)
    {
        SymTab_DataType typ=sym_tab_find(CurrentST,tok->string_hodnota)->data_type;
        if (typ==par->data_type)
            return 1;
    }
    Error(4);
    return 0;
}

int Expr_Analysis()
{
    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type==tEOL || tok->type==STREDNIK || tok->type==THEN)
        Error(2);

    if (tok->type==ID || tok->type==LENGTH || tok->type==SUBSTR || tok->type==ASC || tok->type==CHR)//volani funkce
    {
        if (tok->type==LENGTH) tok->string_hodnota="Length";
        else if (tok->type==SUBSTR) tok->string_hodnota="SubStr";
        else if (tok->type==ASC) tok->string_hodnota="Asc";
        else if (tok->type==CHR) tok->string_hodnota="Chr";

        if (sym_tab_find(GlobalST,tok->string_hodnota)!=NULL)
        {
            char* funid=tok->string_hodnota;
            SymTab_Element* pom = sym_tab_find(GlobalST,funid);
            tok=GetToken(soubor);
            PrintToken(tok);

            if (tok->type==KULATA_ZAV_ZAC)
            {
                tok=GetToken(soubor);
                PrintToken(tok);

                int i = 0;
                while(tok->type!=KULATA_ZAV_KON)
                {
                    if (!(tok->type==RETEZEC || tok->type==NUMBER_DOUBLE || tok->type==NUMBER_INT || tok->type==ID))
                    {
                        Error(4);
                        return 0;
                    }
                    if (tok->type==ID)
                    {
                        if (sym_tab_find(CurrentST,tok->string_hodnota)==NULL)
                        {
                            Error(3);
                        }
                    }
                    if (i==pom->paramcount)
                    {
                        Error(4);
                    }
                    char* str=pom->pararr->par[i];
                    SymTab_Element* par=sym_tab_find(pom->localtable,str);
                    if (SameType(par,tok)==0)
                    {
                        Error(4);
                    }
                    PushParam(tok);

                    i++;

                    tok=GetToken(soubor);
                    PrintToken(tok);
                    if (tok->type==KULATA_ZAV_KON)
                    {
                        break;
                    }
                    if (tok->type!=CARKA)
                    {
                        Error(2);
                        return 0;
                    }
                    tok=GetToken(soubor);
                    PrintToken(tok);
                }
                if (i!=pom->paramcount)
                {
                    Error(4);
                }
                if (tok->type!=KULATA_ZAV_KON)
                {
                    Error(2);
                    return 0;
                }
                tok=GetToken(soubor);
                PrintToken(tok);
                if (tok->type!=STREDNIK)
                {
                    if (tok->type!=tEOL)
                    {
                        Error(2);
                    }
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
                UngetToken(tok);
            }
            return 1;
        }
        if (sym_tab_find(CurrentST,tok->string_hodnota)==NULL)
        {
            Error(3);
        }
    }

    zasobnik = (tStack*) malloc(sizeof(tStack));
    stackInit(zasobnik);
    int index=0;
    token* pred=NULL;
    if (ValidType(tok)==4)
        Error(2);

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
            Error(2);
        }
        pred=tok;
        tok=GetToken(soubor);
        PrintToken(tok);
        if (ValidType(tok)==1 && ValidType(pred)==1)
        {
            Error(2);
        }
        else if (ValidType(pred)==4 && ValidType(tok)==4)
        {
            Error(2);
        }
        else if (ValidType(pred)==1 && ValidType(tok)==2)
        {
            Error(2);
        }
        else if (ValidType(pred)==1 && ValidType(tok)==2)
        {
            Error(2);
        }
        else if (ValidType(pred)==3 && ValidType(tok)==1)
        {
            Error(2);
        }
        else if (ValidType(pred)==2 && ValidType(tok)==4)
        {
            Error(2);
        }
        else if (ValidType(pred)==4 && ValidType(tok)==3)
        {
            Error(2);
        }
        else if (ValidType(pred)==3 && ValidType(tok)==2)
        {
            Error(2);
        }
        else if (ValidType(pred)==2 && ValidType(tok)==3)
        {
            Error(2);
        }
        else if (ValidType(pred)==4 && ValidType(tok)==5)
        {
            Error(2);
        }
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
        if (writeout==1)
        {
            PushRetVal(postfixexp[0]);
            writeout=0;
            return 1;
        }
        else
        {
            PushParam(postfixexp[0]);
            return 1;
        }
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
            token* res =Operation(op,op1,op2);
            stackPush(res,zasobnik);
        }

    }
    printf("PUSHS TF@tempvar%d\n",tempvarcount-1);
    stackPop(zasobnik);
    return 1;
}
