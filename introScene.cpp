#include "stdafx.h"
#include "introScene.h"

introScene::introScene()
{
}

introScene::~introScene()
{
}

HRESULT introScene::init()
{
	// Å³¶§
	BEATMANAGER->AllStopMusic();
	SOUNDMANAGER->play("Intro");

	_video = new video;
	_video->init("intro.avi");
	return S_OK;
}

void introScene::release()
{
	_video->release();
}

void introScene::update()
{
	_video->update();
}

void introScene::render()
{
	_video->render();
}
