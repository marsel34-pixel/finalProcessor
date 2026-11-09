
#include "stackM.h"
#include <assert.h>
#include "draw.h"

#ifndef funcForProc
#define funcForProc
const int lefterThanPC = 5;
const int righterThanPC = 10;
const int sizeOfRAMLineX = 200;
const int sizeOfRAMLineY = 200;
struct processor
{
    stack workStack;
    stack funcStack;
    int* RAM;
    int PC;
    int regOfProcessor[4];
    unsigned char* machineCode;
};
void JUMP(processor *proc);
void DIVO(processor *proc);

void JUMA(processor *proc);
void JUMB(processor *proc);
void JUMEA(processor *proc);
void JUMEB(processor *proc);
void JUME(processor *proc);
void JUMNE(processor *proc);
int FromPointerToInt(unsigned char* c);

void processorDump(processor *comp, unsigned char* machineCode, int PC);

void POP(processor *proc);
void ADD(processor *proc);
void OUTM(processor *proc);
void SUB(processor *proc);
void MUL(processor *proc);
void DIV(processor *proc);
void RET(processor *proc);
void CALL(processor *proc);
void INM(processor *proc);
void SQRT(processor *proc);
void HLT(processor *proc);
void ProcessorDumpComand(processor *proc);
void GETKEY(processor* proc);
void DRAWScreen(processor *proc);
void DRAW(int *RAM);
void SIN(processor *proc);
void COS(processor *proc);
void PushGOD(processor *comp);

#endif