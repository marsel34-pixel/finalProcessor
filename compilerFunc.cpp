#include "compilerFunc.h"

int fromComandToNum(const char* comand, int secondIsNum)
{
    for (int i = 0; i < numComands; i++)
    {
        if(strcmp(comand, comands[i].nameCom) == 0)
        {
            return i;
        }
    }
    printf("something Wrong <%s>", comand);
    assert(0);
    return 0;
}

int fromStrToNum(const char* str)
{
    if (strcmp(str, "AX") == 0)
    {
        return AX;
    }
    else if (strcmp(str, "BX") == 0)
    {
        return BX;
    }
    else if (strcmp(str, "CX") == 0)
    {
        return CX;
    }
    else if (strcmp(str, "DX") == 0)
    {
        return DX;
    }
    
    printf("Bad str\n");
    assert(0);
    return -1;
}

void addElementToArray(bufferC *buf, int el, int bytes)
{
    if(buf->sizeofCode + 4 <= buf->len)
    {
        
        (buf->sizeofCode) *= 2;
        buf->machineCode = (unsigned char*)realloc(buf->machineCode, buf->sizeofCode);
        //printf("%p", buf);
        
    }
    for (int i = bytes - 1; i >= 0; i--)
    {
        //printf("%d ", (unsigned char)(el >> (i*8)));
        buf->machineCode[buf->len] = (unsigned char)(el >> (i*8));
        buf->len++;
    }
    
}

void addCode(bufferC *buf, FILE* CodeTxt, char numArgs, int first, int second, int third)
{
    if (numArgs == 3)
    {
        fprintf(CodeTxt, "%d %d %d\n", first, second, third);
        addElementToArray(buf, first, 1);
        addElementToArray(buf, second, 4);
        addElementToArray(buf, third, 4);
    }
    else if (numArgs == 2)
    {
        fprintf(CodeTxt, "%d %d\n", first, second);
        addElementToArray(buf, first, 1);
        addElementToArray(buf, second, 4);
    }
    else
    {
        fprintf(CodeTxt, "%d\n", first);
        addElementToArray(buf, first, 1);
    }
}
void analizePUSH(int *lenCode, char* comand2, bufferC *bufferCode, FILE* Code)
{
    int numberOfScnaf = 0;
    int numberBuf = 0;
    char nameReg[20] = {};
    (*lenCode)+=5;
    if (comand2[0] == '[')
    {
        numberOfScnaf = sscanf(comand2, "[%[A-DX] + %d", nameReg, &numberBuf);
        if (numberOfScnaf == 2)
        {
            (*lenCode)+=4;
            addCode(bufferCode, Code, 3, 0xE1, fromStrToNum(nameReg), numberBuf);
        }
        else if (numberOfScnaf == 1)
        {
            
            addCode(bufferCode, Code, 2, 0xC1, fromStrToNum(nameReg), 0);
        }
        else 
        {
            sscanf(comand2, "[%d", &numberBuf);
            addCode(bufferCode, Code, 2, 0xA1, numberBuf, 0);
        }
    }
    else
    {
        numberOfScnaf = sscanf(comand2, "%[A-DX] + %d", nameReg, &numberBuf);
        if (numberOfScnaf == 2)
        {
            (*lenCode)+=4;
            addCode(bufferCode, Code, 3, 0x61, fromStrToNum(nameReg), numberBuf);
        }
        else if (numberOfScnaf == 1)
        {
            
            addCode(bufferCode, Code, 2, 0x41, fromStrToNum(nameReg), 0);
        }
        else 
        {
            sscanf(comand2, "%d", &numberBuf);
            addCode(bufferCode, Code, 2, 0x21, numberBuf, 0);
        }
    }
}

void analizePOP(int *lenCode, char* comand2, bufferC *bufferCode, FILE* Code)
{
    (*lenCode)+=5;
    int numberOfScnaf = 0;
    int numberBuf = 0;
    char nameReg[20] = {};
    if (comand2[0] == '[')
    {
        numberOfScnaf = sscanf(comand2, "[%[A-DX] + %d", nameReg, &numberBuf);
        if (numberOfScnaf == 2)
        {
            (*lenCode)+=4;
            addCode(bufferCode, Code, 3, 0xE7, fromStrToNum(nameReg), 
                numberBuf);
        }
        else if (numberOfScnaf == 1)
        {
            addCode(bufferCode, Code, 2, 0xC7, fromStrToNum(nameReg), 0);
        }
        else 
        {
            sscanf(comand2, "[%d", &numberBuf);
            addCode(bufferCode, Code, 2, 0xA7, numberBuf, 0);
        }
    }
    else
    {
        numberOfScnaf = sscanf(comand2, "%[A-DX] + %d", nameReg, &numberBuf);
        if (numberOfScnaf == 2 || numberOfScnaf == 0)
        {
            assert(0);
        }
        else
        {
            addCode(bufferCode, Code, 2, 0x47, fromStrToNum(nameReg), 0);
        }
    }
}

void analizeTwos(int *lenCode, char* comand, char* comand2, bufferC *bufferCode, FILE* Code, int *labels)
{
    char* endNumberPtr = NULL;
    int numberBuf = strtod(comand2, &endNumberPtr);

    (*lenCode)+=5;
    if (*endNumberPtr == '\0')
    {
        endNumberPtr == NULL;
        addCode(bufferCode, Code, 2, fromComandToNum(comand, 1),numberBuf,0);
    }
    else
    {
        if (comand2[0] == ':')
        {
            numberBuf = strtod(comand2 + 1, &endNumberPtr);
            assert(*endNumberPtr == '\0');
            addCode(bufferCode, Code, 2, fromComandToNum(comand, 1),labels[numberBuf],0);
        }
        else
        {
            addCode(bufferCode, Code, 2, fromComandToNum(comand, 0),fromStrToNum(comand2),0);
        }
    }
}
void analizeONEs(int *lenCode, char* comand, char* comand2, bufferC *bufferCode, FILE* Code, int *labels)
{
    char* endNumberPtr = NULL;
    int numberBuf = 0;
    if (comand[0] == ':')
    {
        numberBuf = strtod(comand + 1, &endNumberPtr);
        if (*endNumberPtr != '\0')
        {
            printf("wrongLabel\n");
            assert(0);
        }
        
        labels[numberBuf] = *lenCode;
        //printf("%d", labels[numberBuf]);
    }
    else
    {
        (*lenCode)++;
        addCode(bufferCode, Code, 1, fromComandToNum(comand, 0),0,0);
    }
}