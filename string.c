/********* string.c *********
 *
 * FIT VUT, IFJ 119
 * Author: Martin Gajdosik, xgajdo21
 * Summary: Operace s retezci.
 *
 */
#include "string.h"

#define ALLOC_SIZE 100

int InitBuffer(buffer* buff)//Inicializace bufferu pro zteni ze vstupu
{
    buff->allocsize=ALLOC_SIZE;
    buff->lenght=0;
    buff->str =(char*) malloc(ALLOC_SIZE*sizeof(char));
    if (buff->str==NULL)
    {
        return 0;
    }
    return 1;
}

void FreeBuffer(buffer* buff)//Uvolneni bufferu
{
    free(buff->str);
}

int AddChar(buffer* buff,char c)//Prida znak do bufferu
{
    if (buff->lenght+1 == buff->allocsize)
    {
        buff->str=realloc(buff->str,buff->allocsize+ALLOC_SIZE);
        if (buff->str==NULL)
        {
            Error(99);
            return 0;
        }
        buff->allocsize+=ALLOC_SIZE;
    }
    buff->str[buff->lenght]=c;
    buff->lenght++;
    return 1;
}

char *GetStringBuffer(buffer *buff)//Vraci obsah bufferu
{
   return buff->str;
}

int InitParArray(pararray* p)//Inicializuje 2D pole znaku, ktere uchovava identifikatory parametru funkci
{
    p->parcount=0;
    p->allocsize=ALLOC_SIZE;
    p->par=malloc(ALLOC_SIZE*sizeof(char*));
    if (p->par==NULL)
        return 0;
    return 1;
}

int InsertPar(pararray* p,char* id)//Vlozeni noveho identifikatoru parametru funkce
{
    if (p->parcount+1 == p->allocsize)
    {
        char** pom;
        pom=realloc(p->par,p->allocsize+ALLOC_SIZE);
        if (pom==NULL)
        {
            return 0;
        }
        p->par=pom;
    }
    p->par[p->parcount]=(char*) malloc(strlen(id)*sizeof(char));
    strcpy(p->par[p->parcount], id);
    p->par[p->parcount][strlen(id)]='\0';
    p->parcount++;
    return 1;
}

