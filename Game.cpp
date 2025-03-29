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
	return 0;
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
	return sizeof(black) / sizeof(black[0]);
}

int Game::getWL()
{
	return sizeof(white) / sizeof(white[0]);
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
