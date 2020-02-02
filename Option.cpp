#include "stdafx.h"
#include "Option.h"

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

	// 재시작 이미지
	//IMAGEMANAGER->addImage("options_control_restart", "image/UI/Option/options_control_restart.bmp", 188, 36, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("options_control_restart_selected", "image/UI/Option/options_control_restart_selected.bmp", 188, 36, true, RGB(255, 0, 255));
	//
	//
	//IMAGEMANAGER->addImage("game_duration", "image/UI/Option/game_duration.bmp", 100, 24, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("game_duration_selected", "image/UI/Option/game_duration_selected.bmp", 100, 24, true, RGB(255, 0, 255));

	// 두개 
	IMAGEMANAGER->addImage("game_runsummary", "image/UI/Option/game_runsummary.bmp", 204, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("options_quit_lobby2", "image/UI/Option/options_quit_lobby2.bmp", 144, 50, 1,2,true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("options_control_restart2", "image/UI/Option/options_control_restart2.bmp", 131, 50, 1, 2, true,RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("options_exitgame2", "image/UI/Option/options_exitgame2.bmp",94, 48,1, 2, true, RGB(255, 0, 255));

	isOpen = false;
	_isDead = false;
	keyId = _isDeadDirection = 0;

	for (int i = 0; i < 3;i++)
	{
		_frameY[i] = 0;
	}
	return S_OK;
}

void Option::release()
{
}

void Option::update()
{
	playerDirection();

	if (_isDead)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_isDeadDirection--;
			SOUNDMANAGER->play("sfx_ui_select_up");
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_isDeadDirection++;
			SOUNDMANAGER->play("sfx_ui_select_down");
		}


		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			SOUNDMANAGER->play("sfx_ui_start");
			if (_isDeadDirection == 0)
			{
				
			}
			else if (_isDeadDirection == 1)
			{
				SCENEMANAGER->changeScene("Stage");
			}
			else if (_isDeadDirection == 2)
			{
				PostQuitMessage(0);
			}
		}
	}
}

void Option::render(HDC hdc)
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

		IMAGEMANAGER->findImage("overlay_BG")->render(hdc, 0, 0);
		IMAGEMANAGER->findImage("options_pause")->render(hdc, WINSIZEX_HALF - 124, 50);
		IMAGEMANAGER->findImage("options_button_back")->render(hdc, WINSIZEX_HALF - 46, 200);
		IMAGEMANAGER->findImage("options_options")->render(hdc, WINSIZEX_HALF - 22, WINSIZEY / 2);
		IMAGEMANAGER->findImage("options_exitgame")->render(hdc, WINSIZEX_HALF - 47, 400);
		IMAGEMANAGER->findImage("Brightness")->alphaRender(hdc, 0);
	}

	if (_isDead)
	{
		IMAGEMANAGER->findImage("overlay_BG")->render(hdc, 0, 0);

		IMAGEMANAGER->findImage("game_runsummary")->render(hdc, WINSIZEX_HALF - 124, 50);

		IMAGEMANAGER->findImage("options_control_restart2")->frameRender(hdc,WINSIZEX_HALF - 75, 200, 0, _frameY[0]);

		IMAGEMANAGER->findImage("options_quit_lobby2")->frameRender(hdc, WINSIZEX_HALF - 80, 300,0, _frameY[1]);  // 게임 요약 

		IMAGEMANAGER->findImage("options_exitgame2")->frameRender(hdc, WINSIZEX_HALF - 55,400, 0, _frameY[2]);
	}
}

void Option::playerDirection()
{
	if (_isDeadDirection < 0) _isDeadDirection = 0;
	if (_isDeadDirection >= 3) _isDeadDirection = 2;

	for (int i = 0;i < 3;i++)
	{
		if (_isDeadDirection == i)  // 0 1 2 
		{
			_frameY[_isDeadDirection] = 1;
		}
		else
		{
			_frameY[i] = 0;
		}
	}
}
