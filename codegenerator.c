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
int typetestcount=0;
int concat=0;
int tempvarcount=0;
int substrcount=0;

void Program_begin()//Zacatek programu
{
    printf(".IFJcode17\n");
    printf("DEFVAR GF@pom\n");
    printf("JUMP main\n");
}

void Main_fun()//Hlavni telo programu
{
    printf("LABEL main\n");
    printf("CREATEFRAME\n");
}

void IfCond()//Podminka v if then else vyrazu
{
    printf("PUSHS bool@true\n");
    printf("JUMPIFNEQS ifelse%d\n",ifelsecount);
}

void Iftrueend()//Label pro kladne vyhodnoceni vyrazu v if then else vyrazu
{
    printf("JUMP ifelseend%d\n",ifelsecount);
}

void IfElse()//Label pro zaporne vyhodnoceni vyrazu v if then else vyrazu
{
    printf("LABEL ifelse%d\n",ifelsecount);
}

void IfEnd()//Label pro konec if then else vyrazu
{
    printf("LABEL ifelseend%d\n",ifelsecount);
    ifelsecount++;
}

void LoopStart()//Label pro zacatek cyklu
{
    cycle=1;
    for (int i=0;i<10;i++)
    {
        printf("DEFVAR TF@tempvar%d\n",tempvarcount+i);
    }
    printf("LABEL while%d\n",dowhilecount);
}

void LoopCond()//podminka cyklu
{
    printf("PUSHS bool@true\n");
    printf("JUMPIFNEQS whileend%d\n",dowhilecount);
}

void LoopEnd()//Konec cyklu
{
    printf("JUMP while%d\n",dowhilecount);
    printf("LABEL whileend%d\n",dowhilecount);
    dowhilecount++;
    cycle=0;
}

void Declare_var(char* id)//deklarace promenne
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

void Read(token* var)//cteni ze vstupu
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
}

void ConvertToInt()//konverze typu
{
    printf("FLOAT2INTS\n");
}

void ConvertToFloat()//konverze typu
{
    printf("INT2FLOATS\n");
}

void Write()//vyps na vystup
{
    printf("POPS GF@pom\n");
    printf("WRITE GF@pom\n");
}

void PushRetVal(token* tok)//vrati navratovou hodnotu
{
    if (tok->type==NUMBER_DOUBLE)
    {
        printf("PUSHS float@%f\n",tok->double_hodnota);
        exprtype=SymTab_DataType_Double;
    }
    else if (tok->type==NUMBER_INT)
    {
        printf("PUSHS int@%d\n",tok->int_hodnota);
        exprtype=SymTab_DataType_Integer;
    }
    else if (tok->type==RETEZEC)
    {
        printf("PUSHS string@%s\n",tok->string_hodnota);
        exprtype=SymTab_DataType_String;
    }
    else
    {
        printf("PUSHS TF@%s\n",tok->string_hodnota);
    }
}

void PushParam(token* tok)//umisti na zasobnik parametr funkce
{
    if (tok->type==NUMBER_DOUBLE)
    {
        printf("PUSHS float@%f\n",tok->double_hodnota);
        exprtype=SymTab_DataType_Double;
    }
    else if (tok->type==NUMBER_INT)
    {
        printf("PUSHS int@%d\n",tok->int_hodnota);
        exprtype=SymTab_DataType_Integer;
    }
    else if (tok->type==RETEZEC)
    {
        printf("PUSHS string@%s\n",tok->string_hodnota);
        exprtype=SymTab_DataType_String;
    }
    else
    {
        printf("PUSHS TF@%s\n",tok->string_hodnota);
    }
}

void Call_fun(char* id)//volani funkce
{
    printf("PUSHFRAME\n");
    printf("CALL %s\n",id);
    printf("POPFRAME\n");
}

void Declare_fun(char* id)//deklarace funkce
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

