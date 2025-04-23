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
	vector<Piece> getBlackPieces();
	vector<Piece> getWhitePieces();
	int getBL();
	int getWL();
	void resetTile();
	bool checkTC();
	bool checkPC();
	void resetPC();
	POINT getPrevTile();
	vector<POINT> getPotential();
	void resetPotential();
	void nextTurn();

private:

	vector<Piece> white;
	vector<Piece> black;
	//int bS, wS;

	POINT tile, prevTile, cTile;
	bool tileChanged;
	bool pieceChanged;
	bool blkTurn;
	int selectedPos;
	vector<POINT> potential;

	void setPotential();

	bool isBlocked(int x1, int y1, int x2, int y2);
};

 