#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef STRINGFILE
#define STRINGFILE

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

void rand_str(char*dest, int length);
#endif
