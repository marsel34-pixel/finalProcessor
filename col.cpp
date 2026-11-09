#include <stdio.h>
#include <assert.h>

const int sizeDisplay = 40000;

int main()
{
    FILE* f = fopen("output_640x480.rgb", "rb");
    FILE* cod = fopen("k.bin", "wb");
    assert(f);
    unsigned char buf[sizeDisplay*3] = {};
    unsigned char bufLast[sizeDisplay*3] = {};
    
    unsigned char bufferBin[sizeDisplay*10+1] = {};
    int lenAdded = 0;
    for (int j = 0; ; j++)
    {
        if (fread(buf, 1, sizeDisplay*3, f) >= sizeDisplay*3)
        {
            if (j%1 == 0){
                lenAdded = 0;
                for (int i = 0; i < sizeDisplay; i++)
                {
                   
                    if (j == 0 || ((bufLast[i*3] - buf[i*3]) * (bufLast[i*3] - buf[i*3]) + 
                        (bufLast[i*3+1] - buf[i*3+1]) * (bufLast[i*3+1] - buf[i*3+1]) +
                        (bufLast[i*3+2] - buf[i*3+2]) * (bufLast[i*3+2] - buf[i*3+2]) >=1000))
                    {
                        bufferBin[lenAdded*10] = 0x21;//PUSH 
                        
                        bufferBin[lenAdded*10+1] = buf[i*3]; //COLOR
                        bufferBin[lenAdded*10+2] = buf[i*3+1];
                        bufferBin[lenAdded*10+3] = buf[i*3+2];
                        bufferBin[lenAdded*10+4] = 4;

                        bufferBin[lenAdded*10 + 5] = 0xA7;//POP

                        bufferBin[lenAdded*10 +6] = i >> 24;
                        bufferBin[lenAdded*10 +7] = i >> 16;//INDEX
                        bufferBin[lenAdded*10 +8] = i >> 8;
                        bufferBin[lenAdded*10 +9] = i;

                        bufLast[i*3] = buf[i*3];
                        bufLast[i*3+1] = buf[i*3+1];
                        bufLast[i*3+2] = buf[i*3+2];
                        lenAdded++;
                    }
                }
                bufferBin[lenAdded*10] = 20;
                fwrite(bufferBin, 1, lenAdded*10 + 1, cod);
            }
        }
        else
        {
            break;
        }
    }
    int z[1] = {2};
    fwrite(z, 4, 1, cod);
    //fprintf(cod, "%d", 9);
    fclose(f);
    fclose(cod);
}