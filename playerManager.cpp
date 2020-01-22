#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init()
{
	// ¹Ù´Ú Å×½ºÆ® 
	IMAGEMANAGER->addFrameImage("floor", "./image/player/floor.bmp", 156, 104, 3, 2, true, RGB(255, 0, 255),true);
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