void ImplicitReturn()//Implicitni navratova hodnota
{
    SymTab_DataType pom=sym_tab_find(CurrentST,currentfun)->data_type;
    if (pom==SymTab_DataType_Double)
    {
        printf("PUSHS float@0.0\n");
    }
    else if (pom==SymTab_DataType_Integer)
    {
        printf("PUSHS int@0\n");
    }
    else if (pom==SymTab_DataType_String)
    {
        printf("PUSHS string@\n");
    }
}

void Declare_funend()//Konec funkce
{
    printf("RETURN\n");
}

void AssignVal(char* id)//Prirazeni hodnoty vyrazu
{
    printf("POPS TF@%s\n",id);
}

void Length()//Funkce pro delku retezce
{
    printf("DEFVAR TF@tempvar%d\n",tempvarcount);
    printf("POPS TF@tempvar%d\n",tempvarcount);
    printf("STRLEN TF@tempvar%d TF@tempvar%d\n",tempvarcount,tempvarcount);
    printf("PUSHS TF@tempvar%d\n",tempvarcount);
    tempvarcount++;
    exprtype=SymTab_DataType_Integer;
}

void SubStr()//Funkcepro podretezec
{
    printf("PUSHFRAME\n");
    printf("CREATEFRAME\n");
    printf("DEFVAR TF@n\n");
    printf("POPS TF@n\n");
    printf("DEFVAR TF@i\n");
    printf("POPS TF@i\n");
    printf("DEFVAR TF@s\n");
    printf("POPS TF@s\n");
    printf("DEFVAR TF@res\n");
    printf("MOVE TF@res string@\n");
    printf("DEFVAR TF@index\n");
    printf("DEFVAR TF@length\n");
    printf("STRLEN TF@length TF@s\n");

    printf("LT GF@pom TF@i int@1\n");
    printf("PUSHS GF@pom\n");
    printf("EQ GF@pom TF@length int@0\n");
    printf("PUSHS GF@pom\n");
    printf("ORS\n");
    printf("PUSHS bool@true\n");
    printf("JUMPIFNEQS substrcond1%d\n",substrcount);
    printf("PUSHS string@\n");
    printf("JUMP substrend%d\n",substrcount);

    printf("LABEL substrcond1%d\n",substrcount);
    printf("SUB TF@i TF@i int@1\n");
    printf("LT GF@pom TF@n int@1\n");
    printf("PUSHS GF@pom\n");
    printf("GT GF@pom TF@n TF@length\n");
    printf("PUSHS GF@pom\n");
    printf("ORS\n");
    printf("PUSHS bool@true\n");
    printf("JUMPIFNEQS substrcond2%d\n",substrcount);

    printf("MOVE TF@index TF@i\n");
    printf("LABEL substrloop1%d\n",substrcount);
    printf("LT GF@pom TF@index TF@length\n");
    printf("JUMPIFNEQ substrret%d GF@pom bool@true\n",substrcount);
    printf("GETCHAR GF@pom TF@s TF@index\n");
    printf("CONCAT TF@res TF@res GF@pom\n");
    printf("ADD TF@index TF@index int@1\n");
    printf("JUMP substrloop1%d\n",substrcount);

    printf("LABEL substrcond2%d\n",substrcount);
    printf("MOVE TF@index int@0\n");
    printf("LABEL substrloop2%d\n",substrcount);
    printf("LT GF@pom TF@index TF@n\n");
    printf("JUMPIFNEQ substrret%d GF@pom bool@true\n",substrcount);
    printf("ADD GF@pom TF@i TF@index\n");
    printf("GETCHAR GF@pom TF@s GF@pom\n");
    printf("CONCAT TF@res TF@res GF@pom\n");
    printf("ADD TF@index TF@index int@1\n");
    printf("JUMP substrloop2%d\n",substrcount);


    printf("LABEL substrret%d\n",substrcount);
    printf("PUSHS TF@res\n");
    printf("LABEL substrend%d\n",substrcount);
    printf("POPFRAME\n");
    substrcount++;
    exprtype=SymTab_DataType_String;
}

