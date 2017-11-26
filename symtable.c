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
    if (elem==NULL || table==NULL)
        return 0;
    SymTab_Element* pom=table->root;
    if (pom==NULL)
    {
        table->root=elem;
        return 1;
    }
    else
    {
        while (pom!=NULL)
        {
           int i=strcmp(elem->id,pom->id);
           if (i==0)
           {
               return 1;
           }
           else if (i<0)
           {
               if (pom->left==NULL)
               {
                   pom->left=elem;
                   return 1;
               }
               else
               {
                   pom=pom->left;
               }
           }
           else if (i>0)
           {
               if (pom->right==NULL)
               {
                   pom->right=elem;
                   return 1;
               }
               else
               {
                   pom=pom->right;
               }
           }
        }
    }
    return 0;
}

SymTab_Element* sym_tab_find(Sym_Tab *table,char* id)
{
    if (table==NULL)
    {
        return NULL;
    }
    SymTab_Element* pom=table->root;
    if (pom==NULL)
    {
        return NULL;
    }
    else
    {
        while (pom!=NULL)
        {
           int i=strcmp(id,pom->id);
           if (i==0)
           {
                return pom;
           }
           else if (i<0)
           {
                pom=pom->left;
           }
           else if (i>0)
           {
                pom=pom->right;
           }
        }
    }
    return NULL;
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
        new_elem_ptr->declared=0;
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
        new_elem_ptr->declared=0;
        new_elem_ptr->initialized=0;
        new_elem_ptr->paramcount=0;
        new_elem_ptr->pararr=malloc(sizeof(pararray));
        InitParArray(new_elem_ptr->pararr);
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
        new_elem_ptr->declared=0;
        new_elem_ptr->initialized=0;
        new_elem_ptr->left=NULL;
        new_elem_ptr->right=NULL;
        return new_elem_ptr;
    }
}
