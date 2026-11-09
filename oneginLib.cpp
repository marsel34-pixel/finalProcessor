#include "oneginLib.h"

#include <assert.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


int readFromFile(const char* nameFile, char* index[])
{
    assert(nameFile);
    assert(index);

    int file = open(nameFile, O_RDONLY | _O_BINARY);    

    if (file == -1)
    {
        printf("cant open file");
        assert(0);
    }

    struct stat fileStat= {};
    stat(nameFile, &fileStat);

    char* buffer = (char*)calloc(fileStat.st_size + 2, 1);
    
    read(file, buffer, fileStat.st_size);

    int numberOfStr = 1;
    index[0] = buffer;
    //printf("<%s>", buffer);
    //printf("stat = %d\n", fileStat.st_size);
    for (int i = 0; i < fileStat.st_size; i++)
    {

        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            index[numberOfStr] = buffer + i + 1;
            if(checkForEmpty(index[numberOfStr]))
            {
                numberOfStr++;
                if (numberOfStr > maxTextSize - 1)
                {
                    close(file);
                    assert(0);
                }
            }
        }
        else if(buffer[i] == '\r')
        {
            buffer[i] = '\n';
        }
    }
    
    buffer[fileStat.st_size] = '\n';
    buffer[fileStat.st_size + 1] = '\0';
    close(file);
    //printf("len = %d\n", numberOfStr);
    return numberOfStr;
}
int checkForEmpty(char* str)
{
    assert(str);
    int i = 0;
    while (str[i] != 0 && str[i] != '\n')
    {
        if (isAlphaOrNum(str[i++]))
        {
            return 1;
        }
    }
    return 0;
}
bool isAlphaOrNum(char a)
{
    return (a>='a' && a<='z') || (a>='A' && a<='Z') || (a>='0' && a<='9');
}