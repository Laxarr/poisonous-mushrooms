#include <stdio.h>
#include <stdlib.h>

#define ALLOC_SIZE 100

typedef struct
{
    char* str;
    int lenght;
    int allocsize;
} buffer;

int InitBuffer(buffer* buff);
void FreeBuffer(buffer* buff);
int AddChar(buffer* buff,char c);
