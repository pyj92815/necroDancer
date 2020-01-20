#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include"EnemyManager.h"
#include "Beat.h"


class stageScene: public gameNode
{
private:
	playerManager* _pm;
	EnemyManager* _em;
	Beat* _beat;

public:
	stageScene() {}
	~stageScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

