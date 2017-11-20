#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef SYMTABLE
#define SYMTABLE

typedef enum
{
    SymTab_ElemType_Var,
    SymTab_ElemType_Par,
    SymTab_ElemType_Fun
} SymTab_ElemType;

typedef enum
{
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
    int paramcount;
    struct SymTab_Element *left;
    struct SymTab_Element *right;
    struct Sym_Tab* localtable;
} SymTab_Element;

typedef struct Sym_Tab
{
    SymTab_Element* root;
} Sym_Tab;

SymTab_Element* create_sym_tab_elem_par(char* id, SymTab_DataType data);
SymTab_Element* create_sym_tab_elem_fun(char* id, SymTab_DataType data);
SymTab_Element* create_sym_tab_elem_var(char* id, SymTab_DataType data);
Sym_Tab* sym_tab_init();
int sym_tab_insert(SymTab_Element *root,SymTab_Element* elem);
SymTab_Element* sym_tab_find(SymTab_Element *root,char* id);
void sym_tab_free(SymTab_Element *root);
void print_tree(SymTab_Element *root);
#endif
