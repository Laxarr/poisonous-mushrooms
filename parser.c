/********* parser.c *********
 *
 * FIT VUT, IFJ 119
 * Author: Martin Gajdosik, xgajdo21
 * Summary: Parser.
 *
 */
#include "parser.h"

int main ()//Vstupní bod programu
{
    Parse();
	return 0;
}

void BuildInFunctions() //Vložení funkcí Asc,SubStr,Chr,Length do tabulky symbolů
{
    SymTab_Element* pom=create_sym_tab_elem_fun("Length",SymTab_DataType_Integer);
    pom->paramcount=1;
    InsertPar(pom->pararr,"s");
    sym_tab_insert(GlobalST,pom);
    CurrentST=pom->localtable;
    pom=create_sym_tab_elem_par("s",SymTab_DataType_String);
    sym_tab_insert(CurrentST,pom);

    pom=create_sym_tab_elem_fun("SubStr",SymTab_DataType_String);
    pom->paramcount=3;
    InsertPar(pom->pararr,"s");
    InsertPar(pom->pararr,"i");
    InsertPar(pom->pararr,"n");
    sym_tab_insert(GlobalST,pom);
    CurrentST=pom->localtable;
    pom=create_sym_tab_elem_par("s",SymTab_DataType_String);
    sym_tab_insert(CurrentST,pom);
    pom=create_sym_tab_elem_par("i",SymTab_DataType_Integer);
    sym_tab_insert(CurrentST,pom);
    pom=create_sym_tab_elem_par("n",SymTab_DataType_Integer);
    sym_tab_insert(CurrentST,pom);

    pom=create_sym_tab_elem_fun("Asc",SymTab_DataType_Integer);
    pom->paramcount=2;
    InsertPar(pom->pararr,"s");
    InsertPar(pom->pararr,"i");
    sym_tab_insert(GlobalST,pom);
    CurrentST=pom->localtable;
    pom=create_sym_tab_elem_par("s",SymTab_DataType_String);
    sym_tab_insert(CurrentST,pom);
    pom=create_sym_tab_elem_par("i",SymTab_DataType_Integer);
    sym_tab_insert(CurrentST,pom);

    pom=create_sym_tab_elem_fun("Chr",SymTab_DataType_String);
    pom->paramcount=1;
    InsertPar(pom->pararr,"i");
    sym_tab_insert(GlobalST,pom);
    CurrentST=pom->localtable;
    pom=create_sym_tab_elem_par("i",SymTab_DataType_Integer);
    sym_tab_insert(CurrentST,pom);
}

int Parse()//Zahájení překladu
{
    GlobalST=sym_tab_init();//Inicializace Globalní tabulky symbolů
    BuildInFunctions();//Vložení funkcí Asc,SubStr,Chr,Length do tabulky symbolů
    Program_begin();//Vygeneruje první část vysledneho programu
    return Program();
}

void DeleteEOL()//Smazani znaků noveho řádku
{
    token* tok=GetToken(soubor);
    PrintToken(tok);
    while (tok->type==tEOL)
    {
        tok = GetToken(soubor);
        PrintToken(tok);
    }
    UngetToken(tok);
}

int Program()//Program
{
    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type==tEOF)
    {
        Error(2);
        return 0;
    }
    else
    {
        UngetToken(tok);
        return (Fun() && Main());
    }
}

int Main()//Hlavni telo programu
{
    SymTab_Element* pom=create_sym_tab_elem_fun("main",SymTab_DataType_Void);
    sym_tab_insert(GlobalST,pom);
    CurrentST=pom->localtable;
    currentfun="main";
    Main_fun();

    DeleteEOL();
    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=SCOPE)
    {
        Error(2);
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=tEOL)
    {
        Error(2);
        return 0;
    }

    int i=Stat();
    if (i==0)
        return 0;

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=END)
    {
        Error(2);
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=SCOPE)
    {
        Error(2);
        return 0;
    }
    DeleteEOL();
    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=tEOF)
    {
        Error(2);
    }
    return 1;
}

