/********* codegenerator.c *********
 *
 * FIT VUT, IFJ 119
 * Author: Martin Gajdosik, xgajdo21
 * Summary: Gererator kodu.
 *
 */
#include "codegenerator.h"
#define STRINGSIZE 10

int ifelsecount=0;
int dowhilecount=0;
int concat=0;

void Program_begin()
{
    fprintf(stdout,".IFJcode17\n");
    fprintf(stdout,"DEFVAR GF@pom\n");
    fprintf(stdout,"JUMP main\n");
}

void Main_fun()
{
    fprintf(stdout,"LABEL main\n");
    fprintf(stdout,"CREATEFRAME\n");
}

void IfCond()
{
    fprintf(stdout,"PUSHS bool@true\n");
    fprintf(stdout,"JUMPIFNEQS ifelse%d\n",ifelsecount);
}

void Iftrueend()
{
    fprintf(stdout,"JUMP ifelseend%d\n",ifelsecount);
}

void IfElse()
{
    fprintf(stdout,"LABEL ifelse%d\n",ifelsecount);
}

void IfEnd()
{
    fprintf(stdout,"LABEL ifelseend%d\n",ifelsecount);
    ifelsecount++;
}

void LoopStart()
{
    fprintf(stdout,"LABEL while%d\n",dowhilecount);
}

void LoopCond()
{
    fprintf(stdout,"PUSHS bool@true\n");
    fprintf(stdout,"JUMPIFNEQS whileend%d\n",dowhilecount);
}

void LoopEnd()
{
    fprintf(stdout,"JUMP while%d\n",dowhilecount);
    fprintf(stdout,"LABEL whileend%d\n",dowhilecount);
    dowhilecount++;
}

void Declare_var(char* id)
{
    fprintf(stdout,"DEFVAR TF@%s\n",id);
    SymTab_Element* pom= sym_tab_find(CurrentST,id);
    if (pom->data_type==SymTab_DataType_Double)
        fprintf(stdout,"MOVE TF@%s float@0.0\n",id);
    else if (pom->data_type==SymTab_DataType_Integer)
        fprintf(stdout,"MOVE TF@%s int@0\n",id);
    else if (pom->data_type==SymTab_DataType_String)
        fprintf(stdout,"MOVE TF@%s string@""\n",id);
}

void Read(token* var)//vyresit znak pro mezernik
{
    printf("WRITE string@?");
    printf("%c",92);
    printf("032\n");
    SymTab_Element* pom=sym_tab_find(CurrentST,var->string_hodnota);
    if (pom->data_type==SymTab_DataType_Double)
        fprintf(stdout,"READ TF@%s float\n",var->string_hodnota);
    else if (pom->data_type==SymTab_DataType_Integer)
        fprintf(stdout,"READ TF@%s int\n",var->string_hodnota);
    else if (pom->data_type==SymTab_DataType_String)
        fprintf(stdout,"READ TF@%s string\n",var->string_hodnota);
}

void Write()
{
    printf("POPS GF@pom\n");
    printf("WRITE GF@pom\n");
}

void PushRetVal(token* tok)
{
    if (tok->type==NUMBER_DOUBLE)
        printf("PUSHS float@%f\n",tok->double_hodnota);
    else if (tok->type==NUMBER_INT)
    {
        printf("PUSHS int@%d\n",tok->int_hodnota);
    }
    else if (tok->type==RETEZEC)
        printf("PUSHS string@%s\n",tok->string_hodnota);
    else
    {
        printf("PUSHS TF@%s\n",tok->string_hodnota);
    }
}

void PushParam(token* tok)
{
    if (tok->type==NUMBER_DOUBLE)
        printf("PUSHS float@%f\n",tok->double_hodnota);
    else if (tok->type==NUMBER_INT)
    {
        printf("PUSHS int@%d\n",tok->int_hodnota);
        printf("INT2FLOATS\n");
    }
    else if (tok->type==RETEZEC)
        printf("PUSHS string@%s\n",tok->string_hodnota);
    else
    {
        printf("PUSHS TF@%s\n",tok->string_hodnota);
        SymTab_Element* pom=sym_tab_find(CurrentST,tok->string_hodnota);
        if (pom->data_type==SymTab_DataType_Integer)
        {
            printf("INT2FLOATS\n");
        }
    }
}

void Call_fun(char* id)
{
    fprintf(stdout,"PUSHFRAME\n");
    fprintf(stdout,"CALL %s\n",id);
    fprintf(stdout,"POPFRAME\n");
}

