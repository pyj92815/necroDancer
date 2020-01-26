#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "tile.h"
#include <list>

class player;

#define TESTTILENUMX (WINSIZEX / TESTTILESIZE)
#define TESTTILENUMY (WINSIZEY / TESTTILESIZE)

class playerTestTile : public gameNode
{
private:
	vector<tile*>			 _vTiles;
	vector<tile*>::iterator _viTiles;

	player* _player;
	
	int _sight;
public:
	playerTestTile() {}
	~playerTestTile() {}

	HRESULT init();
	void release();
	void update();
	void render();
	void findSight();
	void setPlayerAddressLink(player* player) { _player = player; }
};

