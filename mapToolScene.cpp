#include "stdafx.h"
#include "mapToolScene.h"

mapToolScene::mapToolScene()
{
}

mapToolScene::~mapToolScene()
{
}

HRESULT mapToolScene::init()
{
	_mapTool = new mapTool;
	_mapTool->init();

	return S_OK;
}

void mapToolScene::release()
{
}

void mapToolScene::update()
{
	_mapTool->update();
}

void mapToolScene::render()
{
	_mapTool->render();
}
