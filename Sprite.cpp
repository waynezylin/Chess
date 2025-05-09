#include "Sprite.h"
#include "resource.h"
#include <iostream>
#include <String>
#include "framework.h"

#pragma comment(lib, "Msimg32.lib")

using namespace std;

Sprite::Sprite()
{
    empty = true;
    spriteBrush = HBRUSH();
}

Sprite::Sprite(int col, int row, int bg)
{
    empty = false;
    Sprite::spriteBrush = getSpriteBrush(col, row, bg);
}

HBRUSH Sprite::getSpriteBrush(int col, int row, int bg)
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
    
    if (bg == 1)//black
    {
        TransparentBlt(dstDC, 0, 0, 100, 100, memDC, xOfs, yOfs, 100, 100, RGB(255,255,255));
    }
    else if (bg == 2)
    {
        BitBlt(dstDC, 0, 0, 100, 100, memDC, xOfs, yOfs, SRCCOPY);
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                if (GetPixel(dstDC, i, j) == RGB(255, 255, 255))
                {
                    
                    SetPixel(dstDC, i, j, RGB(0, 255, 0));
                }
            }
        }
    }
    else//white
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
    //OutputDebugStringA(("col: " + std::to_string(col) + " | row: " + std::to_string(row) + "\n").c_str());
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

Sprite Sprite::getSprite(std::string type, bool black, int bg)
{
    int col, row;
    if (type == "rook")
    {
        col = 0;
    }
    else if (type == "knight")
    {
        col = 4;
    }
    else if (type == "bishop")
    {
        col = 1;
    }
    else if (type == "queen")
    {
        col = 2;
    }
    else if (type == "king")
    {
        col = 3;
    }
    else if (type == "pawn")
    {
        col = 5;
    }

    if (black)
    {
        row = 0;
    }
    else
    {
        row = 1;
    }
    return Sprite(col, row, bg);
}


