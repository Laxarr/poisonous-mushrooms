#ifndef CODEGENERATOR
#define CODEGENERATOR

#include "scanner.h"
#include "parser.h"
#include "error.h"

void Program_begin();
void Main_fun();
void Declare_var(char* id);
void Read(token* var);
void Write();
void AssignVal(char* id);
void Call_fun(char* id);
void PushParam(token* tok);
void Declare_fun(char* id);
void Declare_funend();
void IfCond();
void Iftrueend();
void IfElse();
void IfEnd();
void Operation(token* operation,token* op1,token* op2);
void LoopStart();
void LoopCond();
void LoopEnd();
void SubStr();
void Asc();
void Chr();
void Length();
int dowhilecount;
int ifelsecount;
int tempvarcount;
#endif

