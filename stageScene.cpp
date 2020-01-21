#include "stdafx.h"
#include "stageScene.h"

HRESULT stageScene::init()
{
	_pm = new playerManager;
	_pm->init();

	_em = new EnemyManager;
	_em->init();

	_beat = new Beat;
	_beat->init();

	load();

	_ui = new UImanager;
	_ui->init();

	return S_OK;
}

void stageScene::release()
{
}

void stageScene::update()
{
	_pm->update();
	_em->update();

	if (KEYMANAGER->isToggleKey('V'))
	{
		_beat->update();
	}
	_ui->update();
}

void stageScene::render()
{
	if (_isLoad)
	{
		for (int i = 0;i < 800; i++)
		{
			if (_tiles[i].terrain != TR_NONE)
			{
				IMAGEMANAGER->findImage("terrainTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY, _tiles[i].alphaValue);
			}
			if (_tiles[i].wall != W_NONE)
			{
				IMAGEMANAGER->findImage("wallTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].wallFrameX, _tiles[i].wallFrameY, _tiles[i].alphaValue);
			}
			if (_tiles[i].trap != TRAP_NONE)
			{
				IMAGEMANAGER->findImage("trapTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].trapFrameX, _tiles[i].trapFrameY, _tiles[i].alphaValue);
			}
		}
	}
	_pm->render();
	_em->render();
	
	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	if (KEYMANAGER->isToggleKey('V'))
	{
		_beat->render();
	}
	//ENEMYMANAGER->render(getMemDC());
	_ui->render();
}

void stageScene::load()
{
	_isLoad = true;

	HANDLE file;
	DWORD read;

	file = CreateFile("SaveFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * 20 * 40, &read, NULL);
	//맵을 불로온 직후 타일의 속성을 매겨준다

	CloseHandle(file);
}

