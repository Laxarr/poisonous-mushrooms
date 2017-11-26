#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef CODEGENERATOR
#define CODEGENERATOR

#include "scanner.h"
#include "parser.h"

void Program_begin();
void Main_fun();
void Declare_var(char* id);
void Call_fun(char* id);
void PushParam(token* tok);
void Declare_fun(char* id);
void Declare_funend();
void IfCond();
void IfElse();
void IfEnd();
void Operation(token* operation,token* op1,token* op2);
void LooStart();
void LoopCond();
void LoopEnd();
int dowhilecount;
int ifelsecount;
int tempvarcount;
#endif

