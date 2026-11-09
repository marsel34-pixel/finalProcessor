#include <stdio.h>
#include <string.h>
#include <assert.h>
const int maxLenCode = 100;
const char* fromNumToComand(int d)
{
    switch (d)
    {
    case 1:
        return "PUSH";
    case 2:
        return "ADD";
    case 3:
        return "OUT";
    case 4:
        return "SUB";
    case 5:
        return "MUL";
    case 6:
        return "DIV";
    case 148:
        return "HLT";
    default:
        printf("pizdez blat %d\n", d);
        assert(0);
        return 0;
    }
} 
int main()
{
    //FILE* code = fopen("Code.txt", "r");
    FILE* disasembled = fopen("Disasembled.txt", "w");
    FILE* code = fopen("Code.txt", "r");
    int comand = 0;
    double num = 0;
    int numberOfRead = 1;
    int i = 0;
    char buffer[maxLenCode] = {};
    

    while (fgets(buffer, maxLenCode, code))
    {
        numberOfRead = sscanf(buffer, "%d %lg", &comand, &num);
        //printf("%d ", comand);
        if (numberOfRead == 1)
        {
            //code[i++] = comand;
            fprintf(disasembled, "%s\n", fromNumToComand(comand));
        }
        else if (numberOfRead == 2)
        {
            fprintf(disasembled, "%s %lg\n", fromNumToComand(comand), num);
            //code[i++] = comand;
            //code[i++] = num;
        }
    }

}