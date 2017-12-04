/********* codegenerator.c *********
 *
 * FIT VUT, IFJ 119
 * Author: Martin Gajdosik, xgajdo21
 * Summary: Gererator kodu.
 *
 */
#include "codegenerator.h"

int ifelsecount=0;
int dowhilecount=0;
int concat=0;
int tempvarcount=0;
int cycle=0;
SymTab_Element* op1pom=NULL;
SymTab_Element* op2pom=NULL;

void Program_begin()
{
    printf(".IFJcode17\n");
    printf("DEFVAR GF@pom\n");
    printf("JUMP main\n");
}

void Main_fun()
{
    printf("LABEL main\n");
    printf("CREATEFRAME\n");
}

void IfCond()
{
    printf("PUSHS bool@true\n");
    printf("JUMPIFNEQS ifelse%d\n",ifelsecount);
}

void Iftrueend()
{
    printf("JUMP ifelseend%d\n",ifelsecount);
}

void IfElse()
{
    printf("LABEL ifelse%d\n",ifelsecount);
}

void IfEnd()
{
    printf("LABEL ifelseend%d\n",ifelsecount);
    ifelsecount++;
}

void LoopStart()
{
    cycle=1;
    for (int i=0;i<10;i++)
    {
        printf("DEFVAR TF@tempvar%d\n",tempvarcount+i);
    }
    printf("LABEL while%d\n",dowhilecount);
}

void LoopCond()
{
    printf("PUSHS bool@true\n");
    printf("JUMPIFNEQS whileend%d\n",dowhilecount);
}

void LoopEnd()
{
    printf("JUMP while%d\n",dowhilecount);
    printf("LABEL whileend%d\n",dowhilecount);
    dowhilecount++;
    cycle=0;
}

void Declare_var(char* id)
{
    printf("DEFVAR TF@%s\n",id);
    SymTab_Element* pom= sym_tab_find(CurrentST,id);
    if (pom->data_type==SymTab_DataType_Double)
        printf("MOVE TF@%s float@0.0\n",id);
    else if (pom->data_type==SymTab_DataType_Integer)
        printf("MOVE TF@%s int@0\n",id);
    else if (pom->data_type==SymTab_DataType_String)
        printf("MOVE TF@%s string@""\n",id);
}

void Read(token* var)//vyresit znak pro mezernik
{
    printf("WRITE string@?");
    printf("%c",92);
    printf("032\n");
    SymTab_Element* pom=sym_tab_find(CurrentST,var->string_hodnota);
    if (pom->data_type==SymTab_DataType_Double)
        printf("READ TF@%s float\n",var->string_hodnota);
    else if (pom->data_type==SymTab_DataType_Integer)
        printf("READ TF@%s int\n",var->string_hodnota);
    else if (pom->data_type==SymTab_DataType_String)
        printf("READ TF@%s string\n",var->string_hodnota);
    if (pom->data_type==SymTab_DataType_Integer)
    {
        printf("INT2FLOAT TF@%s TF@%s\n",var->string_hodnota,var->string_hodnota);
    }
}

void ConvertToInt()
{
    printf("FLOAT2INTS\n");
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
    printf("PUSHFRAME\n");
    printf("CALL %s\n",id);
    printf("POPFRAME\n");
}

void Declare_fun(char* id)
{
    printf("LABEL %s\n",id);
    printf("CREATEFRAME\n");
    for (int i=0;i<sym_tab_find(GlobalST,id)->paramcount;i++)
    {
        SymTab_Element* fun=sym_tab_find(GlobalST,id);
        printf("DEFVAR TF@%s\n",fun->pararr->par[i]);
        printf("POPS TF@%s\n",fun->pararr->par[i]);
    }
}

void Declare_funend()
{
    printf("RETURN\n");
}

void AssignVal(char* id)
{
    printf("POPS TF@%s\n",id);
}

