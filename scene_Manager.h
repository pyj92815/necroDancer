#pragma once
#include "gameNode.h"
#include "introScene.h"
#include "loadingScene.h"
#include "stageScene.h"
#include "bossScene.h"
#include "endScene.h"
#include "bossStageScene.h" // 보스 스테이지 

class scene_Manager:public gameNode
{
private:
	introScene* _intro;
	stageScene* _stage;
	endScene* _end;
	bossStageScene* _boss;

public:
	scene_Manager();
	~scene_Manager();

	HRESULT init();
	void release();
	void update();
	void render();

};

