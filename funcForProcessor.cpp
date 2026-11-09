
#include "funcForProcessor.h"

#include "stdio.h"
#include <math.h>


void ADD(processor *proc)
{
    if(proc->workStack.size < 2){
        printf("Too small stack to add");
        assert(0);
    }
    int x = 0, y = 0;
    popStack(&proc->workStack, &x);
    popStack(&proc->workStack, &y);
    pushStack(&proc->workStack, x+y);
}
void OUTM(processor *proc)
{
    if(proc->workStack.size < 1){
        printf("Too small stack to out");
        assert(0);
    }
    int x = 0;
    popStack(&proc->workStack, &x);
    printf("%d\n", x);
}

void SUB(processor *proc)
{
    if(proc->workStack.size < 2){
        printf("Too small stack to sub");
        assert(0);
    }
    int x = 0, y = 0;
    popStack(&proc->workStack, &x);
    popStack(&proc->workStack, &y);
    pushStack(&proc->workStack, y-x);
}
void MUL(processor *proc)
{
    if(proc->workStack.size < 2){
        printf("Too small stack to mul");
        assert(0);
    }
    int x = 0, y = 0;
    popStack(&proc->workStack, &x);
    popStack(&proc->workStack, &y);
    pushStack(&proc->workStack, x*y);
}
void DIV(processor *pc)
{
    if(pc->workStack.size < 2){
        printf("Too small stack to div");
        assert(0);
    }
    int x = 0, y = 0;
    popStack(&pc->workStack, &x);
    popStack(&pc->workStack, &y);
    if(x == 0)
    {
        
    }

    pushStack(&pc->workStack, y/x);
    //return 0;
}

void POP(processor *comp)
{
    int len = 0;
    int x = 0;
    unsigned char num = *(comp->machineCode + comp->PC - 1);
    //printf("POP\n");
    popStack(&comp->workStack, &x);
    //printf("num %d\n", num);
    //printf("x = %d\n",num);
    if(num & 0x80)
    {
        
        if (num & 0x40)
        {
            //printf("%d\n",comp->regOfProcessor[machineCode[(*PC)]] );
            len += comp->regOfProcessor[FromPointerToInt(comp->machineCode + comp->PC)];
            comp->PC += 4;
        }
        if (num & 0x20)
        {
            len += FromPointerToInt(comp->machineCode + comp->PC);
            //printf("len %d", len);
            comp->PC += 4;
        }
        
        //printf("l = %d\n",len);
        comp->RAM[len] = x;
    }
    else
    {
        comp->regOfProcessor[FromPointerToInt(comp->machineCode + comp->PC)] = x;
        comp->PC += 4;
    }
    
    
}
void HLT(processor *proc)
{
    proc->PC = -1;
}

void processorDump(processor *comp, unsigned char* machineCode, int PC)
{
    
    stackDump(&comp->funcStack);
    stackDump(&comp->workStack);
    putchar('\n');

    for (int i = 0; i < 4; i++)
    {
        printf("%d reg = %d\n", i, comp->regOfProcessor[i]);
    }
    int startPoint = (PC - lefterThanPC) >= 0 ? PC - lefterThanPC : 0;
    for (int i = startPoint; i < PC + righterThanPC; i++)
    {
        printf("|%5d", machineCode[i]);
    }
    printf("|\n");
    for (int i = startPoint; i < PC; i++)
    {
        printf("      ");
    }
    printf("   ^");
    putchar('\n');
    printf("currectPc = %d", PC);
}

void JUMP(processor *proc)
{
    proc->PC = FromPointerToInt(proc->machineCode + proc->PC);
}

void JUMA(processor *proc)
{
    int x = 0, y = 0;
    popStack(&proc->workStack, &x);
    popStack(&proc->workStack, &y);
    if (x>y)
    {
        proc->PC = FromPointerToInt(proc->machineCode + proc->PC);
    }
    else
    {
        proc->PC+=4;
    }
}

void JUMB(processor *proc)
{
    int x = 0, y = 0;
    popStack(&proc->workStack, &x);
    popStack(&proc->workStack, &y);
    if (x<y)
    {
        proc->PC = FromPointerToInt(proc->machineCode + proc->PC);
    }
    else
    {
        proc->PC+=4;
    }
}

void JUMEA(processor *proc)
{
    int x = 0, y = 0;
    popStack(&proc->workStack, &x);
    popStack(&proc->workStack, &y);
    if (x>=y)
    {
        proc->PC = FromPointerToInt(proc->machineCode + proc->PC);
    }
    else
    {
        proc->PC+=4;
    }
}

