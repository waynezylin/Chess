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
		black.push_back(Piece(i, 0, true, type));
		black.push_back(Piece(i, 1, true, "pawn"));
		white.push_back(Piece(i, 7, false, type));
		white.push_back(Piece(i, 6, false, "pawn"));
	}
	tileChanged = false;
	pieceChanged = true;
	blkTurn = false;
	/*bS = sizeof(black) / sizeof(black[0]);
	wS = sizeof(white) / sizeof(white[0]);*/
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
	int clickS = (blkTurn) ? black.size() : white.size();
	vector<Piece>& clickP = (blkTurn) ? black : white;

	if (selectedPos == -1)
	{
		for (int i = 0; i < clickS; i++)
		{
			if (clickP[i].getX() == tile.x && clickP[i].getY() == tile.y)
			{

				selectedPos = i;
				setPotential();
				return 1; //if nothing selected then select the piece at the current tile
			}
		}
	}
	else
	{
		if (tile.x == clickP[selectedPos].getX() && tile.y == clickP[selectedPos].getY())
		{
			selectedPos = -1;
			resetPotential();
			return 2; //if reselecting the piece that is already selected then reset the selected piece
		}

		int occupied = -1;
		bool naMove = true;
		int atkPos = 0;
		for (Piece p : white)
		{
			if (p.getX() == tile.x && p.getY() == tile.y)
			{
				occupied = 1;
				break;
			}
			atkPos++;
		}
		if (occupied == -1)
		{
			atkPos = 0;
			for (Piece p : black)
			{
				if (p.getX() == tile.x && p.getY() == tile.y)
				{
					occupied = 2;
					break;
				}
				atkPos++;
			}
		}
		
		for (POINT pot : potential)
		{
			if (tile.x == pot.x && tile.y == pot.y)
			{
				naMove = false;
				break;
			}
		}
		if (!naMove)
		{
			switch (occupied)
			{
			case -1:
				if (clickP[selectedPos].getType() == "pawn" && clickP[selectedPos].checkPawnFirst() == true)
				{
					clickP[selectedPos].pawnMoved();
				}
				clickP[selectedPos].move(tile.x, tile.y);
				resetPotential();
				selectedPos = -1;
				return 3; //piece moved to an empty space. advance turn

			case 1:
				if (blkTurn)
				{
					white.erase(white.begin() + atkPos);
				}
				clickP[selectedPos].move(tile.x, tile.y);
				resetPotential();
				selectedPos = -1;
				return 4; //piece consumed and taken over position. advance turn

			case 2:
				if (!blkTurn)
				{
					black.erase(black.begin() + atkPos);
				}
				clickP[selectedPos].move(tile.x, tile.y);
				resetPotential();
				selectedPos = -1;
				return 4; //piece consumed and taken over position. advance turn

			default:
				break;
			}
			
		}
		
		
	}

	return -1;
}

vector<Piece> Game::getBlackPieces()
{
	return black;
}

vector<Piece> Game::getWhitePieces()
{
	return white;
}

int Game::getBL()
{
	//return bS;
	return black.size();
}