int FunDec()//Deklarace funkce
{
    DeleteEOL();
    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=DECLARE)
    {
        Error(2);
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=FUNCTION)
    {
        Error(2);
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=ID)
    {
        Error(2);
        return 0;
    }

    char* idfunkce=tok->string_hodnota;
    if (sym_tab_find(GlobalST,idfunkce)!=NULL)//Redeklarace funkce
    {
        Error(3);
        return 0;
    }
    declared=0;
    currentfun=idfunkce;
    SymTab_Element* pom=create_sym_tab_elem_fun(idfunkce,SymTab_DataType_Void);
    sym_tab_insert(GlobalST,pom);//Vlozeni nove funkce do tabulky symbolů
    CurrentST=pom->localtable;

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=KULATA_ZAV_ZAC)
    {
        Error(2);
        return 0;
    }

    int i=FunPars();
    if (i==0)
        return 0;

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=KULATA_ZAV_KON)
    {
        Error(2);
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=AS)
    {
        Error(2);
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (!(tok->type==STRING || tok->type==DOUBLE || tok->type==INTEGER))
    {
        Error(2);
        return 0;
    }
    //Zjisti navratovy typ funkce
    pom=sym_tab_find(GlobalST,idfunkce);
    if (tok->type==STRING)
    {
        pom->data_type=SymTab_DataType_String;
    }
    else if (tok->type==DOUBLE)
    {
        pom->data_type=SymTab_DataType_Double;
    }
    else if (tok->type==INTEGER)
    {
        pom->data_type=SymTab_DataType_Integer;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=tEOL)
    {
        Error(2);
        return 0;
    }

    return 1;
}

int FunDef()//Definice funkce
{
    DeleteEOL();
    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=FUNCTION)
    {
        Error(2);
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=ID)
    {
        Error(2);
        return 0;
    }

    char* idfunkce=tok->string_hodnota;
    currentfun=idfunkce;
    SymTab_Element* pom=sym_tab_find(GlobalST,idfunkce);
    if (pom==NULL)//Pokud funkce neni deklarovana, vlozi ji do tabulky symbolu
    {
        declared=0;
        pom=create_sym_tab_elem_fun(idfunkce,SymTab_DataType_Void);
        sym_tab_insert(GlobalST,pom);
        CurrentST=pom->localtable;
    }
    else
    {
        if (pom->initialized==1)//Chyba pri redefinici funkce
        {
            Error(3);
        }
        declared=1;
        CurrentST=pom->localtable;
    }

    pom->initialized=1;

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=KULATA_ZAV_ZAC)
    {
        Error(2);
        return 0;
    }

    int i=FunPars();
    if (i==0)
        return 0;

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=KULATA_ZAV_KON)
    {
        Error(2);
        return 0;
    }

    Declare_fun(idfunkce);

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=AS)
    {
        Error(2);
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (!(tok->type==STRING || tok->type==DOUBLE || tok->type==INTEGER))
    {
        Error(2);
        return 0;
    }
    //Zjisti a zkontroluje navratovy typ funkce
    pom=sym_tab_find(GlobalST,idfunkce);
    if (declared==0)
    {
        if (tok->type==STRING)
        {
            pom->data_type=SymTab_DataType_String;
        }
        else if (tok->type==DOUBLE)
        {
            pom->data_type=SymTab_DataType_Double;
        }
        else if (tok->type==INTEGER)
        {
            pom->data_type=SymTab_DataType_Integer;
        }
    }
    else
    {
        if (tok->type==STRING)
        {
            if (pom->data_type!=SymTab_DataType_String)
            {
                Error(3);
                return 0;
            }
        }
        else if (tok->type==DOUBLE)
        {
            if (pom->data_type!=SymTab_DataType_Double)
            {
                Error(3);
                return 0;
            }
        }
        else if (tok->type==INTEGER)
        {
            if (pom->data_type!=SymTab_DataType_Integer)
            {
                Error(3);
                return 0;
            }
        }
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=tEOL)
    {
        Error(2);
        return 0;
    }

    i=Stat();
    if (i==0)
        return 0;

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=END)
    {
        Error(2);
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=FUNCTION)
    {
        Error(2);
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=tEOL)
    {
        Error(2);
        return 0;
    }
    Declare_funend();

    return 1;
}

int FunPars()//Parametry funkci
{
    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type==ID)
    {
        UngetToken(tok);
        return (Par() && ParNext());
    }
    else if (tok->type==KULATA_ZAV_KON)
    {
        UngetToken(tok);
        return 1;
    }
    return 0;
}

int Fun()//Deklarace a definice funkci
{
    DeleteEOL();
    int fdec=-1;
    int fdef=-1;
    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type==SCOPE)
    {
        UngetToken(tok);
        return 1;
    }
    if (tok->type==DECLARE)//Bude nasledovat deklarace funkce
    {
        UngetToken(tok);
        fdec=FunDec();
        if (fdec==0)
            return 0;
    }
    if (fdec==1)
    {
        tok=GetToken(soubor);
        PrintToken(tok);
    }

    if (tok->type==FUNCTION)//Bude nasledovat definice funkce
    {
        UngetToken(tok);
        fdef= FunDef();
        if (fdef==0)
            return 0;
    }

    if (fdef==1)
    {
        tok=GetToken(soubor);
        PrintToken(tok);
    }
    if (fdec==-1 && fdef==-1)
    {
        if (tok->type!=SCOPE)
            Error(2);
    }
    if (fdec==-1)
    {
        fdec=1;
    }

    if (fdef==-1)
    {
        fdef=1;
    }
    UngetToken(tok);
    return (Fun() && fdef && fdec);

}

