#pragma once
#include "gameNode.h"
#include "introScene.h"
#include "loadingScene.h"
#include "stageScene.h"
#include "bossScene.h"
#include "endScene.h"

class scene_Manager:public gameNode
{
private:
	introScene* _intro;
	stageScene* _stage;
	endScene* _end;
	bossScene* _boss;

public:
	scene_Manager();
	~scene_Manager();

	HRESULT init();
	void release();
	void update();
	void render();

};

