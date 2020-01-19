#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include"EnemyManager.h"


class stageScene: public gameNode
{
private:
	playerManager* _pm;
	EnemyManager* _em;

public:
	stageScene() {}
	~stageScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