int Par()//Parametr funkce
{

    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=ID)
    {
        Error(2);
        return 0;
    }
    char* idpar=tok->string_hodnota;
    if (sym_tab_find(GlobalST,idpar)!=NULL)//Id parametru je stejny jako id nejak funkce
    {
        Error(3);
    }
    for (int i = 0;i<sym_tab_find(GlobalST,currentfun)->paramcount-1;i++)//Duplicita id v parametrech funkce
    {
        if (strcmp(idpar,sym_tab_find(GlobalST,currentfun)->pararr->par[i])==0)
        {
            Error(3);
        }
    }
    if (declared==1)
    {
        if (sym_tab_find(CurrentST,idpar)==NULL)
        {
            Error(3);
            return 0;
        }
    }
    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=AS)
    {
        Error(2);
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (!(tok->type==STRING || tok->type==DOUBLE || tok->type==INTEGER))
    {
        Error(2);
        return 0;
    }
    //Datovy typ parametru
    SymTab_DataType typ;
    if (tok->type==STRING)
    {
        typ=SymTab_DataType_String;
    }
    else if (tok->type==DOUBLE)
    {
        typ=SymTab_DataType_Double;
    }
    else if (tok->type==INTEGER)
    {
        typ=SymTab_DataType_Integer;
    }
    if (declared==1)//Kontrola typu parametru pri deklrovane funkci
    {
        SymTab_Element* pom=sym_tab_find(CurrentST,idpar);
        if (pom->data_type!=typ)
        {
            Error(3);
            return 0;
        }
    }
    else//Vlozeni parametru do lokalni tabulky symbolu
    {
        SymTab_Element* pom=create_sym_tab_elem_par(idpar,typ);
        sym_tab_insert(CurrentST,pom);
        pom=sym_tab_find(GlobalST,currentfun);
        InsertPar(pom->pararr,idpar);
        pom->paramcount++;
    }

    return 1;
}

int ParNext()//Dalsi parametr funkce
{
    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type==KULATA_ZAV_KON)
    {
        UngetToken(tok);
        return 1;
    }
    if (tok->type!=CARKA)
    {
        Error(2);
        return 0;
    }

    int i=Par();
    if (i==0)
        return 0;

    return ParNext();
}

int Stat()//Blok prikazu
{
    DeleteEOL();
    int i=S();
    if (i==0)
        return 0;

    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type==LOOP)
    {
        UngetToken(tok);
        return 1;
    }
    else if (tok->type==ELSE)
    {
        UngetToken(tok);
        return 1;
    }
    else if (tok->type==END)
    {
        UngetToken(tok);
        return 1;
    }
    else if (tok->type==SCOPE)
    {
        Error(2);
    }

    UngetToken(tok);
    return Stat();
}

