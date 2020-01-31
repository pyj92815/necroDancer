#include "stdafx.h"
#include "playerManager.h"
#include "bossStageScene.h"
HRESULT playerManager::init(int idx,int idy)
{
	_player = new player;
	_player->init(idx,idy,TESTTILESIZE, TESTTILESIZE);
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

void playerManager::effectRender()
{
	_player->effectRender();
}
