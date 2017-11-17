#include <stdio.h>
#include <stdlib.h>

#ifndef STRINGFILE
#define STRINGFILE

typedef struct
{
    char* str;
    int lenght;
    int allocsize;
} buffer;

int InitBuffer(buffer* buff);
void FreeBuffer(buffer* buff);
int AddChar(buffer* buff,char c);
char *GetStringBuffer(buffer *buff);

#endif
