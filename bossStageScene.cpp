#include "stdafx.h"
#include "bossStageScene.h"

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

	// bossStageMap_Load();	// 이후에 영주맵 받아와서 실행 해봐야함 (경로 수정 해야함)
	_player = new player;
	_player->init(10,10,52,52);

	return S_OK;
}

void bossStageScene::release()
{
}

void bossStageScene::update()
{
	//_bossStageTile->setTotalTile(_vTotalList);		// 맵 타일 갱신 함수

	_deathMetal->update();
	_player->update();
}

void bossStageScene::render()
{
	//_bossStageTile->render();			// 맵 타일 출력

	_deathMetal->render();
	_player->render();
}

void bossStageScene::bossStageMap_Load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("boss_Stage.map", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _BSTList, sizeof(tile) * TESTTILESIZE * TESTTILESIZE, &read, NULL);

	CloseHandle(file);
}
