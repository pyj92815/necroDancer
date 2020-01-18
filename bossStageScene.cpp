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
	_vTotalList = _bossStageTile->getTotalTile();	// 보스 스테이지에 쓰일 타일을 만들고 복사한다.

	_deathMetal = new deathMetal;
	_deathMetal->init("데스메탈", 5, 5, TESTTILESIZE, TESTTILESIZE);

	return S_OK;
}

void bossStageScene::release()
{
}

void bossStageScene::update()
{
	_bossStageTile->setTotalTile(_vTotalList);		// 맵 타일 갱신 함수

	_deathMetal->update();
}

void bossStageScene::render()
{
	_bossStageTile->render();			// 맵 타일 출력

	_deathMetal->render();
}
