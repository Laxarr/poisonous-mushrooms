#include "expr.h"
int Expr_Analysis()
{
    token* tok=GetToken(soubor);
    PrintToken(tok);
    if (tok->type==ID)//volani funkce
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
        else
        {
          //tady muzes zacit psat











        }
    }
    return 1;
}
