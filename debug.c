#include "debug.h"

void PrintToken(token* tok)
{
    if (tok==NULL)
    {
        return;
    }
    if (tok->type==NUMBER_INT)
    {
        printf("%d debug\n",tok->int_hodnota);
    }
    else if (tok->type==NUMBER_DOUBLE)
    {
        printf("%f debug\n",tok->double_hodnota);
    }
    else
    {
        printf("%s debug\n",tok->string_hodnota);
    }
}
