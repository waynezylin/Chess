#pragma once
#include "framework.h"
#include "Piece.h"
#include <vector>

using namespace std;

class Game
{

public:
	Game();
	void update();
	bool updateTile(POINT mouse);
	POINT getSelectedTile();
	int click();
	Piece* getBlackPieces();
	Piece* getWhitePieces();
	int getBL();
	int getWL();
	void resetTile();
	bool checkTC();
	bool checkPC();
	void resetPC();
	POINT getPrevTile();

private:

	Piece white[16];
	Piece black[16];
	int bS, wS;

	POINT tile, prevTile, cTile;
	bool tileChanged;
	bool pieceChanged;
	bool blkTurn;
	int selectedPos;
	vector<POINT> potential;

	void setPotential();
};

 