#include "codeTocamds.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

#ifndef compilerFUNC
#define compilerFUNC

struct bufferC
{
    unsigned char *machineCode;
    int sizeofCode;
    int len;
};

int fromComandToNum(const char* comand, int secondIsNum);
int fromStrToNum(const char* str);
void addElementToArray(bufferC *buf, int el, int bytes);
void addCode(bufferC *buf, FILE* CodeTxt, char numArgs, int first, int second, int third);
void analizePUSH(int *lenCode, char* comand2, bufferC *bufferCode, FILE* Code);
void analizePOP(int *lenCode, char* comand2, bufferC *bufferCode, FILE* Code);
void analizeTwos(int *lenCode, char* comand, char* comand2, bufferC *bufferCode, FILE* Code, int *labels);
void analizeONEs(int *lenCode, char* comand, char* comand2, bufferC *bufferCode, FILE* Code, int *labels);

#endif