void Length()
{
    printf("DEFVAR TF@n\n");
    printf("POPS TF@n\n");
    printf("STRLEN TF@n TF@n\n");
    printf("PUSHS TF@n\n");
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

char* GetOperator(token* operation)
{
    if (operation->type==PLUS)
        return "ADD";
    else if (operation->type==MINUS)
        return "SUB";
    else if (operation->type==DELENI)
        return "DIV";
    else if (operation->type==CELO_CIS_DELENI)
        return "DIV";
    else if (operation->type==NASOBENI)
        return "MUL";
    else if (operation->type==VETSI)
        return "GT";
    else if (operation->type==MENSI)
        return "LT";
    else
        return "EQ";
}

void CheckOperands(token* operation,token* op1,token* op2)
{
        if (op1->type==ID)
            op1pom=sym_tab_find(CurrentST,op1->string_hodnota);
        if (op2->type==ID)
            op2pom=sym_tab_find(CurrentST,op2->string_hodnota);

        concat=0;
        if (op1pom!=NULL)
        {
            if (sym_tab_find(CurrentST,op1pom->id)->data_type==SymTab_DataType_String)
                concat++;
        }
        if (op2pom!=NULL)
        {
            if (sym_tab_find(CurrentST,op2pom->id)->data_type==SymTab_DataType_String)
                concat++;
        }
        if (op1->type==RETEZEC) concat++;
        if (op2->type==RETEZEC) concat++;

        if (concat==2)
        {
            if (operation->type!=PLUS)
            {
                Error(4);
            }
            concat=0;
            if (op1pom==NULL && op2pom==NULL)
                printf("CONCAT TF@tempvar%d string@%s string@%s\n",tempvarcount,op1->string_hodnota,op2->string_hodnota);
            else if (op1pom==NULL && op2pom!=NULL)
                printf("CONCAT TF@tempvar%d string@%s TF@%s\n",tempvarcount,op1->string_hodnota,op2pom->id);
            else if (op1pom!=NULL && op2pom!=NULL)
                printf("CONCAT TF@tempvar%d TF@%s TF@%s\n",tempvarcount,op1pom->id,op2pom->id);
            else if (op1pom!=NULL && op2pom==NULL)
                printf("CONCAT TF@tempvar%d TF@%s string@%s\n",tempvarcount,op1pom->id,op2->string_hodnota);

            return;

        }
        else if (concat!=0)
        {
            Error(4);
        }

        char* op=GetOperator(operation);

        if (op1->type==NUMBER_INT)
        {
            op1->double_hodnota=op1->int_hodnota;
        }
        if (op2->type==NUMBER_INT)
        {
            op2->double_hodnota=op2->int_hodnota;
        }

        if (op1->type==TEMP && op2->type==TEMP)
            printf("%s TF@tempvar%d TF@tempvar%d TF@tempvar%d\n",op,tempvarcount,op1->int_hodnota,op2->int_hodnota);
        else if (op1->type==TEMP && op2pom==NULL)
            printf("%s TF@tempvar%d TF@tempvar%d float@%g\n",op,tempvarcount,op1->int_hodnota,op2->double_hodnota);
        else if (op1->type==TEMP && op2pom!=NULL)
            printf("%s TF@tempvar%d TF@tempvar%d TF@%s\n",op,tempvarcount,op1->int_hodnota,op2pom->id);
        else if (op1pom==NULL && op2->type==TEMP)
            printf("%s TF@tempvar%d float@%g TF@tempvar%d\n",op,tempvarcount,op1->double_hodnota,op2->int_hodnota);
        else if (op1pom!=NULL && op2->type==TEMP)
            printf("%s TF@tempvar%d TF@%s TF@tempvar%d\n",op,tempvarcount,op1pom->id,op2->int_hodnota);
        else if (op1pom==NULL && op2pom==NULL)
            printf("%s TF@tempvar%d float@%g float@%g\n",op,tempvarcount,op1->double_hodnota,op2->double_hodnota);
        else if (op1pom==NULL && op2pom!=NULL)
            printf("%s TF@tempvar%d float@%g TF@%s\n",op,tempvarcount,op1->double_hodnota,op2pom->id);
        else if (op1pom!=NULL && op2pom!=NULL)
            printf("%s TF@tempvar%d TF@%s TF@%s\n",op,tempvarcount,op1pom->id,op2pom->id);
        else if (op1pom!=NULL && op2pom==NULL)
            printf("%s TF@tempvar%d TF@%s float@%g\n",op,tempvarcount,op1pom->id,op2->double_hodnota);

        if (op1->type==NUMBER_INT)
        {
            op1->int_hodnota=op1->double_hodnota;
        }
        if (op2->type==NUMBER_INT)
        {
            op2->int_hodnota=op2->double_hodnota;
        }
}


token* Operation(token* operation,token* op1,token* op2)
{
    token* tok = (token*) malloc(sizeof(token));

    if (operation->type==CELO_CIS_DELENI)
    {
        if (cycle!=1)
        printf("DEFVAR TF@tempvar%d\n",tempvarcount);
        CheckOperands(operation,op1,op2);



        printf("FLOAT2INT TF@tempvar%d TF@tempvar%d\n",tempvarcount,tempvarcount);
        printf("INT2FLOAT TF@tempvar%d TF@tempvar%d\n",tempvarcount,tempvarcount);
        tok->type=TEMP;
        tok->int_hodnota=tempvarcount;
        tempvarcount++;
        return tok;
    }

    else if (operation->type==DELENI)
    {
        if (cycle!=1)
        printf("DEFVAR TF@tempvar%d\n",tempvarcount);
        CheckOperands(operation,op1,op2);

        tok->type=TEMP;
        tok->int_hodnota=tempvarcount;
        tempvarcount++;
        return tok;
    }

    else if (operation->type==PLUS)
    {
        if (cycle!=1)
        printf("DEFVAR TF@tempvar%d\n",tempvarcount);
        CheckOperands(operation,op1,op2);

        tok->type=TEMP;
        tok->int_hodnota=tempvarcount;
        tempvarcount++;
        return tok;
    }
    else if (operation->type==MINUS)
    {
        if (cycle!=1)
        printf("DEFVAR TF@tempvar%d\n",tempvarcount);
        CheckOperands(operation,op1,op2);

        tok->type=TEMP;
        tok->int_hodnota=tempvarcount;
        tempvarcount++;
        return tok;
    }

    else if (operation->type==NASOBENI)
    {
        if (cycle!=1)
        printf("DEFVAR TF@tempvar%d\n",tempvarcount);
        CheckOperands(operation,op1,op2);

        tok->type=TEMP;
        tok->int_hodnota=tempvarcount;
        tempvarcount++;
        return tok;
    }

    else if (operation->type==MENSI)
    {
        if (cycle!=1)
        printf("DEFVAR TF@tempvar%d\n",tempvarcount);
        CheckOperands(operation,op1,op2);

        tok->type=TEMP;
        tok->int_hodnota=tempvarcount;
        tempvarcount++;
        return tok;
    }

    else if (operation->type==VETSI)
    {
        if (cycle!=1)
        printf("DEFVAR TF@tempvar%d\n",tempvarcount);
        CheckOperands(operation,op1,op2);

        tok->type=TEMP;
        tok->int_hodnota=tempvarcount;
        tempvarcount++;
        return tok;
    }

    else if (operation->type==ROVNOST)
    {
        if (cycle!=1)
        printf("DEFVAR TF@tempvar%d\n",tempvarcount);
        CheckOperands(operation,op1,op2);

        tok->type=TEMP;
        tok->int_hodnota=tempvarcount;
        tempvarcount++;
        return tok;
    }

    else if (operation->type==VETSI_ROVNO)
    {
        tok->type=VETSI;
        token* tok1=Operation(tok,op1,op2);
        tok->type=ROVNOST;
        token* tok2=Operation(tok,op1,op2);

        if (cycle!=1)
        printf("DEFVAR TF@tempvar%d\n",tempvarcount);
        printf("OR TF@tempvar%d TF@tempvar%d TF@tempvar%d\n",tempvarcount,tok1->int_hodnota,tok2->int_hodnota);

        tok->type=TEMP;
        tok->int_hodnota=tempvarcount;
        tempvarcount++;
        return tok;
    }

    else if (operation->type==MENSI_ROVNO)
    {
        tok->type=MENSI;
        token* tok1=Operation(tok,op1,op2);

        tok->type=ROVNOST;
        token* tok2=Operation(tok,op1,op2);

        if (cycle!=1)
        printf("DEFVAR TF@tempvar%d\n",tempvarcount);
        printf("OR TF@tempvar%d TF@tempvar%d TF@tempvar%d\n",tempvarcount,tok1->int_hodnota,tok2->int_hodnota);

        tok->type=TEMP;
        tok->int_hodnota=tempvarcount;
        tempvarcount++;
        return tok;
    }

    else if (operation->type==NEROVNOST)
    {
        tok->type=ROVNOST;
        token* tok1=Operation(tok,op1,op2);

        if (cycle!=1)
        printf("DEFVAR TF@tempvar%d\n",tempvarcount);
        printf("NOT TF@tempvar%d TF@tempvar%d\n",tempvarcount,tok1->int_hodnota);

        tok->type=TEMP;
        tok->int_hodnota=tempvarcount;
        tempvarcount++;
        return tok;
    }
    return NULL;
}
