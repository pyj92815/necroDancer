#pragma once
#include "gameNode.h"

class endScene:public gameNode
{
public:
	endScene();
	~endScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

