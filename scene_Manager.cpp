#include "stdafx.h"
#include "scene_Manager.h"


scene_Manager::scene_Manager()
{
}

scene_Manager::~scene_Manager()
{
}

HRESULT scene_Manager::init()
{

	SCENEMANAGER->addScene("Intro", _intro = new introScene);
	SCENEMANAGER->addScene("Loading", new loadingScene);
	SCENEMANAGER->addScene("Stage", _stage = new stageScene);
	SCENEMANAGER->addScene("End", _end = new endScene);
	SCENEMANAGER->addScene("Boss", _boss = new bossStageScene);

	SCENEMANAGER->addScene("MAPTOOL", new mapTool);

	SCENEMANAGER->changeScene("Intro");

	return S_OK;
}

void scene_Manager::release()
{
}

void scene_Manager::update()
{
	SCENEMANAGER->update();
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("Intro");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		SCENEMANAGER->changeScene("Stage");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F4))
	{
		SCENEMANAGER->changeScene("Boss");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		SCENEMANAGER->changeScene("Loading");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		SCENEMANAGER->changeScene("MAPTOOL");
	}


}

void scene_Manager::render()
{
	SCENEMANAGER->render();
}
