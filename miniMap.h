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

	vector<Enemy*>   _vEnemyTile;

	EnemyManager* _em;
	playerManager* _pm;

	int _r;
	int _g;
	int _b;

	float _playerX;
	float _playerY;

public:
	miniMap();
	~miniMap();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void getStageMap(vector<tagTile*> stageMap) { _vStageMap = stageMap; }
	void getEnemyPoint(EnemyManager* em) { _em = em; }
	void setEnemyXY(vector<Enemy*> vEnemy) { _vEnemyTile = vEnemy;	}
	void setPlayerXY(float x, float y) 
	{
		_playerX = x; 
		_playerY = y;
	}
};

