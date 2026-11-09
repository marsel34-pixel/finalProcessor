#include "stackM.h"
#include <assert.h>

int initStack(stack* stk, size_t capacity ON_DEBUG(, const char* name, const char* file, const char* function, int line, void (*printElement)(int i ,stackType a)))
{
    ON_DEBUG(
    if (stk == NULL)
    {
        printEr("init NULL stack");
        ASSERTED;
        return 1;
    }
    if (capacity <= 0)
    {
        printEr("init 0 or lower capacity");
        ASSERTED;
        return 1;
    }
    )   
    //ON_DEBUG(printf("svo giod\n");)
    ON_DEBUG(
    if (stk->size != 0 || stk->capacity != 0 || stk->startCapacity != 0 
        || stk->file != NULL || stk->name != NULL || stk->line > 0 || stk->function != NULL || stk->isActive)
        {
        printEr("Error: initialize used stack\n");
        ASSERTED;
        return 1;
        }
    )
    #ifdef CANARY
        stk->stackPointer = (stackType*)calloc(capacity + 2, sizeof(stackType)) + 1;
    #else
        stk->stackPointer = (stackType*)calloc(capacity, sizeof(stackType));
    #endif

    if (stk->stackPointer)
    {
        
        //printf("right = %d\n", rightCanary(stk->stackPointer, stk->capacity));
        ON_DEBUG(stk->name = name; 
                 stk->file = file;
                 stk->function = function;
                 stk->line = line;
                 stk->printFunc = printElement;)
        setActive(stk, 1);
        stk->capacity = capacity;
        stk->startCapacity = capacity;

        #ifdef CANARY
            *getLeftCanary(stk) = canaryLeftStackNum;
            *getRightCanary(stk) = canaryRightStackNum;
        #endif

        for (int i = 0; i < stk->capacity; i++)
        {
            stk->stackPointer[i] = posionNumber;
        }

        #ifdef CANARY
            stk->leftStructCanary = canaryLeftStructNum;
            stk->rightStructCanary = canaryRightStructNum;
        #endif

        #ifdef HESH
            stk->hesh = getHeshFunc(stk);
        #endif
        return 0;
    }
    else 
    {
        printDump("TO HEAVY",NULL);
        return 1;
    }
    return 0;
}

int pushStack(stack* stk, stackType element)
{
    ON_DEBUG(if (checkStack(stk)) {setActive(stk, 0); ASSERTED; return 1;})

    //printf("right = %d\n", rightCanary(stk->stackPointer, stk->capacity));  
    if (stk->size + 1 > stk->capacity)
    {
        #ifdef CANARY
            stackType* buf = (stackType*)realloc(stk->stackPointer - 1, (stk->capacity  * multiplayCapacity  + 2) * sizeof(stackType));
        #else
            stackType* buf = (stackType*)realloc(stk->stackPointer, (stk->capacity  * multiplayCapacity) * sizeof(stackType));
        #endif
        if (buf)
        {
        
            stk->capacity *= multiplayCapacity;
            #ifdef CANARY
                stk->stackPointer = buf + 1;
                *getRightCanary(stk) = canaryRightStackNum;
            #else
                 stk->stackPointer = buf;
            #endif

            for (int i = stk->size; i < stk->capacity; i++)
            {
                stk->stackPointer[i] = posionNumber;
            }
            //printf("size increase %zu", stk->capacity);
        }
        else
        {
            printDump("TO HEAVY",NULL);
            return 1;
        }
    }

    stk->stackPointer[stk->size++] = element;
    #ifdef HESH
        stk->hesh = getHeshFunc(stk);
    #endif
    return 0;
}

int popStack(stack* stk, stackType *returnNumber)
{
    
    ON_DEBUG(
    if (checkStack(stk)) 
    {
        setActive(stk, 0);
        ASSERTED;
        return 1;
    } 
    if (stk->size == 0) 
    {
        stackDump(stk); 
        printEr("pop zero size stack\n");
        setActive(stk, 0);
        ASSERTED;
        return 1;
    })

    //printf("right = %d\n", rightCanary(stk->stackPointer, stk->capacity));
    if (stk->size == 0)
    {
        return 1;
    }
    if(stk->size * multiplayCapacity * multiplayCapacity < stk->capacity && stk->capacity > stk->startCapacity)
    {
        #ifdef CANARY
            stk->stackPointer = (stackType*)realloc(stk->stackPointer - 1, (stk->capacity / multiplayCapacity + 2) * sizeof(stackType)) + 1;
            stk->capacity /= multiplayCapacity;
            *getRightCanary(stk) = canaryRightStackNum;
        #else
            stk->stackPointer = (stackType*)realloc(stk->stackPointer, (stk->capacity / multiplayCapacity) * sizeof(stackType));
            stk->capacity /= multiplayCapacity;
        #endif
        //printf("size lower %zu\n", stk->capacity);
    }
    *returnNumber = stk->stackPointer[stk->size-1];
    
    stk->stackPointer[stk->size-1] = posionNumber;
    stk->size--;

    #ifdef HESH
        stk->hesh = getHeshFunc(stk);
    #endif

    return 0;
}

