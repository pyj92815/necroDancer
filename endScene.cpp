#include "stdafx.h"
#include "endScene.h"

endScene::endScene()
{
}

endScene::~endScene()
{
}

HRESULT endScene::init()
{
	_video = new video;
	_video->init("ending-credit.ogv",true);
	return S_OK;
}

void endScene::release()
{
}

void endScene::update()
{
	_video->update();
}

void endScene::render()
{
	_video->render();
}
