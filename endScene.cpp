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

	_video->init("credits_1.ogv",true);

	BEATMANAGER->AllStopMusic();
	SOUNDMANAGER->play("credit_music");

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
