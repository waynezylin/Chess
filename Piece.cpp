#include "Piece.h"

using namespace std;

Piece::Piece()
{
	Piece::x = -1;
	Piece::y = -1;
	Piece::isBlk = false;
	Piece::type = "null";
}

Piece::Piece(int x, int y, bool isBlack, string type)
{
	Piece::x = x;
	Piece::y = y;
	Piece::isBlk = isBlack;
	Piece::type = type;
	Piece::pawnFirst = true;
	Piece::enpassant = false;
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
	if (Piece::type == "pawn" && pawnFirst && abs(Piece::y - y) == 2)
	{
		enpassant = true;
	}
	else 
	{
		enpassant = false;
	}
	Piece::x = x;
	Piece::y = y;
}

bool Piece::checkPawnFirst()
{
	return pawnFirst;
}

void Piece::pawnMove(bool m)
{
	pawnFirst = m;
}

bool Piece::equals(Piece p)
{
	if (p.type == Piece::type)
	{
		if (p.x == Piece::x)
		{
			if (p.y == Piece::y)
			{
				if (p.isBlk == Piece::isBlk)
				{
					return true;
				}
			}
		}
	}
	return false;
}
