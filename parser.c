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
	static FILE *soubor;

	char *nazev = argv[1];
	soubor = fopen(nazev,"rt");
		if (soubor == NULL) {
		    fprintf(stderr, "soubor nelze otevrit!\n");
		    exit(1);
		}

    Parse();

	fclose (soubor);
	return 1;
}

int Parse()
{
    return Program();
}

int Program()
{
    token* tok=GetToken(soubor);
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

int Main()
{
    token* tok=GetToken(soubor);
    if (tok->type==KEYWORD)
    {
        if (strcmp(tok->string_hodnota,"scope")!=0)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    int i=Stat();
    if (i==0)
        return 0;

    tok=GetToken(soubor);
    if (tok->type==KEYWORD)
    {
        if (strcmp(tok->string_hodnota,"end")!=0)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (tok->type==KEYWORD)
    {
        if (strcmp(tok->string_hodnota,"scope")!=0)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
    return 1;
}

int FunDec()
{
    token* tok=GetToken(soubor);
    if (tok->type==KEYWORD)
    {
        if (strcmp(tok->string_hodnota,"declare")!=0)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (tok->type==KEYWORD)
    {
        if (strcmp(tok->string_hodnota,"function")!=0)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (tok->type!=ID)
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (tok->type!=LEVA_ZAV)
    {
        return 0;
    }

    int i=FunPars();
    if (i==0)
        return 0;

    tok=GetToken(soubor);
    if (tok->type!=PRAVA_ZAV)
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (tok->type==KEYWORD)
    {
        if (strcmp(tok->string_hodnota,"as")!=0)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (!(tok->type==RETEZEC || tok->type==NUMBER_DOUBLE || tok->type==NUMBER_INT))
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (tok->type!=tEOL)
    {
        return 0;
    }

    return 1;
}

int FunDef()
{
    token* tok=GetToken(soubor);
    if (tok->type==KEYWORD)
    {
        if (strcmp(tok->string_hodnota,"function")!=0)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (tok->type!=ID)
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (tok->type!=LEVA_ZAV)
    {
        return 0;
    }

    int i=FunPars();
    if (i==0)
        return 0;

    tok=GetToken(soubor);
    if (tok->type!=PRAVA_ZAV)
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (tok->type==KEYWORD)
    {
        if (strcmp(tok->string_hodnota,"as")!=0)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (!(tok->type==RETEZEC || tok->type==NUMBER_DOUBLE || tok->type==NUMBER_INT))
    {
        return 0;
    }

    i=Stat();
    if (i==0)
        return 0;

    tok=GetToken(soubor);
    if (tok->type!=tEOL)
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (tok->type==KEYWORD)
    {
        if (strcmp(tok->string_hodnota,"end")!=0)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (tok->type==KEYWORD)
    {
        if (strcmp(tok->string_hodnota,"function")!=0)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (tok->type!=tEOL)
    {
        return 0;
    }

    return 1;
}

int FunPars()
{
    token* tok=GetToken(soubor);
    if (tok->type==ID)
    {
        UngetToken(tok);
        return (Par() && ParNext());
    }
    else if (tok->type==PRAVA_ZAV)
    {
        UngetToken(tok);
        return 1;
    }
    return 0;
}

int Fun()
{
    //ukoncit deklarace a definice
    int fdec=0;
    int fdef=0;
    token* tok=GetToken(soubor);
    if (tok->type==KEYWORD)
    {
        if (strcmp(tok->string_hodnota,"declare")==0)
        {
            UngetToken(tok);
            fdec=FunDec();
        }
    }

    tok=GetToken(soubor);
    if (tok->type==KEYWORD)
    {
        if (strcmp(tok->string_hodnota,"function")==0)
        {
            UngetToken(tok);
            fdef= FunDef();
        }
    }
    return (Fun() && fdef && fdec);

}

int Par()
{
    token* tok=GetToken(soubor);
    if (tok->type!=ID)
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (tok->type==KEYWORD)
    {
        if (strcmp(tok->string_hodnota,"as")!=0)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (!(tok->type==RETEZEC || tok->type==NUMBER_DOUBLE || tok->type==NUMBER_INT))
    {
        return 0;
    }

    tok=GetToken(soubor);
    if (tok->type!=tEOL)
    {
        return 0;
    }
    return 1;
}

int ParNext()
{
    token* tok=GetToken(soubor);
    if (tok->type!=CARKA)
    {
        return 0;
    }

    int i=Par();
    if (i==0)
        return 0;

    tok=GetToken(soubor);
    if (tok->type==CARKA)
    {
        UngetToken(tok);
        return ParNext();
    }

    tok=GetToken(soubor);
    if (tok->type==PRAVA_ZAV)
    {
        UngetToken(tok);
        return 1;
    }
    return 0;
}

int Stat()
{
    return 0;
}

int S()
{
    return 0;
}

int I()
{
    return 0;
}

int E()
{
    return 0;
}

int Else()
{
    token* tok=GetToken(soubor);
    if (tok->type==KEYWORD)
    {
        if (strcmp(tok->string_hodnota,"end")==0)
        {
            UngetToken(tok);
            return 1;
        }
    }

    tok=GetToken(soubor);
    if (tok->type==KEYWORD)
    {
        if (strcmp(tok->string_hodnota,"else")!=0)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }

    tok=GetToken(soubor);
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
    return 0;
}
