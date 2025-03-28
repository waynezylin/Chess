#pragma once
#include "framework.h"
#include "Piece.h"

using namespace std;

class Game
{

public:
	void update();
	bool updateTile(POINT mouse);
	POINT getSelectedTile();
	int click();


private:

	Piece white[16];
	Piece black[16];

	POINT tile;



};

 