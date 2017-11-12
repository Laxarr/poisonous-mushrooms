#include "str.h"

int InitBuffer(buffer* buff)
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

void FreeBuffer(buffer* buff)
{
    free(buff->str);
}

int AddChar(buffer* buff,char c)
{
    if (buff->lenght+1 == buff->allocsize)
    {
        char* pom;
        pom=realloc(buff->str,buff->allocsize+ALLOC_SIZE);
        if (pom==NULL)
        {
            return 0;
        }
        buff->str=pom;
    }
    buff->str[buff->lenght]=c;
    buff->lenght++;
    return 1;
}

char *GetStringBuffer(buffer *buff)
{
   return buff->str;
}
