#include "parser.h"

int main (int argc, char **argv) {
	//argument bude název souboru
	//podminky kdyz bude spatnej pocet argumentu
	// mozna se muze brat vice argumentu, nebo jeste nejaky, NUTNO DODELAT
	//EXIT SE MUSI NECIM NAHRADIT
	if ((argc != 2) || (strcmp(argv[1],"") == 0))
    {
		fprintf(stderr, "nespravne argumenty\n");
		exit(2);
	}

	//otevreni souboru

	char *nazev = argv[1];
	soubor = fopen(nazev,"rt");
		if (soubor == NULL) {
		    fprintf(stderr, "soubor nelze otevrit!\n");
		    exit(1);
		}
/*
    token* tok = GetToken(soubor);
    while (tok->type!=tEOF)
    {
        PrintToken(tok);
        tok = GetToken(soubor);
    }
    PrintToken(tok);
*/
    printf("%d\n",Parse());
	fclose (soubor);
	return 0;
}

int Parse()
{
    GlobalST=sym_tab_init();
    Program_begin();
    return Program();
}

void DeleteEOL()//Smazani znaku noveho radku
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
    DeleteEOL();
    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type==tEOF)
    {
        return 1;
    }
    else
    {
        UngetToken(tok);
        return (Fun() && Main() && Program());
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
        return 0;
    }

    int i=Stat();
    if (i==0)
        return 0;

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=END)
    {
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=SCOPE)
    {
        return 0;
    }
    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=tEOL)
    {
        return 0;
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
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=FUNCTION)
    {
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=ID)
    {
        return 0;
    }

    char* idfunkce=tok->string_hodnota;
    if (sym_tab_find(GlobalST,idfunkce)!=NULL)
    {
        return 0;
    }
    declared=0;
    currentfun=idfunkce;
    SymTab_Element* pom=create_sym_tab_elem_fun(idfunkce,SymTab_DataType_Void);
    sym_tab_insert(GlobalST,pom);
    CurrentST=pom->localtable;

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=KULATA_ZAV_ZAC)
    {
        return 0;
    }

    int i=FunPars();
    if (i==0)
        return 0;

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=KULATA_ZAV_KON)
    {
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=AS)
    {
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (!(tok->type==STRING || tok->type==DOUBLE || tok->type==INTEGER))
    {
        return 0;
    }

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
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=ID)
    {
        return 0;
    }

    char* idfunkce=tok->string_hodnota;
    currentfun=idfunkce;
    SymTab_Element* pom=sym_tab_find(GlobalST,idfunkce);
    if (pom==NULL)
    {
        declared=0;
        pom=create_sym_tab_elem_fun(idfunkce,SymTab_DataType_Void);
        sym_tab_insert(GlobalST,pom);
        CurrentST=pom->localtable;
    }
    else
    {
        declared=1;
        CurrentST=pom->localtable;
    }
    Declare_fun(idfunkce);

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=KULATA_ZAV_ZAC)
    {
        return 0;
    }

    int i=FunPars();
    if (i==0)
        return 0;

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=KULATA_ZAV_KON)
    {
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=AS)
    {
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (!(tok->type==STRING || tok->type==DOUBLE || tok->type==INTEGER))
    {
        return 0;
    }

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
                return 0;
        }
        else if (tok->type==DOUBLE)
        {
            if (pom->data_type!=SymTab_DataType_Double)
                return 0;
        }
        else if (tok->type==INTEGER)
        {
            if (pom->data_type!=SymTab_DataType_Integer)
            return 0;
        }
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=tEOL)
    {
        return 0;
    }

    i=Stat();
    if (i==0)
        return 0;

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=END)
    {
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=FUNCTION)
    {
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=tEOL)
    {
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
    if (tok->type==DECLARE)
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

    if (tok->type==FUNCTION)
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
        return 0;
    }

    char* idpar=tok->string_hodnota;
    if (declared==1)
    {
        if (sym_tab_find(CurrentST,idpar)==NULL)
        {
            return 0;
        }
    }
    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=AS)
    {
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (!(tok->type==STRING || tok->type==DOUBLE || tok->type==INTEGER))
    {
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
    if (declared==1)
    {
        SymTab_Element* pom=sym_tab_find(CurrentST,idpar);
        if (pom->data_type!=typ)
        {
            return 0;
        }
    }
    SymTab_Element* pom=create_sym_tab_elem_fun(idpar,typ);
    sym_tab_insert(CurrentST,pom);
    pom=sym_tab_find(GlobalST,currentfun);
    InsertPar(pom->pararr,idpar);
    pom->paramcount++;

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
    return Stat();
}

int S()//Prikaz
{
    DeleteEOL();
    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type==DIM)//Deklarace promenne
    {
        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=ID)
        {
            return 0;
        }

        char* varid=tok->string_hodnota;
        SymTab_Element* pom=sym_tab_find(CurrentST,varid);
        if (pom!=NULL)
        {
            return 0;
        }

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=AS)
        {
            return 0;
        }

        tok=GetToken(soubor);
        PrintToken(tok);
        if (!(tok->type==STRING || tok->type==DOUBLE || tok->type==INTEGER))
        {
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
            return E();
        }
        UngetToken(tok);

        return 1;
    }
    else if (tok->type==ID) //Prirazeni ID=E
    {
        SymTab_Element* pom=sym_tab_find(CurrentST,tok->string_hodnota);
        if (pom==NULL)
        {
            return 0;
        }
        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=ROVNOST)
        {
            return 0;
        }
        return E();
    }
    else if (tok->type==INPUT)//INPUT ID
    {
        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=ID)
        {
            return 0;
        }
        SymTab_Element* pom=sym_tab_find(CurrentST,tok->string_hodnota);
        if (pom==NULL)
        {
            return 0;
        }
        Read(tok);
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
            return 0;
        }
        return E();
    }
    else if (tok->type==IF)//If else
    {

        int i=E();
        if (i==0)
            return 0;

        IfCond();

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=THEN)
        {
            return 0;
        }

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=tEOL)
        {
            return 0;
        }

        i=Stat();
        if (i==0)
            return 0;

        IfElse();

        i=Else();
        if (i==0)
            return 0;

        IfEnd();

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=END)
        {
            return 0;
        }

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=IF)
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
    else if (tok->type==DO)//DO WHILE E Stat LOOP
    {
        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=WHILE)
        {
            return 0;
        }

        LoopStart();

        int i=E();
        if (i==0)
            return 0;

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=tEOL)
        {
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
            return 0;
        }

        tok=GetToken(soubor);
        PrintToken(tok);
        if (tok->type!=tEOL)
        {
            return 0;
        }
    }
    UngetToken(tok);
    return 1;
}

int E()
{
    return Expr_Analysis();
}

int Else()
{
    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type==END)
    {
        UngetToken(tok);
        return 1;
    }

    if (tok->type!=ELSE)
    {
        return 0;
    }

    tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type!=tEOL)
    {
        return 0;
    }

    int i = Stat();
    if (i==0)
        return 0;

    return 1;
}

int Out()
{
    int i=E();
    if (i==0)
        return 0;

    Write();

    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type==STREDNIK)
    {
        return Out();
    }
    else if (tok->type!=tEOL)
    {
        return 0;
    }
    UngetToken(tok);
    return 1;
}
