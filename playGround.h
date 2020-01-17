#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include"EnemyManager.h"

class playGround : public gameNode
{
private:
	playerManager* _pm;
	EnemyManager* _em;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	playGround();
	~playGround();
};

