#pragma once
#include "framework.h"

using namespace std;

class Piece
{
public:

	int getX();
	int getY();
	string getColour();
	string getType();

	void promote(string type);


private:

	string colour, type;
	int x, y;

};