#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "oneginLib.h"
#include "compilerFunc.h"

void complile(int* labels, const char* nameFileWithCode)
{
    char* indexOfstr[maxTextSize] = {};
    FILE* Code = fopen("Code.txt", "w");
    FILE* codeBin = fopen("CodeBin.bin", "wb");
    int numberOfStr = readFromFile(nameFileWithCode, indexOfstr);
    char comand[100] = {};
    char comand2[100] = {};
    bufferC bufferCode = {};
    bufferCode.sizeofCode = 10000;
    bufferCode.machineCode = (unsigned char*)calloc(bufferCode.sizeofCode, 1);
    int numberOfScnaf = 0;
    int lenCode = 0;
    
    for (int i = 0; i < numberOfStr; i++)
    {
        numberOfScnaf = sscanf(indexOfstr[i], "%s %s", comand, comand2);
        
        if (strcmp(comand, "PUSH") == 0)
        {
            analizePUSH(&lenCode, comand2, &bufferCode, Code);
        }
        else if (strcmp(comand, "POP") == 0)
        {
            analizePOP(&lenCode, comand2, &bufferCode, Code);
        }
        else if (numberOfScnaf == 2)
        {
            analizeTwos(&lenCode, comand, comand2, &bufferCode, Code, labels);
        }
        else
        {
            analizeONEs(&lenCode, comand, comand2, &bufferCode, Code, labels);
        }
        //printf("%s %s %d\n", comand, comand2, lenCode);
    }
    fwrite(bufferCode.machineCode, 1, bufferCode.len, codeBin);
    free(bufferCode.machineCode);
    fclose(codeBin);
    fclose(Code);
}

int main(int argc, char** argv)
{
    if (argc == 2)
    {
        int labels[30] = {-1, -1, -1, -1};
        complile(labels, argv[1]);
        complile(labels, argv[1]);
    }
    else
    {
        printf("Bad start");
    }
}

