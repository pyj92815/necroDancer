#pragma once
#include "gameNode.h"
#include "tile.h"

#define TILEWIDTH 32
#define TILEHEIGHT 32

#define TILENUMX (WINSIZEX / TILEWIDTH)
#define TILENUMY (WINSIZEY / TILEHEIGHT)

class aStarTest : public gameNode
{
private:
	vector<tile*>			_vTotalList;
	vector<tile*>::iterator _viTotalList;

	vector<tile*>				_vOpenList;
	vector<tile*>::iterator		_viOpenList;

	vector<tile*>				_vClosedList;
	vector<tile*>::iterator		_viClosedList;

	tile* _startTile;
	tile* _endTile;
	tile* _currentTile;

	//요건 나중에 테스트할때 쓸것.
	bool _start;
	int _count;

public:
	aStarTest();
	~aStarTest();

	HRESULT init();
	
	void setTiles();

	vector<tile*> addOpenList(tile* currentTile);

	void pathFinder(tile* currentTile);

	void release();
	void update();
	void render();
};

