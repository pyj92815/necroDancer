#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "EnemyManager.h"
#include "bossStageScene.h"

class playGround : public gameNode
{
private:
	playerManager* _pm;
	EnemyManager* _em;
	bossStageScene* _bss;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	playGround();
	~playGround();
};

