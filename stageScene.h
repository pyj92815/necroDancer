#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include"EnemyManager.h"
//#include "Beat.h"
#include "UImanager.h"

class bossStageScene;

struct tagClass
{
	tagTile* tile;
	playerManager* player;
	Enemy* enemy;
};
struct zOrder
{
	float* y;
	tagClass* Object;

	zOrder(float* y, tagClass* Object)
	{
		this->y = y;
		this->Object = Object;
	};
	zOrder() { ; }
};
class stageScene: public gameNode
{
private:
	playerManager* _pm;
	EnemyManager* _em;
	//Beat* _beat;
	UImanager* _ui;
	tagTile _tiles[20 * 40];  // 받아와야하는 (타일 갯수 수정할 예정)
	bool _isLoad;
	bossStageScene* _bossStageScene;

	map<tagClass*, float>					_mZorder;
	map<tagClass*, float>::iterator		_miZorder;

	vector<pair<float, tagClass*>> 				_vZorder;
	vector<pair<float, tagClass*>>::iterator	   _viZorder;

	vector<zOrder*> _zOrderVector;

public:
	stageScene() {}
	~stageScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	vector<zOrder*>ZorderUpdate(vector<zOrder*>  num);
	void load();
	void bossStageSceneAddressLink(bossStageScene* bossStageScene) { _bossStageScene = bossStageScene; }
	player* getPlayerAddress() { return _pm->getPlayerInfo(); }
	UImanager* getUiAddress() { return _ui; }
};

