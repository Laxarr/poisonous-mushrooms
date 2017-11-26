#include "string.h"

#define ALLOC_SIZE 100

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
            free(pom);
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

int InitParArray(pararray* p)
{
    p->parcount=0;
    p->allocsize=ALLOC_SIZE;
    p->par=malloc(ALLOC_SIZE*sizeof(char*));
    if (p->par==NULL)
        return 0;
    return 1;
}

int InsertPar(pararray* p,char* id)
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
    return 1;
}

void rand_str(char* dest, int length)
{
    char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i=0;
    time_t t;
    srand(time(&t));
    while (length-- > 0) {
        int index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        dest[i] = charset[index];
        i++;
    }
    dest[i] = '\0';
}
