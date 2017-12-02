/********* error.c *********
 *
 * FIT VUT, IFJ 119
 * Author: Ondrej Brekl, xbrekl00
 * Summary: Zpracovani chybovych stavu.
 *
 */
#include "error.h"

void Error(int errcode)
{
    switch (errcode)
    {
        case 1:
            fprintf(stderr,"Chyba lexikální analýzy.");
            exit(1);
            break;
        case 2:
            fprintf(stderr,"Chyba syntaktické analýzy.");
            exit(2);
            break;
        case 3:
            fprintf(stderr,"Sémantická chyba v programu – nedefinovaná funkce/proměnná nebo pokus o redefinici funkce/proměnné");
            exit(3);
            break;
        case 4:
            fprintf(stderr,"Sémantická chyba typové kompatibility výrazů nebo špatné volání funkce.");
            exit(4);
            break;
        case 6:
            fprintf(stderr,"Jiná sémantická chyba.");
            exit(6);
            break;
        case 99:
            fprintf(stderr,"Vnitřní chyba překladače.");
            exit(99);
            break;
        default:
            break;
    }

}