void Declare_fun(char* id)
{
    fprintf(stdout,"LABEL %s\n",id);
    fprintf(stdout,"CREATEFRAME\n");
    for (int i=0;i<sym_tab_find(GlobalST,id)->paramcount;i++)
    {
        SymTab_Element* fun=sym_tab_find(GlobalST,id);
        fprintf(stdout,"DEFVAR TF@%s\n",fun->pararr->par[i]);
        fprintf(stdout,"POPS TF@%s\n",fun->pararr->par[i]);
    }
}

void Declare_funend()
{
    fprintf(stdout,"RETURN\n");
}

void AssignVal(char* id)
{
    SymTab_Element* pom=sym_tab_find(CurrentST,id);
    if (pom->data_type == SymTab_DataType_Integer)
    {
        fprintf(stdout,"FLOAT2INTS\n");
    }
    fprintf(stdout,"POPS TF@%s\n",id);

}

void Length()
{
    fprintf(stdout,"DEFVAR TF@n\n");
    fprintf(stdout,"POPS TF@n\n");
    fprintf(stdout,"STRLEN TF@n TF@n\n");
    fprintf(stdout,"PUSHS TF@n\n");
}

void SubStr()
{
}

void Asc()
{
    fprintf(stdout,"STRI2INTS\n");
}

void Chr()
{
    fprintf(stdout,"INT2CHARS\n");
}

void CheckOperands(token* operation,token* op1,token* op2)
{
    SymTab_Element* op1pom=NULL;
    SymTab_Element* op2pom=NULL;
    if (op1 != NULL && op2!=NULL)
    {
        if (op1->type==ID)
            op1pom=sym_tab_find(CurrentST,op1->string_hodnota);
        if (op2->type==ID)
            op2pom=sym_tab_find(CurrentST,op2->string_hodnota);

        if (op1pom==NULL)
        {
            if (op1->type==NUMBER_DOUBLE)
                fprintf(stdout,"PUSHS float@%f\n",op1->double_hodnota);
            else if (op1->type==NUMBER_INT)
            {
                fprintf(stdout,"PUSHS int@%d\n",op1->int_hodnota);
                fprintf(stdout,"INT2FLOATS\n");
            }
        }
        else
        {
            if (sym_tab_find(CurrentST,op1pom->id)->data_type==SymTab_DataType_Integer)
            {
                fprintf(stdout,"PUSHS TF@%s\n",op1pom->id);
                fprintf(stdout,"INT2FLOATS\n");
            }
            else
            {
                fprintf(stdout,"PUSHS TF@%s\n",op1pom->id);
            }
        }

        if (op2pom==NULL)
        {
            if (op2->type==NUMBER_DOUBLE)
                fprintf(stdout,"PUSHS float@%f\n",op2->double_hodnota);
            else if (op2->type==NUMBER_INT)
            {
                fprintf(stdout,"PUSHS int@%d\n",op2->int_hodnota);
                fprintf(stdout,"INT2FLOATS\n");
            }
        }
        else
        {
            if (sym_tab_find(CurrentST,op2pom->id)->data_type==SymTab_DataType_Integer)
            {
                fprintf(stdout,"PUSHS TF@%s\n",op2pom->id);
                fprintf(stdout,"INT2FLOATS\n");
            }
            else
            {
                fprintf(stdout,"PUSHS TF@%s\n",op2pom->id);
            }
        }
    }
    else if (op1==NULL && op2==NULL)
    {

    }
    else if (op2==NULL)
    {
        token* tok=op2;
        op2=op1;
        op1=tok;
        printf("POPS GF@pom\n");
        printf("DEFVAR GF@pom1\n");
        printf("POPS GF@pom1\n");
        printf("PUSHS GF@pom\n");
        printf("PUSHS GF@pom1\n");
    }
    else if (op1==NULL)
    {
        if (op2->type==ID)
            op2pom=sym_tab_find(CurrentST,op2->string_hodnota);
        if (op2pom==NULL)
        {
            if (op2->type==NUMBER_DOUBLE)
                fprintf(stdout,"PUSHS float@%f\n",op2->double_hodnota);
            else if (op2->type==NUMBER_INT)
            {
                fprintf(stdout,"PUSHS int@%d\n",op2->int_hodnota);
                fprintf(stdout,"INT2FLOATS\n");
            }
        }
        else
        {
            if (sym_tab_find(CurrentST,op2pom->id)->data_type==SymTab_DataType_Integer)
            {
                fprintf(stdout,"PUSHS TF@%s\n",op2pom->id);
                fprintf(stdout,"INT2FLOATS\n");
            }
            else
            {
                fprintf(stdout,"PUSHS TF@%s\n",op2pom->id);
            }
        }
    }
}

