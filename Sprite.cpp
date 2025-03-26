#include "Sprite.h"
#include <iostream>
//#include "framework.h";
#pragma comment(lib, "Msimg32.lib")

using namespace std;

Sprite::Sprite(int col, int row, bool bgBlk)
{
    Sprite::spriteBrush = getSpriteBrush(col, row, bgBlk);
}

HBRUSH Sprite::getSpriteBrush(int col, int row, bool bgBlk)
{
    HBITMAP spriteSheet = (HBITMAP)LoadImage(NULL, L"d:\\Coding\\Chess\\sprite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    HDC memDC, dstDC, curDC;
    HBITMAP oldMemBmp, oldDstBmp, dstBmp;
    curDC = GetDC(HWND_DESKTOP);

    memDC = CreateCompatibleDC(NULL);
    dstDC = CreateCompatibleDC(NULL);

    dstBmp = CreateCompatibleBitmap(curDC, 100, 100);
    int xOfs, yOfs;
    xOfs = 100 * col;
    yOfs = 100 * row;

    oldMemBmp = (HBITMAP)SelectObject(memDC, spriteSheet);
    oldDstBmp = (HBITMAP)SelectObject(dstDC, dstBmp);
    
    if(bgBlk == true)
    {
        TransparentBlt(dstDC, 0, 0, 100, 100, memDC, xOfs, yOfs, 100, 100, RGB(255,255,255));
    }
    else 
    {
        BitBlt(dstDC, 0, 0, 100, 100, memDC, xOfs, yOfs, SRCCOPY);
    }

    SelectObject(memDC, oldMemBmp);
    SelectObject(dstDC, oldDstBmp);
    ReleaseDC(HWND_DESKTOP, curDC);
    DeleteDC(memDC);
    DeleteDC(dstDC);

    HBRUSH result;
    result = CreatePatternBrush(dstBmp);
    DeleteObject(dstBmp);
    return result;
}

void Sprite::drawSprite(int x, int y, HDC paintDC, int numCols, int numRows)
{
    RECT curDstRect;

    curDstRect.left = x;
    curDstRect.top = y;
    curDstRect.right = curDstRect.left + 100;
    curDstRect.bottom = curDstRect.top + 100;
    SelectObject(paintDC, spriteBrush);
    FillRect(paintDC, &curDstRect, spriteBrush);
    DeleteObject(spriteBrush);

}