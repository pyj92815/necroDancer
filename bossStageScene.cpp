#include "stdafx.h"
#include "bossStageScene.h"
#include "player.h"

bossStageScene::bossStageScene()
{
}

bossStageScene::~bossStageScene()
{
}

HRESULT bossStageScene::init()
{
	_bossStageTile = new bossStageTestTile;
	_bossStageTile->init();
	_vTotalList = _bossStageTile->getTotalTile();	// ���� ���������� ���� Ÿ���� ����� �����Ѵ�.

	_deathMetal = new deathMetal;
	_deathMetal->init("������Ż", 5, 5, TESTTILESIZE, TESTTILESIZE);

	return S_OK;
}

void bossStageScene::release()
{
}

void bossStageScene::update()
{
	_bossStageTile->setTotalTile(_vTotalList);		// �� Ÿ�� ���� �Լ�

	_deathMetal->update();
}

void bossStageScene::render()
{
	_bossStageTile->render();			// �� Ÿ�� ���

	_deathMetal->render();
}
