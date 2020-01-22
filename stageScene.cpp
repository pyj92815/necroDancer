#include "stdafx.h"
#include "stageScene.h"
#include "bossStageScene.h"

HRESULT stageScene::init()
{
	_pm = new playerManager;
	_pm->init();

	_em = new EnemyManager;
	_em->init();

	//_beat = new Beat;
	//_beat->init();

	load();

	_ui = new UImanager;
	_ui->init();

	//제트오더 초기 
	tagZorder* player;
	player = new tagZorder;
	ZeroMemory(player, sizeof(player));
	//memset(player, 0, sizeof(player));
	player->player = _pm;
	player->enemy = NULL;
	player->tile = NULL;
	_mZorder.insert(pair<float*,tagZorder*>(_pm->getPlayerY(), player));
	for (int i = 0; i < 800;++i)
	{
		tagZorder* tile;
		tile = new tagZorder;
		ZeroMemory(tile, sizeof(tile));
		tile->tile = &_tiles[i];
		tile->player = NULL;
		tile->enemy = NULL;
		_mZorder.insert(pair<float*, tagZorder*>((float*)_tiles[i].rc.bottom, tile));
	}
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
		BEATMANAGER->update();
	}
	_ui->update();

}

void stageScene::render()
{
	////땅 렌더
	//if (_isLoad)
	//{
	//	for (int i = 0;i < 800; i++)
	//	{
	//		if (_tiles[i].terrain != TR_NONE)
	//		{
	//			IMAGEMANAGER->findImage("terrainTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY, _tiles[i].alphaValue);
	//		}
	//		if (_tiles[i].wall != W_NONE)
	//		{
	//			IMAGEMANAGER->findImage("wallTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].wallFrameX, _tiles[i].wallFrameY, _tiles[i].alphaValue);
	//		}
	//		if (_tiles[i].trap != TRAP_NONE)
	//		{
	//			IMAGEMANAGER->findImage("trapTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].trapFrameX, _tiles[i].trapFrameY, _tiles[i].alphaValue);
	//		}
	//	}
	//}
	////플레이어 렌더 
	//_pm->render();
	////몬스터 렌더 
	//_em->render();

	//제트오더 랜더 
	for (_miZorder = _mZorder.begin(); _miZorder != _mZorder.end(); ++_miZorder)
	{
		//문제는 조금 렉걸림 제트오더로 출력 
		if (_miZorder->second->tile != NULL)
		{
			if (_miZorder->second->tile->terrain != TR_NONE)
			{
				IMAGEMANAGER->findImage("terrainTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _miZorder->second->tile->rc.left, _miZorder->second->tile->rc.top, _miZorder->second->tile->terrainFrameX, _miZorder->second->tile->terrainFrameY, _miZorder->second->tile->alphaValue);
				continue;
			}
			if (_miZorder->second->tile->wall != W_NONE)
			{
				IMAGEMANAGER->findImage("terrainTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _miZorder->second->tile->rc.left, _miZorder->second->tile->rc.top, _miZorder->second->tile->terrainFrameX, _miZorder->second->tile->terrainFrameY, _miZorder->second->tile->alphaValue);
				continue;
			}
			if (_miZorder->second->tile->trap != TRAP_NONE)
			{
				IMAGEMANAGER->findImage("trapTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _miZorder->second->tile->rc.left, _miZorder->second->tile->rc.top, _miZorder->second->tile->trapFrameX, _miZorder->second->tile->trapFrameY, _miZorder->second->tile->alphaValue);
				continue;
			}
		}
		if (_miZorder->second->player != NULL)
		{
			_miZorder->second->player->render();
			continue;
		}
		if (_miZorder->second->enemy != NULL)
		{
			_miZorder->second->enemy->render();
			continue;
		}	
	}
	
	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	
	if (KEYMANAGER->isToggleKey('V'))
	{
		BEATMANAGER->render();
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

