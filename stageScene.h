#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include"EnemyManager.h"
//#include "Beat.h"
#include "UImanager.h"


class stageScene: public gameNode
{
private:
	playerManager* _pm;
	EnemyManager* _em;
	//Beat* _beat;
	UImanager* _ui;

	tagTile _tiles[20 * 40];  // 받아와야하는 (타일 갯수 수정할 예정)
	bool _isLoad;
public:
	stageScene() {}
	~stageScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void load();
};