void Operation(token* operation,token* op1,token* op2)
{
    if (operation->type==CELO_CIS_DELENI)
    {
        CheckOperands(operation,op1,op2);
        fprintf(stdout,"DIVS\n");
        fprintf(stdout,"FLOAT2R2EINTS\n");
    }

    else if (operation->type==DELENI)
    {
        CheckOperands(operation,op1,op2);
        fprintf(stdout,"DIVS\n");
    }

    else if (operation->type==PLUS)//pridat konkatenanci retezcu
    {
        SymTab_Element* op1pom=NULL;
        SymTab_Element* op2pom=NULL;
        char* str1=malloc(sizeof(char));
        char* str2=malloc(sizeof(char));
        if (op1 != NULL && op2!=NULL)
        {
            if (op1->type==ID)
                op1pom=sym_tab_find(CurrentST,op1->string_hodnota);
            if (op2->type==ID)
                op2pom=sym_tab_find(CurrentST,op2->string_hodnota);

            if (op1pom==NULL)
            {
                if (op1->type==RETEZEC)
                {
                    fprintf(stdout,"PUSHS string@%s\n",op1->string_hodnota);
                    concat++;
                    str1 = realloc(str1, strlen(op1->string_hodnota));
                    strcat(str1,"string@");
                    strcat(str1,op1->string_hodnota);
                }
            }
            else
            {
                if (sym_tab_find(CurrentST,op1pom->id)->data_type==SymTab_DataType_String)
                {
                    fprintf(stdout,"PUSHS TF@%s\n",op1pom->id);
                    concat++;
                    str1 = realloc(str1, strlen(op1pom->id));
                    strcpy(str1, op1pom->id);
                }
            }

            if (op2pom==NULL)
            {
                if (op2->type==RETEZEC)
                {
                    fprintf(stdout,"PUSHS string@%s\n",op2->string_hodnota);
                    concat++;
                    str2 = realloc(str2, strlen(op2->string_hodnota));
                    strcat(str2,"string@");
                    strcat(str2,op2->string_hodnota);
                }
            }
            else
            {
                if (sym_tab_find(CurrentST,op2pom->id)->data_type==SymTab_DataType_String)
                {
                    fprintf(stdout,"PUSHS TF@%s\n",op2pom->id);
                    concat++;
                    str2 = realloc(str2, strlen(op2pom->id));
                    strcpy(str2, op2pom->id);
                }
            }
        }

        if (concat==2)
        {
            fprintf(stdout,"CONCAT GF@pom %s %s\n",str1,str2);
            fprintf(stdout,"PUSHS GF@pom\n");
        }
        else
        {
            CheckOperands(operation,op1,op2);
            fprintf(stdout,"ADDS\n");
        }
        free(str1);
        free(str2);
    }

    else if (operation->type==MINUS)
    {
        CheckOperands(operation,op1,op2);
        printf("SUBS\n");
    }

    else if (operation->type==NASOBENI)
    {
        CheckOperands(operation,op1,op2);
        printf("MULS\n");
    }

    else if (operation->type==MENSI)
    {
        CheckOperands(operation,op1,op2);
        printf("LTS\n");
    }

    else if (operation->type==VETSI)
    {
        CheckOperands(operation,op1,op2);
        printf("GTS\n");
    }

    else if (operation->type==VETSI_ROVNO)
    {
        CheckOperands(operation,op1,op2);
        printf("GTS\n");

        CheckOperands(operation,op1,op2);
        printf("EQS\n");

        printf("ORS\n");
    }

    else if (operation->type==MENSI_ROVNO)
    {
        CheckOperands(operation,op1,op2);
        printf("LTS\n");

        CheckOperands(operation,op1,op2);
        printf("EQS\n");

        printf("ORS\n");
    }

    else if (operation->type==NEROVNOST)
    {
        CheckOperands(operation,op1,op2);
        printf("EQS\n");

        printf("NOTS\n");
    }

    else if (operation->type==ROVNOST)
    {
        CheckOperands(operation,op1,op2);
        printf("EQS\n");
    }
}
