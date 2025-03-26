#pragma once

#include "framework.h"

class Sprite
{
public:
	Sprite(int col, int row, bool bgBlk);

	HBRUSH spriteBrush;

	void drawSprite(int x, int y, HDC paintDC, int numCols, int numRows);


private:
	HBRUSH getSpriteBrush(int col, int row, bool bgBlk);

};

