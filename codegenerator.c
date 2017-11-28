#include "codegenerator.h"
#define STRINGSIZE 10

int tempvarcount=0;
int ifelsecount=0;
int dowhilecount=0;

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

void IfElse()
{
    printf("LABEL ifelse%d\n",ifelsecount);
}

void IfEnd()
{
    ifelsecount++;
}

void LoopStart()
{
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
}

void Declare_var(char* id)
{
    printf("DEFVAR TF@%s\n",id);
}

void Read(token* var)
{
    printf("? \n");
    if (var->type==DOUBLE)
        printf("READ TF@%s float\n",var->string_hodnota);
    else if (var->type==INTEGER)
        printf("READ TF@%s int\n",var->string_hodnota);
    else if (var->type==STRING)
        printf("READ TF@%s string\n",var->string_hodnota);
}

void Write()
{
    printf("POPS GF@pom\n");
    printf("WRITE GF@pom\n");
}

void PushParam(token* tok)
{
    if (tok->type==NUMBER_DOUBLE)
        printf("PUSHS float@%f\n",tok->double_hodnota);
    else if (tok->type==NUMBER_INT)
        printf("PUSHS int@%d\n",tok->int_hodnota);
    else
        printf("PUSHS string@%s\n",tok->string_hodnota);
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
    printf("POPS TF@%s",id);
}

void Operation(token* operation,token* op1,token* op2)
{
    SymTab_Element* op1pom=NULL;
    SymTab_Element* op2pom=NULL;
    if (op1->type==ID)
    {
        op1pom=sym_tab_find(CurrentST,op1->string_hodnota);
    }
    if (op2->type==ID)
    {
        op2pom=sym_tab_find(CurrentST,op2->string_hodnota);
    }

    if (operation->type==CELO_CIS_DELENI)
    {
        if (op1pom==NULL)
        {
            printf("PUSHS int@%d\n",op1->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op1pom->id);
        }
        if (op2pom==NULL)
        {
            printf("PUSHS int@%d\n",op2->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op2pom->id);
        }
        printf("DIVS\n");
        char pom[STRINGSIZE+tempvarcount];
        rand_str(pom,STRINGSIZE+tempvarcount);
        tempvarcount++;
        printf("DEFVAR TF@%s\n",pom);
        printf("POPS TF@%s\n",pom);
        printf("FLOAT2R2EINT %s %s\n",pom,pom);
        printf("PUSHS %s\n",pom);
    }

    else if (operation->type==DELENI)
    {
        if (op1pom==NULL)
        {
            printf("PUSHS double@%f\n",op1->double_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op1pom->id);
        }
        if (op2pom==NULL)
        {
            printf("PUSHS double@%f\n",op2->double_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op2pom->id);
        }
        printf("DIVS\n");
    }

    else if (operation->type==PLUS)//pridat konkatenanci retezcu
    {
        if (op1pom==NULL)
        {
            if (op1->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op1->double_hodnota);
            else if (op1->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op1->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op1pom->id);
        }
        if (op2pom==NULL)
        {
            if (op2->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op2->double_hodnota);
            else if (op2->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op2->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op2pom->id);
        }
        printf("ADDS\n");
    }

    else if (operation->type==MINUS)
    {
        if (op1pom==NULL)
        {
            if (op1->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op1->double_hodnota);
            else if (op1->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op1->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op1pom->id);
        }
        if (op2pom==NULL)
        {
            if (op2->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op2->double_hodnota);
            else if (op2->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op2->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op2pom->id);
        }
        printf("SUBS\n");
    }

    else if (operation->type==NASOBENI)
    {
        if (op1pom==NULL)
        {
            if (op1->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op1->double_hodnota);
            else if (op1->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op1->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op1pom->id);
        }
        if (op2pom==NULL)
        {
            if (op2->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op2->double_hodnota);
            else if (op2->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op2->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op2pom->id);
        }
        printf("MULS\n");
    }

    else if (operation->type==MENSI)
    {
        if (op1pom==NULL)
        {
            if (op1->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op1->double_hodnota);
            else if (op1->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op1->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op1pom->id);
        }
        if (op2pom==NULL)
        {
            if (op2->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op2->double_hodnota);
            else if (op2->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op2->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op2pom->id);
        }
        printf("LTS\n");
    }

    else if (operation->type==VETSI)
    {
        if (op1pom==NULL)
        {
            if (op1->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op1->double_hodnota);
            else if (op1->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op1->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op1pom->id);
        }
        if (op2pom==NULL)
        {
            if (op2->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op2->double_hodnota);
            else if (op2->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op2->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op2pom->id);
        }
        printf("GTS\n");
    }

    else if (operation->type==VETSI_ROVNO)
    {
        if (op1pom==NULL)
        {
            if (op1->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op1->double_hodnota);
            else if (op1->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op1->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op1pom->id);
        }
        if (op2pom==NULL)
        {
            if (op2->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op2->double_hodnota);
            else if (op2->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op2->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op2pom->id);
        }
        printf("GTS\n");

        if (op1pom==NULL)
        {
            if (op1->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op1->double_hodnota);
            else if (op1->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op1->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op1pom->id);
        }
        if (op2pom==NULL)
        {
            if (op2->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op2->double_hodnota);
            else if (op2->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op2->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op2pom->id);
        }
        printf("EQS\n");

        printf("ORS\n");
    }

    else if (operation->type==MENSI_ROVNO)
    {
        if (op1pom==NULL)
        {
            if (op1->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op1->double_hodnota);
            else if (op1->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op1->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op1pom->id);
        }
        if (op2pom==NULL)
        {
            if (op2->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op2->double_hodnota);
            else if (op2->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op2->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op2pom->id);
        }
        printf("LTS\n");

        if (op1pom==NULL)
        {
            if (op1->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op1->double_hodnota);
            else if (op1->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op1->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op1pom->id);
        }
        if (op2pom==NULL)
        {
            if (op2->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op2->double_hodnota);
            else if (op2->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op2->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op2pom->id);
        }
        printf("EQS\n");

        printf("ORS\n");
    }

    else if (operation->type==NEROVNOST)
    {
        if (op1pom==NULL)
        {
            if (op1->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op1->double_hodnota);
            else if (op1->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op1->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op1pom->id);
        }
        if (op2pom==NULL)
        {
            if (op2->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op2->double_hodnota);
            else if (op2->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op2->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op2pom->id);
        }
        printf("EQS\n");

        printf("NOTS\n");
    }

    else if (operation->type==ROVNOST)
    {
        if (op1pom==NULL)
        {
            if (op1->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op1->double_hodnota);
            else if (op1->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op1->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op1pom->id);
        }
        if (op2pom==NULL)
        {
            if (op2->type==NUMBER_DOUBLE)
                printf("PUSHS double@%f\n",op2->double_hodnota);
            else if (op2->type==NUMBER_INT)
                printf("PUSHS int@%d\n",op2->int_hodnota);
        }
        else
        {
            printf("PUSHS TF@%s\n",op2pom->id);
        }
        printf("EQS\n");
    }
}
