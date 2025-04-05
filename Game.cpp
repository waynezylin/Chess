#include "Game.h"

Game::Game()
{
	for (int i = 0; i < 8; i++)
	{
		string type;
		switch (i)
		{
		case 0:
		case 7:
			type = "rook";
			break;
		case 1:
		case 6:
			type = "knight";
			break;
		case 2:
		case 5:
			type = "bishop";
			break;
		case 3:
			type = "queen";
			break;
		case 4:
			type = "king";
			break;
		}
		black[i] = Piece(i, 0, true, type);
		black[i + 8] = Piece(i, 1, true, "pawn");
		white[i] = Piece(i, 7, false, type);
		white[i + 8] = Piece(i, 6, false, "pawn");
	}
	tileChanged = false;
	pieceChanged = true;
	blkTurn = false;
	bS = sizeof(black) / sizeof(black[0]);
	wS = sizeof(white) / sizeof(white[0]);
	selectedPos = -1;
}

void Game::update()
{
	
}

bool Game::updateTile(POINT mouse)
{   
	mouse.x = trunc(mouse.x / 100);
	mouse.y = trunc(mouse.y / 100);
	//OutputDebugStringA(("mouseX: " + to_string(mouse.x) + " : ").c_str());
	//OutputDebugStringA(("mouseY: " + to_string(mouse.y) + "\n").c_str());
	if (tile.x != mouse.x)
	{
		prevTile.x = tile.x;
		tile.x = mouse.x;
		tileChanged = true;
		//OutputDebugStringA(("mouseX: " + to_string(mouse.x) + " : ").c_str());
		//OutputDebugStringA(("prev: " + to_string(prevTile.x) + " : ").c_str());
		//OutputDebugStringA(("cur: " + to_string(tile.x) + "\n").c_str());
	}
	if (tile.y != mouse.y)
	{
		prevTile.y = tile.y;
		tile.y = mouse.y;
		tileChanged = true;
		//OutputDebugStringA(("mouseY: " + to_string(mouse.y) + " : ").c_str());
		//OutputDebugStringA(("prev: " + to_string(prevTile.y) + " : ").c_str());
		//OutputDebugStringA(("cur: " + to_string(tile.y) + "\n").c_str());
	}
	return tileChanged;
}

POINT Game::getSelectedTile()
{
	return tile;
}

int Game::click()
{
	int clickS;
	Piece* clickP;
	if (blkTurn) {
		clickS = bS;
		clickP = black;
	}
	else
	{
		clickS = wS;
		clickP = white;
	}

	if (selectedPos == -1)
	{
		for (int i = 0; i < clickS; i++)
		{
			if (clickP[i].getX() == tile.x && clickP[i].getY() == tile.y)
			{

				selectedPos = i;
				return 1; //if nothing selected then select the piece at the current tile


			}
		}
	}
	else
	{
		if (tile.x == clickP[selectedPos].getX() && tile.y == clickP[selectedPos].getY())
		{
			selectedPos = -1;
			return 2; //if reselecting the piece that is already selected then reset the selected piece
		}


	}

	return -1;
}

Piece* Game::getBlackPieces()
{
	return black;
}

Piece* Game::getWhitePieces()
{
	return white;
}

int Game::getBL()
{
	return bS;
}

int Game::getWL()
{
	return wS;
}

void Game::resetTile()
{
	tileChanged = false;
}

bool Game::checkTC()
{
	return tileChanged;
}

bool Game::checkPC()
{
	return pieceChanged;
}

void Game::resetPC()
{
	pieceChanged = false;
}

POINT Game::getPrevTile()
{
	return prevTile;
}

void Game::setPotential()
{
	Piece p = (blkTurn) ? black[selectedPos] : white[selectedPos];
	if (p.getType() == "pawn")
	{
		if (p.isBlack())
		{
			POINT a;
			a.x = p.getX();
			a.y = p.getY() + 1;
			potential.push_back(a);
			a.x = p.getX();
			a.y = p.getY() + 2;
			potential.push_back(a);
		}
	}
	else if (p.getType() == "rook")
	{

	}
	else if (p.getType() == "knight")
	{

	}
	else if (p.getType() == "bishop")
	{

	}
	else if (p.getType() == "queen")
	{

	}
	else if (p.getType() == "king")
	{

	}
}

