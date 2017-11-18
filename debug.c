#include "debug.h"

void PrintToken(token* tok)
{
    if (tok==NULL)
    {
        return;
    }
    if (tok->type==NUMBER_INT)
    {
        printf("%d ",tok->int_hodnota);
    }
    else if (tok->type==NUMBER_DOUBLE)
    {
        printf("%f ",tok->double_hodnota);
    }
    else if (tok->type==RETEZEC || tok->type==ID)
    {
        printf("%s ",tok->string_hodnota);
    }
    else if (tok->type==tEOF)
    {
        printf("EOF\n");
    }
    else if (tok->type==tEOL)
    {
        printf("EOL\n");
    }
    else if (tok->type==THEN)
    {
        printf("THEN ");
    }
    else if (tok->type==RETURN)
    {
        printf("RETURN ");
    }
    else if (tok->type==FUNCTION)
    {
        printf("FUNCTION ");
    }
    else if (tok->type==ELSE)
    {
        printf("ELSE ");
    }
    else if (tok->type==DO)
    {
        printf("DO ");
    }
    else if (tok->type==AS)
    {
        printf("AS ");
    }
    else if (tok->type==ASC)
    {
        printf("ASC ");
    }
    else if (tok->type==INTEGER)
    {
        printf("INTEGER ");
    }
    else if (tok->type==WHILE)
    {
        printf("WHILE ");
    }
    else if (tok->type==SCOPE)
    {
        printf("SCOPE ");
    }
    else if (tok->type==PRINT)
    {
        printf("PRINT ");
    }
    else if (tok->type==LOOP)
    {
        printf("LOOP ");
    }
    else if (tok->type==INPUT)
    {
        printf("INPUT ");
    }
    else if (tok->type==IF)
    {
        printf("IF ");
    }
    else if (tok->type==END)
    {
        printf("END ");
    }
    else if (tok->type==DIM)
    {
        printf("DIM ");
    }
    else if (tok->type==DECLARE)
    {
        printf("DECLARE ");
    }
    else if (tok->type==ROVNOST)
    {
        printf("= ");
    }
    else if (tok->type==NEROVNOST)
    {
        printf("<> ");
    }
    else if (tok->type==MENSI_ROVNO)
    {
        printf("<= ");
    }
    else if (tok->type==VETSI_ROVNO)
    {
        printf(">= ");
    }
    else if (tok->type==VETSI)
    {
        printf("> ");
    }
    else if (tok->type==MENSI)
    {
        printf("< ");
    }
    else if (tok->type==DELENI)
    {
        printf("/ ");
    }
    else if (tok->type==NASOBENI)
    {
        printf("* ");
    }
    else if (tok->type==MINUS)
    {
        printf("- ");
    }
    else if (tok->type==PLUS)
    {
        printf("+ ");
    }
    else if (tok->type==KULATA_ZAV_KON)
    {
        printf(") ");
    }
    else if (tok->type==KULATA_ZAV_ZAC)
    {
        printf("( ");
    }
    else if (tok->type==STREDNIK)
    {
        printf("; ");
    }
    else if (tok->type==LENGTH)
    {
        printf("LENGTH ");
    }
    else if (tok->type==DOUBLE)
    {
        printf("DOUBLE ");
    }
    else if (tok->type==CHR)
    {
        printf("CHR ");
    }
    else if (tok->type==LOOP)
    {
        printf("LOOP ");
    }
    else if (tok->type==STRING)
    {
        printf("STRING ");
    }
    else if (tok->type==SUBSTR)
    {
        printf("SUBSTR ");
    }
    else if (tok->type==CARKA)
    {
        printf(", ");
    }
}
