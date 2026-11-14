#include <stdio.h>
#include <assert.h>

const int sizeDisplay = 40000;

int main(int argc, char* argv[])
{
    int optimazeForBadApple = 0;
    if (argc == 2)
    {
        optimazeForBadApple = 1;
    }
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
                        
                        if (!optimazeForBadApple)
                        {
                            bufferBin[lenAdded*10+1] = buf[i*3]; //COLOR
                            bufferBin[lenAdded*10+2] = buf[i*3+1];
                            bufferBin[lenAdded*10+3] = buf[i*3+2];
                        }
                        else
                        {
                            if (buf[i*3] > 125)
                            {
                                bufferBin[lenAdded*10+1] = 255; //COLOR
                                bufferBin[lenAdded*10+2] = 255;
                                bufferBin[lenAdded*10+3] = 255;
                            }
                            else
                            {
                                bufferBin[lenAdded*10+1] = 0; //COLOR
                                bufferBin[lenAdded*10+2] = 0;
                                bufferBin[lenAdded*10+3] = 0;
                            }
                        }
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