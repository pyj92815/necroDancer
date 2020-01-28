#include "stdafx.h"
#include "playerManager.h"
#include "bossStageScene.h"
HRESULT playerManager::init()
{
	_player = new player;
	_player->init(10,10,TESTTILESIZE, TESTTILESIZE);
	BEATMANAGER->setPlayerAddressLink(_player);
	return S_OK;
}

void playerManager::release()
{
	_player->release();
}

void playerManager::update()
{
	_player->update();
}

void playerManager::render()
{
	_player->render();
}