void JUMEB(processor *proc)
{
    int x = 0, y = 0;
    popStack(&proc->workStack, &x);
    popStack(&proc->workStack, &y);
    if (x<=y)
    {
        proc->PC = FromPointerToInt(proc->machineCode + proc->PC);
    }
    else
    {
        proc->PC+=4;
    }
}
void GETKEY(processor* proc)
{
    int x = GetKey(FromPointerToInt(proc->machineCode + proc->PC));
    proc->PC += 4;
    pushStack(&proc->workStack, x);
}
void DRAWScreen(processor *proc)
{
    draw(proc->RAM);
}
void JUME(processor *proc)
{
    int x = 0, y = 0;
    popStack(&proc->workStack, &x);
    popStack(&proc->workStack, &y);
    if (x==y)
    {
        proc->PC = FromPointerToInt(proc->machineCode + proc->PC);
    }
    else
    {
        proc->PC+=4;
    }
}
void JUMNE(processor *proc)
{
    int x = 0, y = 0;
    popStack(&proc->workStack, &x);
    popStack(&proc->workStack, &y);
    if (x != y)
    {
        proc->PC = FromPointerToInt(proc->machineCode + proc->PC);
    }
    else
    {
        proc->PC+=4;
    }
}
void DIVO(processor*proc)
{
     if(proc->workStack.size < 2){
        printf("Too small stack to div");
        assert(0);
    }
    int x = 0, y = 0;
    popStack(&proc->workStack, &x);
    popStack(&proc->workStack, &y);
    pushStack(&proc->workStack, y%x);
}

void CALL(processor *proc)
{
    pushStack(&proc->funcStack, proc->PC + 4);
    proc->PC = FromPointerToInt(proc->machineCode + proc->PC);
}

void ProcessorDumpComand(processor *proc)
{
    stackDump(&proc->funcStack);
    stackDump(&proc->workStack);
    putchar('\n');

    for (int i = 0; i < 4; i++)
    {
        printf("%d reg = %d\n", i, proc->regOfProcessor[i]);
    }
    int startPoint = (proc->PC - lefterThanPC) >= 0 ? proc->PC - lefterThanPC : 0;
    for (int i = startPoint; i < proc->PC + righterThanPC; i++)
    {
        printf("|%5d", proc->machineCode[i]);
    }
    printf("|\n");
    for (int i = startPoint; i < proc->PC; i++)
    {
        printf("      ");
    }
    printf("   ^");
    putchar('\n');
    printf("currectPc = %d", proc->PC);
}
void RET(processor *proc)
{
    int x = 0;
    popStack(&proc->funcStack, &x);
    proc->PC = x;
}

void INM(processor *proc)
{
    int x = 0;
    scanf("%d", &x);
    pushStack(&proc->workStack, x);
}

void SQRT(processor *proc)
{
    int x = 0;
    popStack(&proc->workStack, &x);
    pushStack(&proc->workStack, (int)sqrt(x));
}


void DRAW(int* RAM)
{
    for (int i = 0; i< sizeOfRAMLineY; i++)
    {
        for (int j = 0; j < sizeOfRAMLineX; j++)
        {
            putchar(RAM[i * sizeOfRAMLineX + j] > 0 ? ' ' : '*');
            //printf("%d ", RAM[i * sizeOfRAMLine + j]);
        }
        putchar('\n');
    }
}

void SIN(processor *proc)
{
    int x = 0;
    popStack(&proc->workStack, &x);
    pushStack(&proc->workStack, 1000 * sin(x * (M_PI/180)));
}

void COS(processor *proc)
{
    int x = 0;
    popStack(&proc->workStack, &x);
    pushStack(&proc->workStack, 1000 * cos(x * (M_PI/180)));
}
int FromPointerToInt(unsigned char* c)
{
    return c[0] << 24 | c[1] << 16 | c[2] << 8 | c[3];
}
void PushGOD(processor *comp)
{
    int len = 0;
    unsigned char x = *(comp->machineCode + comp->PC -1);

    if (x & 0x40)
    {
        //printf("%d", comp->regOfProcessor[machineCode[(*PC)]]);
        len += comp->regOfProcessor[FromPointerToInt(comp->machineCode + comp->PC)];
        comp->PC += 4;
    }
    if (x & 0x20)
    {
        
        len += FromPointerToInt(comp->machineCode + comp->PC);
        comp->PC += 4;
       
    }
    
    if (x & 0x80)
    {
        //printf("len2 = %d\n", len);
        len = comp->RAM[len];
    }
    pushStack(&comp->workStack, len);
}