
#include <stdio.h>
#include "stackM.h"
#include <assert.h>
#include "codeTocamds.h"
#include "funcForProcessor.h"
#include <sys/stat.h>
#define Draw
#ifdef Draw
#include "draw.h"
#endif
#include <stdlib.h>

void goProgram(unsigned char *machineCode);
void readFromFileForCode(unsigned char **code, const char* nameTextWithCode);


void printSt(int i , stackType a)
{
    printf("[%d] x = %d\n", i, a);
}


int main(int argc, const char** argv)
{
    if (argc == 2)
    {
        unsigned char *machineCode = NULL;

        readFromFileForCode(&machineCode, argv[1]);
        goProgram(machineCode);
    }
    else
    {
        printf("Bad start");
    }
}

void goProgram(unsigned char *machineCodes)
{
    struct processor computer = {};
    computer.machineCode = machineCodes;
    #ifdef Draw
    init();
    #endif
    initStackShort(&computer.workStack, 10, printSt);
    initStackShort(&computer.funcStack, 10, printSt);

    computer.RAM = (int*)calloc(sizeOfRAMLineX*(sizeOfRAMLineY+1), 4);
    //int PC = 0;
    int buf = 0;
    //bool ProgramWork = 1;
    while (computer.PC > -1)
    {
        //processorDump(&computer, computer.machineCode, computer.PC);
        //getchar();
        unsigned char x = *(computer.machineCode + computer.PC);
        computer.PC+=1;

        //printf("x = %d %d\n",x, x & 0x1F);
        comands[x & 0x1F].comp(&computer);
        
    }
}

void readFromFileForCode(unsigned char **code, const char* nameTextWithCode)
{
    FILE* codeBin = fopen(nameTextWithCode, "rb");
    struct stat fileStat= {};
    stat(nameTextWithCode, &fileStat);
    printf("file stat = %d", fileStat.st_size);
    (*code) = (unsigned char*)calloc((fileStat.st_size), 1);
    fread(*code, 1, fileStat.st_size, codeBin);
    fclose(codeBin);
}