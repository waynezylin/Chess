#pragma once

#include "framework.h"

class Sprite
{
public:
	Sprite();

	Sprite(int col, int row, int bg);

	HBRUSH spriteBrush;

	void drawSprite(int x, int y, HDC paintDC);

	static Sprite getDefaultSprite(int col, int row);

	bool isEmpty();

	static Sprite getSprite(std::string type, bool black, int bg);


private:
	HBRUSH getSpriteBrush(int col, int row, int bg);

	bool empty;

};

