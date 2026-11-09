#include "funcForProcessor.h"

struct comand
{
    void (*comp)(processor *proc);
    const char* nameCom;    
};


const comand comands[] = {{ProcessorDumpComand,"dumpProcessor"},
                    {PushGOD, "PUSH"},
                    {JUMP, "JUM"},
                    {JUMA, "JUMA"},
                    {JUMEA, "JUMEA"},
                    {JUMB, "JUMB"},
                    {JUMEB, "JUMEB"},
                    {POP, "POP"},
                    {JUME, "JUME"},
                    {JUMNE, "JUMNE"},
                    {ADD, "ADD"},
                    {SUB, "SUB"},
                    {OUTM, "OUT"},
                    {DIV, "DIV"},
                    {INM, "IN"},
                    {COS, "COS"},
                    {SIN, "SIN"},
                    {DIVO, "DIVO"},
                    {SQRT, "SQRT"},
                    {GETKEY, "GETK"},
                    {DRAWScreen, "DRAW"},
                    {CALL, "CALL"},
                    {RET, "RET"},
                    {MUL, "MUL"},
                    {HLT, "HLT"}};
const int numComands = 25;

enum registers
{
    AX,
    BX,
    CX,
    DX
};