#pragma once
#include "framework.h"

using namespace std;

class Piece
{
public:
	Piece();
	Piece(int x, int y, bool isBlack, string type);

	int getX();
	int getY();
	bool isBlack();
	string getType();

	void promote(string type);
	bool isBgBlk();

private:
	bool isBlk;
	string type;
	int x, y;

};