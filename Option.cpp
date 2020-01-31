#include "stdafx.h"
#include "Option.h"
#include "gameNode.h"


Option::Option()
{
}

Option::~Option()
{
}


HRESULT Option::init()
{
	IMAGEMANAGER->addImage("Brightness", "image/UI/Option/Brightness.bmp", WINSIZEX, WINSIZEY, 0, RGB(255, 255, 255), 1);
	IMAGEMANAGER->addImage("overlay_BG", "image/UI/Option/overlay_black.bmp", WINSIZEX, WINSIZEY, 0, RGB(255, 255, 255), 0);

	IMAGEMANAGER->addImage("options_audiooptions", "image/UI/Option/options_audiooptions.bmp", 116, 24, 1, RGB(255, 0, 255), 0);
	IMAGEMANAGER->addImage("options_audiooptions_selected", "image/UI/Option/options_audiooptions_selected.bmp", 116, 24, 1, RGB(255, 0, 255), 0);

	IMAGEMANAGER->addImage("options_bright", "image/UI/Option/options_bright.bmp", 44, 24, 1, RGB(255, 0, 255), 0);
	IMAGEMANAGER->addImage("options_bright_selected", "image/UI/Option/options_bright_selected.bmp", 44, 24, 1, RGB(255, 0, 255), 0);

	IMAGEMANAGER->addImage("options_button_back", "image/UI/Option/options_button_back.bmp", 92, 24, 1, RGB(255, 0, 255), 0);
	IMAGEMANAGER->addImage("options_button_back_selected", "image/UI/Option/options_button_back_selected.bmp", 92, 24, 1, RGB(255, 0, 255), 0);

	IMAGEMANAGER->addImage("options_exitgame", "image/UI/Option/options_exitgame.bmp", 94, 24, 1, RGB(255, 0, 255), 0);
	IMAGEMANAGER->addImage("options_exitgame_selected", "image/UI/Option/options_exitgame_selected.bmp", 94, 24, 1, RGB(255, 0, 255), 0);

	IMAGEMANAGER->addImage("options_graphicaloptions", "image/UI/Option/options_graphicaloptions.bmp", 116, 24, 1, RGB(255, 0, 255), 0);
	IMAGEMANAGER->addImage("options_graphicaloptions_selected", "image/UI/Option/options_graphicaloptions_selected.bmp", 116, 24, 1, RGB(255, 0, 255), 0);

	IMAGEMANAGER->addImage("options_musicvolume", "image/UI/Option/options_musicvolume.bmp", 96, 24, 1, RGB(255, 0, 255), 0);
	IMAGEMANAGER->addImage("options_musicvolume_selected", "image/UI/Option/options_musicvolume_selected.bmp", 96, 24, 1, RGB(255, 0, 255), 0);

	IMAGEMANAGER->addImage("options_options", "image/UI/Option/options_options.bmp", 44, 24, 1, RGB(255, 0, 255), 0);
	IMAGEMANAGER->addImage("options_options_selected", "image/UI/Option/options_options_selected.bmp", 44, 24, 1, RGB(255, 0, 255), 0);

	IMAGEMANAGER->addImage("options_pause", "image/UI/Option/options_pause.bmp", 248, 48, 1, RGB(255, 0, 255), 0);

	IMAGEMANAGER->addImage("options_quit_lobby", "image/UI/Option/options_quit_lobby.bmp", 138, 24, 1, RGB(255, 0, 255), 0);
	IMAGEMANAGER->addImage("options_quit_lobby_selected", "image/UI/Option/options_quit_lobby_selected.bmp", 138, 24, 1, RGB(255, 0, 255), 0);

	IMAGEMANAGER->addImage("options_soundvolume", "image/UI/Option/options_quit_lobby.bmp", 118, 24, 1, RGB(255, 0, 255), 0);
	IMAGEMANAGER->addImage("options_soundvolume_selected", "image/UI/Option/options_quit_lobby_selected.bmp", 118, 24, 1, RGB(255, 0, 255), 0);

	isOpen = false;
	keyId = 0;
	return S_OK;
}

void Option::release()
{
}

void Option::update()
{

}

void Option::render()
{
	if (isOpen)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{

		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{

		}
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{

		}

		IMAGEMANAGER->findImage("overlay_BG")->render(_backBuffer->getMemDC(), 0, 0);
		IMAGEMANAGER->findImage("options_pause")->render(_backBuffer->getMemDC(), WINSIZEX_HALF - 124, 50);
		IMAGEMANAGER->findImage("options_button_back")->render(_backBuffer->getMemDC(), WINSIZEX_HALF - 46, 200);
		IMAGEMANAGER->findImage("options_options")->render(_backBuffer->getMemDC(), WINSIZEX_HALF - 22, WINSIZEY / 2);
		IMAGEMANAGER->findImage("options_exitgame")->render(_backBuffer->getMemDC(), WINSIZEX_HALF - 47, 400);
		IMAGEMANAGER->findImage("Brightness")->alphaRender(_backBuffer->getMemDC(), 0);
	}
}