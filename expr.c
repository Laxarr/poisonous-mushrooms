#include "expr.h"

typedef enum {
    zadek,   // =
// mozna vyuziju pro prirazeni veci, ktere jdou ulozit na zasobnik
 
} ENvycet;
static const char table[Tsize][Tsize] = { //i, j
            // VSTUP
          // $   +   -   *   /   <   >  <>  <=  >=   =   ID INT DBL  (   )
/* $   */ { ' ','<','<','<','<','<','<','<','<','<','<','<','<','<','<',' '}  
/* +   */ { '>','>','>','<','<','>','>','>','>','>','>','<','<','<','<','>'}   
/* -   */ { '>','>','>','<','<','>','>','>','>','>','>','<','<','<','<','>'}
/* *   */ { '>','>','>','>','>','>','>','>','>','>','>','<','<','<','<','>'}
/* /   */ { '>','>','>','>','>','>','>','>','>','>','>','<','<','<','<','>'}
/* <   */ { '>','<','<','<','<','>','>','>','>','>','>','<','<','<','<','>'}
/* >   */ { '>','<','<','<','<','>','>','>','>','>','>','<','<','<','<','>'}
/* <>  */ { '>','<','<','<','<','>','>','>','>','>','>','<','<','<','<','>'}
/* <=  */ { '>','<','<','<','<','>','>','>','>','>','>','<','<','<','<','>'}
/* >=  */ { '>','<','<','<','<','>','>','>','>','>','>','<','<','<','<','>'}
/* =   */ { '>','<','<','<','<','>','>','>','>','>','>','<','<','<','<','>'}
/* ID  */ { '>','>','>','>','>','>','>','>','>','>','>',' ',' ',' ',' ','>'}
/* INT */ { '>','>','>','>','>','>','>','>','>','>','>',' ',' ',' ',' ','>'}
/* DBL */ { '>','>','>','>','>','>','>','>','>','>','>',' ',' ',' ',' ','>'}
/* (   */ { ' ','<','<','<','<','<','<','<','<','<','<','<','<','<','<','='}
/* )   */ { '>','>','>','<','<','>','>','>','>','>','>',' ','>','>','=','>'}
};
int NumberRow (char* c) { //nwm co mam vracet
    int i;

    if      (c == '$') j = 0;
    else if (tok->type == PLUS) j = 1;
    else if (tok->type == MINUS) j = 2;
    else if (tok->type == NASOBENI) j = 3;
    else if (tok->type == DELENI) j = 4;
    else if (tok->type == MENSI) j = 5;
    else if (tok->type == VETSI) j = 6;
    else if (tok->type == MENSI_ROVNO) j = 7;
    else if (tok->type == VETSI_ROVNO) j = 8;
    else if (tok->type == ROVNO) j = 9;
    else if (tok->type == ID) j = 10;
    //nwm
    else if (tok->type == DOLAR) j = 11;
    else if (tok->type == DOLAR) j = 12;
    //nwm
    else if (tok->type == KULATA_ZAV_ZAC) j = 13;
    else if (tok->type == KULATA_ZAV_KON) j = 14;

    return j;
 }


int NumberColumn (token* tok) { // vraci cislo sloupce, kde je vstup
    int j;

    if      (tok->type == DOLAR) j = 0;
    else if (tok->type == PLUS) j = 1;
    else if (tok->type == MINUS) j = 2;
    else if (tok->type == NASOBENI) j = 3;
    else if (tok->type == DELENI) j = 4;
    else if (tok->type == MENSI) j = 5;
    else if (tok->type == VETSI) j = 6;
    else if (tok->type == MENSI_ROVNO) j = 7;
    else if (tok->type == VETSI_ROVNO) j = 8;
    else if (tok->type == ROVNO) j = 9;
    else if (tok->type == ID) j = 10;
    //nwm
    else if (tok->type == DOLAR) j = 11;
    else if (tok->type == DOLAR) j = 12;
    //nwm
    else if (tok->type == KULATA_ZAV_ZAC) j = 13;
    else if (tok->type == KULATA_ZAV_KON) j = 14;

    return j;
 }

char TableSearch (int* i,int* j) { // najde v tabulce znak a vrati ho
    char c = table [i][j];
    return c;
}

int IsSymbol () { // kouka na stack jestli je na zasobniku symbol(terminal)


}

int Expr_Analysis() //nekde tady to budu muset cyklit
{
    stackInit(Tstack);
    // vloz na zasobnik $
    stackPush (Tstack,'$');

     //nacti dalsi token
    token* tok=GetToken(soubor);

    

   
    // vrcholu zasobniku precti znak a prirad mu cislo odpovidajici radku tabulky
    char top_char;
    int i, j;

    char table_char;

    stackTop ( const Tstack,top_char);


    i = NumberRow(top_char);
    j = NumberColumn(token* tok);



    // nacteny token a prirad mu cislo ze sloupce taulky

   


    //najdi s pomoci souradnic znamenko v tabulce < > =
     table_char = TableSearch (i, j);

    // krade pera

    // podle toho se rozhodni

    if (table_char == '=') {
        stackPush (Tstack, top_char); // TADY budu vkladat asi neco jineho

    }

    else if (table_char == '<') {

        if (je terminal posledni znak) {
             stackPush (Tstack, table_char);
        }

        else {
            ENvycet tmp = StackPop (Tstack);
            stackPush (Tstack, table_char);
            stackPush (Tstack, tmp);
        }         

    }

    else if (table_char == '>') {
        // zde budou ty pravidla, moc jim nerozumim
        // a asi to razeni symbolu

    }

    else {
       printf("error pri zpracovani vyrazu\n");    
    }

    
        // kdyz > 
                  //  Najdi na zásobníku nevrchnější <
                  //  Mezi < a vrcholem najdi pravou stranu nějakého pravidla
                  //  Odstraň tuto část zásobníku včetně <
                  //  Nahraď ji levou stranou pravidla
                    //tady fakt nwm, jak  pracovat


        // kdyz < za nejhornejsi symbol zasobniku (nemusi to byt vrchol) dej <

        // kdyz =   dej  vstupni symbol na zasobnik

        // kdyz ' ' tak hod error

    // 



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
