#pragma once
#include "gameNode.h"

class bossScene:public gameNode
{
public:
	bossScene();
	~bossScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

