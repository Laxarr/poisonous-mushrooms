#include <stdio.h>
#include <stdlib.h>

#ifndef STRING
#define STRING

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