void Asc()//Funkce pro ascii hodnotu znaku
{
    printf("DEFVAR TF@tempvar%d\n",tempvarcount+1);
    printf("POPS TF@tempvar%d\n",tempvarcount+1);
    printf("DEFVAR TF@tempvar%d\n",tempvarcount);
    printf("POPS TF@tempvar%d\n",tempvarcount);
    printf("STRLEN GF@pom TF@tempvar%d\n",tempvarcount);
    printf("GT GF@pom TF@tempvar%d GF@pom\n",tempvarcount+1);
    printf("SUB TF@tempvar%d TF@tempvar%d int@1\n",tempvarcount+1,tempvarcount+1);
    printf("JUMPIFEQ ascfail%d GF@pom bool@true\n",asccount);
    printf("LT GF@pom TF@tempvar%d int@0\n",tempvarcount+1);
    printf("JUMPIFEQ ascfail%d GF@pom bool@true\n",asccount);
    printf("STRI2INT GF@pom TF@tempvar%d TF@tempvar%d\n",tempvarcount,tempvarcount+1);
    printf("PUSHS GF@pom\n");
    printf("JUMP ascend%d\n",asccount);
    printf("LABEL ascfail%d\n",asccount);
    printf("PUSHS int@0\n");
    printf("LABEL ascend%d\n",asccount);
    asccount++;
    tempvarcount+=2;
    exprtype=SymTab_DataType_Integer;
}

void Chr()//Funkce pro znak podle ascii hodnoty
{
    printf("DEFVAR TF@tempvar%d\n",tempvarcount);
    printf("POPS TF@tempvar%d\n",tempvarcount);
    printf("TYPE GF@pom TF@tempvar%d\n",tempvarcount);
    printf("JUMPIFNEQ typecheck%d GF@pom string@float\n",typetestcount);
    printf("FLOAT2INT TF@tempvar%d TF@tempvar%d\n",tempvarcount,tempvarcount);
    printf("LABEL typecheck%d\n",typetestcount);
    printf("PUSHS TF@tempvar%d\n",tempvarcount);
    printf("INT2CHARS\n");
    typetestcount++;
    tempvarcount++;
    exprtype=SymTab_DataType_String;
}

char* GetOperator(token* operation)//Vraci retezec s instrukci
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

void CheckOperands(token* operation,token* op1,token* op2)//Generator logicko-aritmetickych operaci
{
        SymTab_Element* op1pom=NULL;
        SymTab_Element* op2pom=NULL;
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

        if (concat==2)//Bude se provadet konkatenace
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
            exprtype=SymTab_DataType_String;
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
        //Konverce datovych typu
        if (op1pom!=NULL)
        {
            printf("TYPE GF@pom TF@%s\n",op1pom->id);
            printf("JUMPIFNEQ typecheck%d GF@pom string@int\n",typetestcount);
            printf("INT2FLOAT TF@%s TF@%s\n",op1pom->id,op1pom->id);
            printf("LABEL typecheck%d\n",typetestcount);
            typetestcount++;
        }
        if (op2pom!=NULL)
        {
            printf("TYPE GF@pom TF@%s\n",op2pom->id);
            printf("JUMPIFNEQ typecheck%d GF@pom string@int\n",typetestcount);
            printf("INT2FLOAT TF@%s TF@%s\n",op2pom->id,op2pom->id);
            printf("LABEL typecheck%d\n",typetestcount);
            typetestcount++;
        }

        //generovani aritmeticko/logickych operaci
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
        exprtype=SymTab_DataType_Double;
}


token* Operation(token* operation,token* op1,token* op2)//Triadresny kod
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
        relationcond=1;
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
        relationcond=1;
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
        relationcond=1;
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
        relationcond=1;
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
        relationcond=1;
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
        relationcond=1;
        return tok;
    }
    return NULL;
}
