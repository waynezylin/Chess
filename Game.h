#pragma once
#include "framework.h"
#include "Piece.h"

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

	POINT tile, prevTile;
	bool tileChanged;
	bool pieceChanged;

};

 