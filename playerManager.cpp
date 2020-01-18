#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init()
{
	// 바닥 테스트 
	IMAGEMANAGER->addFrameImage("floor", "./image/player/floor.bmp", 156, 104, 3, 2, true, RGB(255, 0, 255),true);
	_player = new player;
	_player->init(10,10,TESTTILESIZE, TESTTILESIZE);

	_ptt = new playerTestTile;
	_ptt->setPlayerAddressLink(_player);
	_ptt->init();

	_bossStageScene = new bossStageScene;				 // 보스 스테이지에서 플레이어 정보를 링크하기 위해 만들었음.
	_bossStageScene->setPlayerAddressLink(_player);		 // 보스 스테이지에서 플레이어 정보를 링크하기 위해 만들었음.
	
	return S_OK;
}

void playerManager::release()
{
	_player->release();
	_ptt->release();
}

void playerManager::update()
{
	_player->update();
	_ptt->update();
}

void playerManager::render()
{
	_ptt->render();
	_player->render();
}
