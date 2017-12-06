/********* string.h *********
 *
 * FIT VUT, IFJ 119
 * Author: Martin Gajdosik, xgajdo21
 * Summary: Operace s retezci.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef STRINGFILE
#define STRINGFILE
#include "error.h"

typedef struct
{
    char* str;
    int lenght;
    int allocsize;
} buffer;

typedef struct
{
    char** par;
    int parcount;
    int allocsize;
} pararray;

int InitBuffer(buffer* buff);
void FreeBuffer(buffer* buff);
int AddChar(buffer* buff,char c);
char *GetStringBuffer(buffer *buff);

int InitParArray(pararray* p);
int InsertPar(pararray* p,char* id);
#endif
