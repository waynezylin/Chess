#include "Game.h"

void Game::update()
{
	
}

bool Game::updateTile(POINT mouse)
{
	bool diff = false;
	mouse.x = trunc(mouse.x / 100);
	mouse.y = trunc(mouse.y / 100);
	if (tile.x != mouse.x)
	{
		tile.x = mouse.x;
		diff = true;
	}
	if (tile.y = mouse.y)
	{
		tile.y = mouse.y;
		diff = true;
	}
	return diff;
}

POINT Game::getSelectedTile()
{
	return tile;
}

int Game::click()
{

}