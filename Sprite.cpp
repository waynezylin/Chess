#include "Sprite.h"
#include "resource.h"
#include <iostream>
#include <String>

#pragma comment(lib, "Msimg32.lib")

using namespace std;

Sprite::Sprite()
{
    empty = true;
    spriteBrush = HBRUSH();
}

Sprite::Sprite(int col, int row, bool bgBlk)
{
    empty = false;
    Sprite::spriteBrush = getSpriteBrush(col, row, bgBlk);
}

HBRUSH Sprite::getSpriteBrush(int col, int row, bool bgBlk)
{
    //HBITMAP spriteSheet = (HBITMAP)LoadImage(NULL, MAKEINTRESOURCE(IDB_SPRITESHEET), IMAGE_BITMAP, 0, 0, 0);
    HBITMAP spriteSheet = LoadBitmap((HINSTANCE)GetModuleHandle(_T("Chess.exe")), MAKEINTRESOURCE(IDB_SPRITESHEET));

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

void Sprite::drawSprite(int x, int y, HDC paintDC)
{
    RECT curDstRect;

    curDstRect.left = x*100;
    curDstRect.top = y*100;
    curDstRect.right = curDstRect.left + 100;
    curDstRect.bottom = curDstRect.top + 100;
    SelectObject(paintDC, spriteBrush);
    FillRect(paintDC, &curDstRect, spriteBrush);
    DeleteObject(spriteBrush);

}

Sprite Sprite::getDefaultSprite(int col, int row)
{
    OutputDebugStringA(("col: " + std::to_string(col) + " | row: " + std::to_string(row) + "\n").c_str());
    if (row > 1 && row < 6)
    {
        return Sprite();
    }
    int x, y;
    bool boev = ((col + row) % 2 == 0) ? false : true;
    switch (col)
    {
    case 0:
        x = 0;
        break;

    case 1:
        x = 1;
        break;

    case 2:
        x = 4;
        break;

    case 3:
        x = 2;
        break;

    case 4:
        x = 3;
        break;

    case 5:
        x = 4;
        break;

    case 6:
        x = 1;
        break;

    case 7:
        x = 0;
        break;
    }

    switch (row) 
    {
    case 0:
        y = 0;
        break;

    case 1:
        y = 0;
        x = 5;
        break;
#
    case 6:
        y = 1;
        x = 5;
        break;

    case 7:
        y = 1;
        break;
    }
    return Sprite(x, y, boev);
}

bool Sprite::isEmpty()
{
    return empty;
}