int S()//Prikaz
{
    DeleteEOL();
    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type==FUNCTION || tok->type==DECLARE || tok->type==SCOPE)
    {
        Error(2);
    }
    if (tok->type==DIM)//Deklarace promenne
    {
        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=ID)
        {
            Error(2);
            return 0;
        }
        if (sym_tab_find(GlobalST,tok->string_hodnota)!=NULL)
        {
            Error(3);
            return 0;
        }
        char* varid=tok->string_hodnota;
        SymTab_Element* pom=sym_tab_find(CurrentST,varid);
        if (pom!=NULL)
        {
            Error(3);
            return 0;
        }

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=AS)
        {
            Error(2);
            return 0;
        }

        tok=GetToken(soubor);
        PrintToken(tok);
        if (!(tok->type==STRING || tok->type==DOUBLE || tok->type==INTEGER))
        {
            Error(2);
            return 0;
        }

        SymTab_DataType typ;
        if (tok->type==STRING)
        {
            typ=SymTab_DataType_String;
        }
        else if (tok->type==DOUBLE)
        {
            typ=SymTab_DataType_Double;
        }
        else if (tok->type==INTEGER)
        {
            typ=SymTab_DataType_Integer;
        }

        pom=create_sym_tab_elem_var(varid,typ);
        sym_tab_insert(CurrentST,pom);
        Declare_var(pom->id);

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type==ROVNOST)
        {
            currentvar=varid;
            int i = E();
            if (i==0)
                return 0;

            pom=sym_tab_find(CurrentST,varid);
            if (pom->data_type!=exprtype)
            {
                if (pom->data_type==SymTab_DataType_Integer && exprtype==SymTab_DataType_Double)
                {
                    ConvertToInt();
                }
                else if (pom->data_type==SymTab_DataType_Double && exprtype==SymTab_DataType_Integer)
                {
                    ConvertToFloat();
                }
                else Error(4);
            }
            AssignVal(varid);
        }
        else
            UngetToken(tok);

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=tEOL)
        {
            Error(2);
            return 0;
        }
        return 1;
    }
    else if (tok->type==ID) //Prirazeni ID=E
    {
        SymTab_Element* pom=sym_tab_find(CurrentST,tok->string_hodnota);
        if (pom==NULL)
        {
            Error(3);
            return 0;
        }
        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=ROVNOST)
        {
            Error(2);
            return 0;
        }
        int i = E();
        if (i==0)
        {
            return 0;
        }
        if (pom->data_type!=exprtype)
        {
            if (pom->data_type==SymTab_DataType_Integer && exprtype==SymTab_DataType_Double)
            {
                ConvertToInt();
            }
            else if (pom->data_type==SymTab_DataType_Double && exprtype==SymTab_DataType_Integer)
            {
                ConvertToFloat();
            }
            else Error(4);
        }

        AssignVal(pom->id);
        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=tEOL)
        {
            Error(2);
            return 0;
        }
        return 1;
    }
    else if (tok->type==INPUT)//INPUT ID
    {
        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=ID)
        {
            Error(2);
            return 0;
        }
        SymTab_Element* pom=sym_tab_find(CurrentST,tok->string_hodnota);
        if (pom==NULL)
        {
            Error(3);
            return 0;
        }
        Read(tok);
        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=tEOL)
        {
            Error(2);
            return 0;
        }
    }
    else if (tok->type==PRINT)//PRINT OUT
    {
        return Out();
    }
    else if (tok->type==RETURN)//RETURN E
    {
        int i=strcmp(currentfun,"main");
        if (i==0)
        {
            Error(2);
            return 0;
        }
        i = E();
        if (i==0)
        {
            return 0;
        }

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=tEOL)
        {
            Error(2);
            return 0;
        }
        return 1;
    }
    else if (tok->type==IF)//If else
    {
        relationcond=0;
        int i=E();
        if (i==0)
            return 0;
        if (relationcond==0)
        {
            Error(4);
        }
        IfCond();

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=THEN)
        {
            Error(2);
            return 0;
        }

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=tEOL)
        {
            Error(2);
            return 0;
        }

        i=Stat();
        if (i==0)
            return 0;

        Iftrueend();
        IfElse();

        i=Else();
        if (i==0)
            return 0;

        IfEnd();

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=END)
        {
            Error(2);
            return 0;
        }

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=IF)
        {
            Error(2);
            return 0;
        }

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=tEOL)
        {
            Error(2);
            return 0;
        }
    }
    else if (tok->type==DO)//DO WHILE E Stat LOOP
    {
        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=WHILE)
        {
            Error(2);
            return 0;
        }

        LoopStart();

        relationcond=0;

        int i=E();
        if (i==0)
            return 0;

        if (relationcond==0)
        {
            Error(4);
        }

        LoopCond();

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=tEOL)
        {
            Error(2);
            return 0;
        }

        i=Stat();
        if (i==0)
            return 0;

        LoopEnd();

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=LOOP)
        {
            Error(2);
            return 0;
        }

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=tEOL)
        {
            Error(2);
            return 0;
        }
    }
    UngetToken(tok);
    return 1;
}

int E()//Vyraz
{
    return Expr_Analysis();
}

int Else()
{
    token* tok=GetToken(soubor);
    PrintToken(tok);

    if (tok->type!=ELSE)
    {
        Error(2);
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=tEOL)
    {
        Error(2);
        return 0;
    }

    int i = Stat();
    if (i==0)
        return 0;

    return 1;
}

int Out()
{
    writeout=1;
    int i=E();
    if (i==0)
        return 0;

    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=STREDNIK)
    {
        Error(2);
        return 0;
    }

    Write();

    tok=GetToken(soubor);
    PrintToken(tok);

    if (tok->type==tEOL)
    {
        return 1;
    }
    else
    {
        UngetToken(tok);
        return Out();
    }
    return 1;
}
