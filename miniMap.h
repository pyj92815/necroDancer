#pragma once
#include "gameNode.h"
#include "enemyManager.h"
#include "playerManager.h"

class miniMap : public gameNode
{
private:
	//tagTile								_minTiles[MINTILEX * MINTILEY];
	//vector<tagTile*>					_vMinTotalList;
	//vector<tagTile*>::iterator			_viMinTotalList;

	vector<tagTile*>					_vStageMap;
	vector<tagTile*>::iterator			_viStageMap;

	EnemyManager* _em;
	int _r;
	int _g;
	int _b;

public:
	miniMap();
	~miniMap();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void getStageMap(vector<tagTile*> stageMap) { _vStageMap = stageMap; }


};

