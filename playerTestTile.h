#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "tile.h"

#define TESTTILENUMX (WINSIZEX / TESTTILESIZE)
#define TESTTILENUMY (WINSIZEY / TESTTILESIZE)

class playerTestTile : public gameNode
{
private:
	vector<tile*>			 _vTiles;
	vector<tile*>::iterator _viTiles;


public:
	playerTestTile() {}
	~playerTestTile() {}

	HRESULT init();
	void release();
	void update();
	void render();

};

