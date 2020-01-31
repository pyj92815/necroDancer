#pragma once
#include "gameNode.h"
#include "video.h"

class endScene:public gameNode
{
private:
	video* _video;

public:
	endScene();
	~endScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

