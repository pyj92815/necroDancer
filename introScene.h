#pragma once
#include "gameNode.h"
#include "video.h"

class introScene:public gameNode
{
private:
	video* _video;

public:
	introScene();
	~introScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

