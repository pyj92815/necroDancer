#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include"EnemyManager.h"
#include "Beat.h"
#include "UImanager.h"

class bossStageScene;

class stageScene: public gameNode
{
private:
	playerManager* _pm;
	EnemyManager* _em;
	Beat* _beat;
	UImanager* _ui;
	tagTile _tiles[20 * 40];  // �޾ƿ;��ϴ� (Ÿ�� ���� ������ ����)
	bool _isLoad;
	bossStageScene* _bossStageScene;
public:
	stageScene() {}
	~stageScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void load();
	void bossStageSceneAddressLink(bossStageScene* bossStageScene) { _bossStageScene = bossStageScene; }
	player* getPlayerAddress() { return _pm->getPlayerInfo(); }
	UImanager* getUiAddress() { return _ui; }
};