int Game::getWL()
{
	//return wS;
	return white.size();
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

vector<POINT> Game::getPotential()
{
	return potential;
}

void Game::resetPotential()
{
	potential.clear();
}

void Game::nextTurn()
{
	blkTurn = !blkTurn;
}

void Game::setPotential()
{
	Piece p = (blkTurn) ? black[selectedPos] : white[selectedPos];
	POINT a;
	if (p.getType() == "pawn")
	{
		if (p.isBlack())
		{
			a.x = p.getX();
			a.y = p.getY() + 1;
			if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
			{
				potential.push_back(a);
			}
			if (p.checkPawnFirst())
			{
				a.y = p.getY() + 2;
				if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
				{
					potential.push_back(a);
				}
				
			}
		}
		else
		{
			a.x = p.getX();
			a.y = p.getY() - 1;
			if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
			{
				potential.push_back(a);
			}
			if (p.checkPawnFirst())
			{
				a.y = p.getY() - 2;
				if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
				{
					potential.push_back(a);
				}
			}
		}
	}
	else if (p.getType() == "rook")
	{
		a.y = p.getY();
		for (int x = 0; x < 8; x++)
		{
			if (x != p.getX())
			{
				a.x = x;
				if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
				{
					potential.push_back(a);
				}
			}
		}
		a.x = p.getX();
		for (int y = 0; y < 8; y++)
		{
			if (y != p.getY())
			{
				a.y = y;
				if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
				{
					potential.push_back(a);
				}
			}
		}
	}
	else if (p.getType() == "knight")
	{
		a.x = p.getX() + 2;
		a.y = p.getY() + 1;
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}
		a.y = p.getY() - 1;
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}

		a.x = p.getX() - 2;
		a.y = p.getY() + 1;
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}
		a.y = p.getY() - 1;
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}

		a.y = p.getY() + 2;
		a.x = p.getX() + 1;
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}
		a.x = p.getX() - 1;
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}

		a.y = p.getY() - 2;
		a.x = p.getX() + 1;
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}
		a.x = p.getX() - 1;
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}
	}
	else if (p.getType() == "bishop")
	{
		for (int i = 1; i < 8; i++)
		{
			a.x = p.getX() + i;
			a.y = p.getY() + i;
			if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
			{
				potential.push_back(a);
			}

			a.x = p.getX() + i;
			a.y = p.getY() - i;
			if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
			{
				potential.push_back(a);
			}

			a.x = p.getX() - i;
			a.y = p.getY() + i;
			if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
			{
				potential.push_back(a);
			}

			a.x = p.getX() - i;
			a.y = p.getY() - i;
			if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
			{
				potential.push_back(a);
			}
		}
	}
	else if (p.getType() == "queen")
	{
		for (int i = 1; i < 8; i++)
		{
			a.x = p.getX() + i;
			a.y = p.getY() + i;
			if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
			{
				potential.push_back(a);
			}

			a.x = p.getX() + i;
			a.y = p.getY() - i;
			if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
			{
				potential.push_back(a);
			}

			a.x = p.getX() - i;
			a.y = p.getY() + i;
			if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
			{
				potential.push_back(a);
			}

			a.x = p.getX() - i;
			a.y = p.getY() - i;
			if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
			{
				potential.push_back(a);
			}
		}

		a.y = p.getY();
		for (int x = 0; x < 8; x++)
		{
			if (x != p.getX())
			{
				a.x = x;
				if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
				{
					potential.push_back(a);
				}
			}
		}
		a.x = p.getX();
		for (int y = 0; y < 8; y++)
		{
			if (y != p.getY())
			{
				a.y = y;
				if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
				{
					potential.push_back(a);
				}
			}
		}
	}
	else if (p.getType() == "king")
	{
		a.x = p.getX() + 1;
		a.y = p.getY() + 1;
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}

		a.x = p.getX() + 1;
		a.y = p.getY() - 1;
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}

		a.x = p.getX() - 1;
		a.y = p.getY() + 1;
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}

		a.x = p.getX() - 1;
		a.y = p.getY() - 1;
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}


		a.x = p.getX() + 1;
		a.y = p.getY();
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}

		a.x = p.getX() - 1;
		a.y = p.getY();
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}

		a.x = p.getX();
		a.y = p.getY() + 1;
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}

		a.x = p.getX();
		a.y = p.getY() - 1;
		if (!isBlocked(p.getX(), p.getY(), a.x, a.y))
		{
			potential.push_back(a);
		}
	}
}

