#include "symtable.h"

Sym_Tab* sym_tab_init(){
    Sym_Tab* table = (Sym_Tab *) malloc(sizeof(Sym_Tab));
    if (table == NULL)
        return NULL;
    table->root=NULL;
    return table;
}

int sym_tab_insert(Sym_Tab *table,SymTab_Element* elem)
{
    if (table==NULL)
    {
        return 0;
    }
    if (table->root==NULL)
    {
        table->root=elem;
        return 1;
    }
    int i=strcmp(elem->id,table->root->id);
    if (i<0)
    {
        Sym_Tab* pom=sym_tab_init();
        pom->root=table->root->left;
        return sym_tab_insert(pom,elem);
    }
    else if (i>0)
    {
        Sym_Tab* pom=sym_tab_init();
        pom->root=table->root->right;
        return sym_tab_insert(pom,elem);
    }
    else
    {
        return 1;
    }
}

SymTab_Element* sym_tab_find(Sym_Tab *table,char* id)
{
    if (table==NULL)
    {
        return NULL;
    }
    if (table->root==NULL)
    {
        return NULL;
    }

    int i=strcmp(id,table->root->id);
    if (i<0)
    {
        Sym_Tab* pom=NULL;
        pom->root=table->root->left;
        return sym_tab_find(pom,id);
    }
    else if (i>0)
    {
        Sym_Tab* pom=NULL;
        pom->root=table->root->right;
        return sym_tab_find(pom,id);
    }
    else
        return table->root;
}

void print_tree(Sym_Tab *table)
{
    if (table==NULL)
    {
        return;
    }
    if (table->root != NULL)
    {
        Sym_Tab* pom=NULL;
        pom->root=table->root->left;
        print_tree(pom);
        printf("%s\n",table->root->id);
        pom->root=table->root->right;
        print_tree(pom);
    }
}

void sym_tab_free(Sym_Tab *table)
{
    if (table==NULL)
    {
        return;
    }
    if (table->root != NULL)
    {
        Sym_Tab* pom=NULL;
        pom->root=table->root->left;
        sym_tab_free(pom);
        pom->root=table->root->right;
        sym_tab_free(pom);
        free(pom->root);
    }
    table->root=NULL;
}

SymTab_Element* create_sym_tab_elem_par(char* id, SymTab_DataType data)
{
    SymTab_Element* new_elem_ptr = (SymTab_Element *) malloc(sizeof(SymTab_Element));
    if (new_elem_ptr == NULL)
    {
        return NULL;
    }
    else
    {
        new_elem_ptr->id=id;
        new_elem_ptr->elem_type=SymTab_ElemType_Par;
        new_elem_ptr->data_type=data;
        new_elem_ptr->initialized=0;
        new_elem_ptr->left=NULL;
        new_elem_ptr->right=NULL;
        return new_elem_ptr;
    }
}
SymTab_Element* create_sym_tab_elem_fun(char* id, SymTab_DataType data)
{
    SymTab_Element* new_elem_ptr = (SymTab_Element *) malloc(sizeof(SymTab_Element));
    if (new_elem_ptr == NULL)
    {
        return NULL;
    }
    else
    {
        new_elem_ptr->id=id;
        new_elem_ptr->elem_type=SymTab_ElemType_Fun;
        new_elem_ptr->data_type=data;
        new_elem_ptr->paramcount=0;
        new_elem_ptr->localtable=sym_tab_init();
        new_elem_ptr->left=NULL;
        new_elem_ptr->right=NULL;
        return new_elem_ptr;
    }
}
SymTab_Element* create_sym_tab_elem_var(char* id, SymTab_DataType data)
{
    SymTab_Element* new_elem_ptr = (SymTab_Element *) malloc(sizeof(SymTab_Element));
    if (new_elem_ptr == NULL)
    {
        return NULL;
    }
    else
    {
        new_elem_ptr->id=id;
        new_elem_ptr->elem_type=SymTab_ElemType_Var;
        new_elem_ptr->data_type=data;
        new_elem_ptr->initialized=0;
        new_elem_ptr->left=NULL;
        new_elem_ptr->right=NULL;
        return new_elem_ptr;
    }
}
