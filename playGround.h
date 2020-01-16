#pragma once
#include "gameNode.h"
#include "playerManager.h"


class playGround : public gameNode
{
private:
	playerManager* _pm;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	playGround();
	~playGround();
};

