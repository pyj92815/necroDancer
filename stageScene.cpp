#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	_pm = new playerManager;
	_pm->init();

	_em = new EnemyManager;
	_em->init();

	return S_OK;
}

void stageScene::release()
{
}

void stageScene::update()
{
	_pm->update();
	_em->update();
}

void stageScene::render()
{
	_pm->render();
	_em->render();
	//ENEMYMANAGER->render(getMemDC());
}
