#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef STACK_M
#define STACK_M

//#define ALL_ON
#define ALL_OFF

#ifdef ALL_ON
#define ON_DEBUG(...) __VA_ARGS__
//#define CANARY 
#define HESH
#define ASSERTED assert(0)// dump stacktypes
#else
#ifdef ALL_OFF
#define ON_DEBUG(...) __VA_ARGS__
#define ASSERTED //assert(0)//on off dump stacktypes

#else

#define ON_DEBUG(...) __VA_ARGS__
#define CANARY 
#define HESH
#define ASSERTED assert(0)
#endif
#endif

#define redStart "\033[1;31m"
#define orangeStart "\033[93m"
#define endColor "\033[0m"

#define printEr(text) fprintf(stderr, redStart text endColor)
#define printDump(text, ...) fprintf(stderr, orangeStart text endColor, __VA_ARGS__)
struct twoNum{ int x; int y;};
typedef int stackType;
//#define STACK_TYPE_DRAW "%d"
#define initStackShort(stkPointer, capacity, func) initStack(stkPointer, capacity ON_DEBUG(, #stkPointer, __FILE__, __func__, __LINE__, func))

const int multiplayCapacity = 2;

const stackType canaryLeftStackNum = {0x0BEDAEDA};
const stackType canaryRightStackNum = {0xC0FFEE};
const long int canaryLeftStructNum = 0x67691488;
const long int canaryRightStructNum = 0x993B022;
const stackType posionNumber = {67};

struct stack
{
    #if defined(CANARY) || defined(HESH)
        long long int leftStructCanary;
        bool isActive;
    #else 
        ON_DEBUG(bool isActive);
    #endif
    #ifdef HESH
        int hesh;
    #endif
    stackType* stackPointer;
    size_t size;
    size_t capacity;
    size_t startCapacity;
    ON_DEBUG(const char* name; 
            const char* file;
            const char* function;
            int line;
            void (*printFunc)(int i, stackType a);)
    #ifdef CANARY
    long long int rightStructCanary;
    #endif
};
void setActive(stack *stk, int x);

int checkStack(stack* stk);

void stackDump(stack* stk);

int initStack(stack* stk, size_t capacity ON_DEBUG(, const char* name, const char* file, const char* function, int line, void (*printElement)(int i, stackType a)));

int pushStack(stack* stk, stackType element);

int popStack(stack* stk, stackType *returnNumber);

int destroyStack(stack* stk);
#ifdef CANARY
stackType* getLeftCanary(stack *stk);

stackType* getRightCanary(stack *stk);

bool isCanaryAlive(stack *stk);

#endif
int getHeshFunc(stack *stk);

#endif