#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init()
{
	// ¹Ù´Ú Å×½ºÆ® 
	IMAGEMANAGER->addFrameImage("floor", "./image/player/floor.bmp", 78, 52, 3, 2, true, RGB(255, 0, 255));
	_player = new player;
	_player->init(10,10,TESTTILESIZE, TESTTILESIZE);

	_ptt = new playerTestTile;
	_ptt->init();

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
