#include "symtab.h"

int sym_tab_init(Sym_Tab *table){
    table = (Sym_Tab *) malloc(sizeof(Sym_Tab));
    if (table == NULL)
        return -1;
    table->root=NULL;
    return 0;
}

int sym_tab_insert(Sym_Tab *table/*token*/)
{
    if (table == NULL)
        return -1;
    if (table->root==NULL)
    {
        SymTab_Element* new_elem_ptr = (SymTab_Element *) malloc(sizeof(SymTab_Element));

        if (new_elem_ptr == NULL)
        {
            return -1;
        }
        else
        {
            new_elem_ptr->id=""/*tokenid*/;
            new_elem_ptr->elem_type=SymTab_ElemType_Var/*tokentype*/;
            new_elem_ptr->data_type=SymTab_DataType_Integer/*tokendata*/;
            new_elem_ptr->declared=0;
            new_elem_ptr->initialized=0;
            new_elem_ptr->left=NULL;
            new_elem_ptr->right=NULL;
            table->root=new_elem_ptr;
            return 1;
        }
    }
    Sym_Tab* pom=table;
    int i=strcmp(table->root->id,""/*tokenid*/);
    if (i<0)
    {
        pom->root=pom->root->left;
        sym_tab_insert(pom/*token*/);
    }
    else if (i>0)
    {
        pom->root=pom->root->right;
        sym_tab_insert(pom/*token*/);
    }
    return 0;
}

SymTab_Element* sym_tab_find(Sym_Tab *table/*tokenid*/)
{
    if (table == NULL)
        return NULL;

    int i=strcmp(table->root->id,""/*tokenid*/);
    Sym_Tab* pom=table;

    if (i<0)
    {
        pom->root=pom->root->left;
        sym_tab_find(pom/*token*/);
    }
    else if (i>0)
    {
        pom->root=pom->root->right;
        sym_tab_find(pom/*token*/);
    }
    else
        return table->root;
    return NULL;
}

void sym_tab_free(Sym_Tab *table)
{
    if (table->root != NULL)
    {
        Sym_Tab* pom=table;
        pom->root=pom->root->left;
        sym_tab_free(pom);
        pom->root=pom->root->right;
        sym_tab_free(pom);
        free(table->root);
    }
    table->root=NULL;
}