int destroyStack(stack* stk)
{
    ON_DEBUG(if (checkStack(stk)) {ASSERTED; return 1;})

    free(stk->stackPointer);
    ON_DEBUG(stk->name = NULL; 
                 stk->file = NULL;
                 stk->line = -1;
                 stk->function = NULL;)
    #ifdef HESH
        stk->hesh = 0;
    #endif

    setActive(stk, 0);
    stk->size = 0;
    stk->capacity = 0;
    stk->startCapacity = 0;
    return 0;
}

void stackDump(stack* stk)
{
    ON_DEBUG(
    printDump("stack \"%s\" [%p] created by = %s() at %s:%d\n", stk->name, stk->stackPointer, stk->function, stk->file, stk->line);

    #ifdef CANARY
    printDump("Struct Left canary = %#x (%s)  ", stk->leftStructCanary, stk->leftStructCanary == canaryLeftStructNum ? "ALive" : "Die");
    printDump("Struct right canary = %#x (%s)\n", stk->rightStructCanary, stk->rightStructCanary == canaryRightStructNum ? "ALive" : "Die");
    //printDump("stack left canary = %#x (%s)  ", *getLeftCanary(stk), *getLeftCanary(stk) == canaryLeftStackNum ? "ALive" : "Die");
    //printDump("stack right canary = %#x (%s)\n", *getRightCanary(stk), *getRightCanary(stk) == canaryRightStackNum ? "ALive" : "Die");
    #endif

    printDump("capacity = %zu;\n", stk->capacity);
    printDump("size = %zu;\n", stk->size);


    printDump("data\n", NULL);
    for (size_t i = 0; i < stk->capacity; i++)
    {
        if (stk->size > i)
        {
            stk->printFunc(i, stk->stackPointer[i]);
            //printDump("*[%zu] = " STACK_TYPE_DRAW "%s\n", i, stk->stackPointer[i], stk->stackPointer[i] == posionNumber ? "(POISON)" : "");
        }   
        else
        {
            putchar('*');
            stk->printFunc(i, stk->stackPointer[i]);
            //printDump("[%zu] = " STACK_TYPE_DRAW "%s\n", i, stk->stackPointer[i], stk->stackPointer[i] == posionNumber ? "(POISON)" : "");
        }
    }
    )
}

int checkStack(stack* stk)
{
    if (stk == NULL)
    {
        printEr("stack struct is NULL");
        return 1;
    }
    
    #if defined(CANARY) || defined(HESH)

    if (stk->isActive == 0)
    {
        printEr("Stack is broken");
        return 1;
    }
    #ifdef CANARY
    if (stk->leftStructCanary != canaryLeftStructNum || stk->rightStructCanary != canaryRightStructNum)
    {
        stackDump(stk); 
        printEr("StructCanaryIsDie\n");
        return 1;
    }
    if (isCanaryAlive(stk)) 
    {
        stackDump(stk); 
        printEr("StackCanaryIsDie\n");
        return 1;
    }
    #endif
    #else
    ON_DEBUG(if (!stk->isActive)
    {
        return 1;
    })
    #endif

    #ifdef HESH
    if(stk->hesh != getHeshFunc(stk))
    {   
        stackDump(stk);
        printEr("bad hesh");
        return 1;
    }
    #endif

    if (stk->stackPointer == NULL)
    {
        printEr("stack pointer is NULL");
        stackDump(stk);
        return 1;
    }
    if (stk->size > stk->capacity)
    {
        printEr("size of stack bigger than capacity");
        stackDump(stk);
        return 1;
    }
    
    return 0;
}
void setActive(stack *stk, int x)
{
    #if defined(CANARY) || defined(HESH)
        stk->isActive = x;
    #else 
        ON_DEBUG(stk->isActive = x;)
    #endif
}
#ifdef CANARY
bool isCanaryAlive(stack *stk)
{
    return *getRightCanary(stk) != canaryRightStackNum || *getLeftCanary(stk) != canaryLeftStackNum;
}

stackType* getLeftCanary(stack *stk)
{
    return stk->stackPointer - 1;
}

stackType* getRightCanary(stack *stk)
{
    return stk->stackPointer + stk->capacity;
}
#endif

int getHeshFunc(stack *stk)
{
    int hesh = 5831;
    unsigned char* p = (unsigned char*)stk->stackPointer;
    for (int i = 0; i < stk->capacity; i++)
    {
        hesh = hesh*33 + *p;
    }
    return hesh;
}