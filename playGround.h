#pragma once
#include "gameNode.h"
#include "scene_Manager.h"
#include "video.h"


class playGround : public gameNode
{
private:
	scene_Manager* _sm;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

