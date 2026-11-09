#include "draw.h"

#include "TXLib.h"
#include "funcForProcessor.h"

const int sizeOfEl = 4;
void init()
{
    txCreateWindow(sizeOfRAMLineX*sizeOfEl, sizeOfRAMLineY*sizeOfEl);
    txBegin();
}
void draw(int *RAM)
{
    static int *drawnBuf = (int*)calloc(sizeOfRAMLineX*sizeOfRAMLineY, 4);
    int buf = 0;
    int buf2 = 0;
    int buf3 = 0;
    //txClear();
    for (int y = 0; y < sizeOfRAMLineY; y++)
        {
        for (int x = 0; x < sizeOfRAMLineX; x++)
        {
            if(drawnBuf[y*sizeOfRAMLineX + x] != RAM[y*sizeOfRAMLineX + x]){
                drawnBuf[y*sizeOfRAMLineX + x] = RAM[y*sizeOfRAMLineX + x];
                if ((RAM[y*sizeOfRAMLineX + x] & 0xFF) == 0x4)
                {
                    buf = RAM[y*sizeOfRAMLineX + x] >> 24;
                    buf2 = RAM[y*sizeOfRAMLineX + x] >> 16;
                    buf3 = RAM[y*sizeOfRAMLineX + x] >> 8;
                    txSetFillColor(RGB(buf, buf2, buf3));
                    txSetColor (RGB(buf, buf2, buf3)); 
                }
                else if ((RAM[y*sizeOfRAMLineX + x] & 0xFF) == 0x3)
                {
                    buf = RAM[y*sizeOfRAMLineX + x] >> 8;
                    txSetFillColor(RGB(buf, 0, 0));
                    txSetColor (RGB(buf, 0, 0)); 
                }
                else if (RAM[y*sizeOfRAMLineX + x]==2)
                {
                    txSetFillColor(TX_BLACK);
                    txSetColor (TX_BLACK); 
                }
                else if ((RAM[y*sizeOfRAMLineX + x] & 0xFF) == 0x1)
                {
                    buf = RAM[y*sizeOfRAMLineX + x] >> 8;
                    txSetFillColor(RGB(buf, buf, buf));
                    txSetColor (RGB(buf, buf, buf)); 
                }
                else
                {
                    txSetColor (TX_BLUE);
                    txSetFillColor(TX_BLUE);
                }
                txRectangle(x*sizeOfEl, y*sizeOfEl, (x+1)*sizeOfEl, (y+1)*sizeOfEl);
            }
        }
    }
    txSleep(15);
    //txRedrawWindow();
}

int GetKey(int k)
{
    switch (k)
    {
    case 0:
        return txGetAsyncKeyState(VK_UP);
        break;
    case 1:
        return txGetAsyncKeyState(VK_DOWN);
        break;
    case 2:
        return txGetAsyncKeyState(VK_LEFT);
        break;
    case 3:
        return txGetAsyncKeyState(VK_RIGHT);
        break;
    default:
        return 0;
        break;
    }
}