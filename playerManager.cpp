#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init()
{
	_player = new player;
	_player->init();
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
