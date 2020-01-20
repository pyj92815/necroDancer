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
	_vTotalList = _bossStageTile->getTotalTile();	// ���� ���������� ���� Ÿ���� ����� �����Ѵ�.

	_deathMetal = new deathMetal;
	_deathMetal->init("������Ż", 5, 5, TESTTILESIZE, TESTTILESIZE);

	// bossStageMap_Load();	// ���Ŀ� ���ָ� �޾ƿͼ� ���� �غ����� (��� ���� �ؾ���)
	_player = new player;
	_player->init(10,10,52,52);

	return S_OK;
}

void bossStageScene::release()
{
}

void bossStageScene::update()
{
	//_bossStageTile->setTotalTile(_vTotalList);		// �� Ÿ�� ���� �Լ�

	_deathMetal->update();
	_player->update();
}

void bossStageScene::render()
{
	//_bossStageTile->render();			// �� Ÿ�� ���

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
