#include "codegenerator.h"
#define STRINGSIZE 10

int ifelsecount=0;
int dowhilecount=0;

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
    fprintf(stdout,"JUMPIFEQS ifelse%d\n",ifelsecount);
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
    fprintf(stdout,"JUMPIFEQS whileend%d\n",dowhilecount);
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

void Read(token* var)
{
    fprintf(stdout,"WRITE string@? \n");
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
    fprintf(stdout,"POPS GF@pom\n");
    fprintf(stdout,"WRITE GF@pom\n");
}

void PushParam(token* tok)
{
    if (tok->type==NUMBER_DOUBLE)
        fprintf(stdout,"PUSHS float@%f\n",tok->double_hodnota);
    else if (tok->type==NUMBER_INT)
        fprintf(stdout,"PUSHS int@%d\n",tok->int_hodnota);
    else if (tok->type==RETEZEC)
        fprintf(stdout,"PUSHS string@%s\n",tok->string_hodnota);
    else
        fprintf(stdout,"PUSHS TF@%s\n",tok->string_hodnota);
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
            else if (op1->type==RETEZEC)
            {

            }
        }
        else
        {
            if (sym_tab_find(CurrentST,op1pom->id)->data_type==SymTab_DataType_String)
            {

            }
            else if (sym_tab_find(CurrentST,op1pom->id)->data_type==SymTab_DataType_Integer)
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
            else if (op2->type==RETEZEC)
            {

            }
        }
        else
        {
            if (sym_tab_find(CurrentST,op2pom->id)->data_type==SymTab_DataType_String)
            {

            }
            else if (sym_tab_find(CurrentST,op2pom->id)->data_type==SymTab_DataType_Integer)
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
    if (op1==NULL && op2==NULL)
    {

    }
    else if (op1==NULL)
    {
        if (op2pom==NULL)
        {
            if (op2->type==NUMBER_DOUBLE)
                fprintf(stdout,"PUSHS float@%f\n",op2->double_hodnota);
            else if (op2->type==NUMBER_INT)
            {
                fprintf(stdout,"PUSHS int@%d\n",op2->int_hodnota);
                fprintf(stdout,"INT2FLOATS\n");
            }
            else if (op2->type==RETEZEC)
            {

            }
        }
        else
        {
            if (sym_tab_find(CurrentST,op2pom->id)->data_type==SymTab_DataType_String)
            {

            }
            else if (sym_tab_find(CurrentST,op2pom->id)->data_type==SymTab_DataType_Integer)
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
        CheckOperands(operation,op1,op2);
        fprintf(stdout,"ADDS\n");
    }

    else if (operation->type==MINUS)
    {
        CheckOperands(operation,op1,op2);
        fprintf(stdout,"SUBS\n");
    }

    else if (operation->type==NASOBENI)
    {
        CheckOperands(operation,op1,op2);
        fprintf(stdout,"MULS\n");
    }

    else if (operation->type==MENSI)
    {
        CheckOperands(operation,op1,op2);
        fprintf(stdout,"LTS\n");
    }

    else if (operation->type==VETSI)
    {
        CheckOperands(operation,op1,op2);
        fprintf(stdout,"GTS\n");
    }

    else if (operation->type==VETSI_ROVNO)
    {
        CheckOperands(operation,op1,op2);
        fprintf(stdout,"GTS\n");

        CheckOperands(operation,op1,op2);
        fprintf(stdout,"EQS\n");

        fprintf(stdout,"ORS\n");
    }

    else if (operation->type==MENSI_ROVNO)
    {
        CheckOperands(operation,op1,op2);
        fprintf(stdout,"LTS\n");

        CheckOperands(operation,op1,op2);
        fprintf(stdout,"EQS\n");

        fprintf(stdout,"ORS\n");
    }

    else if (operation->type==NEROVNOST)
    {
        CheckOperands(operation,op1,op2);
        fprintf(stdout,"EQS\n");

        fprintf(stdout,"NOTS\n");
    }

    else if (operation->type==ROVNOST)
    {
        CheckOperands(operation,op1,op2);
        fprintf(stdout,"EQS\n");
    }
}
