#include "Piece.h"

using namespace std;

Piece::Piece()
{
}

Piece::Piece(int x, int y, bool isBlack, string type)
{
	Piece::x = x;
	Piece::y = y;
	Piece::isBlk = isBlack;
	Piece::type = type;
}

int Piece::getX()
{
	return x;
}

int Piece::getY()
{
	return y;
}

bool Piece::isBlack()
{
	return isBlk;
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

bool Piece::isBgBlk()
{
	bool a = ((x + y) % 2 == 0) ? false : true;
	return a;
}

void Piece::move(int x, int y)
{
	Piece::x = x;
	Piece::y = y;
}
