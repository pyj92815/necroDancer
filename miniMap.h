#pragma once
#include "gameNode.h"
#include "EnemyManager.h"
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
	playerManager* _pm;


	int _r;
	int _g;
	int _b;
	const char* _imageName;

public:
	miniMap();
	~miniMap();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void getStageMap(vector<tagTile*> stageMap) { _vStageMap = stageMap; }
	void getEnemyPoint(EnemyManager* em) { _em = em; }
	void getPlayerPoint(playerManager* pm) { _pm = pm; }
};

