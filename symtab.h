#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    SymTab_ElemType_Var,
    SymTab_ElemType_Par,
    SymTab_ElemType_Fun
} SymTab_ElemType;

typedef enum
{
    SymTab_DataType_Void,
    SymTab_DataType_Integer,
    SymTab_DataType_Double,
    SymTab_DataType_String
} SymTab_DataType;

typedef struct SymTab_Element
{
    char* id;
    SymTab_ElemType elem_type;
    SymTab_DataType data_type;
    int declared;
    int initialized;
    struct SymTab_Element *left;
    struct SymTab_Element *right;
} SymTab_Element;

typedef struct Sym_Tab
{
    SymTab_Element* root;
} Sym_Tab;


int sym_tab_init(Sym_Tab *table);
int sym_tab_insert(Sym_Tab *table/*token*/);
SymTab_Element* sym_tab_find(Sym_Tab *table/*token*/);
void sym_tab_free(Sym_Tab *table);