bool Game::isBlocked(int x1, int y1, int x2, int y2)
{	//1 = current position | 2 = potential position
		int xDiff = x2 - x1; //positive right | negative left
		int yDiff = y2 - y1; //positive down | negative up
		int dir = 0;
		if (xDiff == 0 && yDiff > 0) //down
		{
			dir = 1;
		}
		else if (xDiff == 0 && yDiff < 0) //up
		{
			dir = 2;
		}
		else if (xDiff > 0 && yDiff == 0) //right
		{
			dir = 3;
		}
		else if (xDiff < 0 && yDiff == 0) //left
		{
			dir = 4;
		}
		else if (xDiff > 0 && yDiff > 0) //right down
		{
			dir = 5;
		}
		else if (xDiff > 0 && yDiff < 0) //right up
		{
			dir = 6;
		}
		else if (xDiff < 0 && yDiff > 0) //left down
		{
			dir = 7;
		}
		else if (xDiff < 0 && yDiff < 0) //left up
		{
			dir = 8;
		}
		
		for (Piece pp : black)
		{
			if (pp.getX() == x2 && pp.getY() == y2 && blkTurn)
			{
				return true;
			}
			int absx = pp.getX() - x1;
			int absy = pp.getY() - y1;
			switch (dir)
			{
			case 1:
				if (pp.getX() == x1 && pp.getY() > y1 && pp.getY() < y2)
				{
					return true;
				}
				break;
			case 2:
				if (pp.getX() == x1 && pp.getY() < y1 && pp.getY() > y2)
				{
					return true;
				}
				break;
			case 3:
				if (pp.getY() == y1 && pp.getX() > x1 && pp.getX() < x2)
				{
					return true;
				}
				break;
			case 4:
				if (pp.getY() == y1 && pp.getX() < x1 && pp.getX() > x2)
				{
					return true;
				}
				break;
			case 5:
				if (pp.getX() > x1 && pp.getY() > y1 && pp.getX() < x2 && pp.getY() < y2 && abs(absx) == abs(absy))
				{
					return true;
				}
				break;
			case 6:
				if (pp.getX() > x1 && pp.getY() < y1 && pp.getX() < x2 && pp.getY() > y2 && abs(absx) == abs(absy))
				{
					return true;
				}
				break;
			case 7:
				if (pp.getX() < x1 && pp.getY() > y1 && pp.getX() > x2 && pp.getY() < y2 && abs(absx) == abs(absy))
				{
					return true;
				}
				break;
			case 8:
				if (pp.getX() < x1 && pp.getY() < y1 && pp.getX() > x2 && pp.getY() > y2 && abs(absx) == abs(absy))
				{
					return true;
				}
				break;
			}
		}
		for (Piece pp : white)
		{
			if (pp.getX() == x2 && pp.getY() == y2 && !blkTurn)
			{
				return true;
			}
			int absx = pp.getX() - x1;
			int absy = pp.getY() - y1;
			switch (dir)
			{
			case 1:
				if (pp.getX() == x1 && pp.getY() > y1 && pp.getY() < y2)
				{
					return true;
				}
				break;
			case 2:
				if (pp.getX() == x1 && pp.getY() < y1 && pp.getY() > y2)
				{
					return true;
				}
				break;
			case 3:
				if (pp.getY() == y1 && pp.getX() > x1 && pp.getX() < x2)
				{
					return true;
				}
				break;
			case 4:
				if (pp.getY() == y1 && pp.getX() < x1 && pp.getX() > x2)
				{
					return true;
				}
				break;
			case 5:
				if (pp.getX() > x1 && pp.getY() > y1 && pp.getX() < x2 && pp.getY() < y2 && abs(absx) == abs(absy))
				{
					return true;
				}
				break;
			case 6:
				if (pp.getX() > x1 && pp.getY() < y1 && pp.getX() < x2 && pp.getY() > y2 && abs(absx) == abs(absy))
				{
					return true;
				}
				break;
			case 7:
				if (pp.getX() < x1 && pp.getY() > y1 && pp.getX() > x2 && pp.getY() < y2 && abs(absx) == abs(absy))
				{
					return true;
				}
				break;
			case 8:
				if (pp.getX() < x1 && pp.getY() < y1 && pp.getX() > x2 && pp.getY() > y2 && abs(absx) == abs(absy))
				{
					return true;
				}
				break;
			}
		}
	return false;
}

