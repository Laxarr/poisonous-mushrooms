/********* codegenerator.h *********
 *
 * FIT VUT, IFJ 119
 * Author: Martin Gajdosik, xgajdo21
 * Summary: Gererator kodu.
 *
 */
#include <string.h>

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
void PushRetVal(token* tok);
void Declare_funend();
void ConvertToInt();
void ImplicitReturn();
void IfCond();
void Iftrueend();
void IfElse();
void IfEnd();
token* Operation(token* operation,token* op1,token* op2);
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
int writeout;
int cycle;
#endif

