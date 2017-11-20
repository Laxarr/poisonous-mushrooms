#include "symtable.h"

Sym_Tab* sym_tab_init(){
    Sym_Tab* table = (Sym_Tab *) malloc(sizeof(Sym_Tab));
    if (table == NULL)
        return NULL;
    table->root=NULL;
    return table;
}

int sym_tab_insert(SymTab_Element *root,SymTab_Element* elem)
{
    if (root==NULL)
    {
        root = elem;
        return 1;
    }
    int i=strcmp(elem->id,root->id);
    if (i<0)
    {
        return sym_tab_insert(root->left,elem);
    }
    else if (i>0)
    {
        return sym_tab_insert(root->right,elem);
    }
    else
    {
        return 1;
    }
}

SymTab_Element* sym_tab_find(SymTab_Element *root,char* id)
{
    if (root==NULL)
    {
        return NULL;
    }

    int i=strcmp(id,root->id);
    if (i<0)
    {
        return sym_tab_find(root->left,id);
    }
    else if (i>0)
    {
        return sym_tab_find(root->right,id);
    }
    else
        return root;
}

void print_tree(SymTab_Element *root)
{
    if (root != NULL)
    {
        print_tree(root->left);
        printf("%s\n",root->id);
        print_tree(root->right);
    }
}

void sym_tab_free(SymTab_Element *root)
{
    if (root != NULL)
    {
        sym_tab_free(root->left);
        sym_tab_free(root->right);
        free(root);
    }
    root=NULL;
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
        new_elem_ptr->declared=1;
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
        new_elem_ptr->declared=1;
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
        new_elem_ptr->declared=1;
        new_elem_ptr->initialized=0;
        new_elem_ptr->left=NULL;
        new_elem_ptr->right=NULL;
        return new_elem_ptr;
    }
}
