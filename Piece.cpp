#include "Piece.h"

using namespace std;

int Piece::getX()
{
	return x;
}

int Piece::getY()
{
	return y;
}

string Piece::getColour()
{
	return colour;
}

string Piece::getType()
{
	return type;
}

void Piece::promote(string type) //do not give player the option to reselect pawn
{
	if (Piece::type == "pawn")
	{
		Piece::type = type;
	}
}
