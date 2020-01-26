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

	//_mZorder.insert(pair<float*, tagZorder*>(_pm->getPlayerY(), player));
	for (int i = 0; i < 400;++i)
	{
		tagClass* tile;
		tile = new tagClass;
		ZeroMemory(tile, sizeof(tile));
		tile->player = NULL;
		tile->enemy = NULL;
		tile->tile = &_tiles[i];
		
		//tile->y = (float*)tile->ZorderClass->tile->rc.bottom;
		//_vZorder.push_back(std::make_pair((float*)_tiles[i].rc.bottom , tile));
		float* ins = new float;
		*ins = (float)_tiles[i].rc.bottom;
		_zOrderVector.push_back(new zOrder(ins, tile));
	}

	//Á¦Æ®¿À´õ ÃÊ±â 
	tagClass* player;
	player = new tagClass;
	ZeroMemory(player, sizeof(player));
	player = new tagClass;
	//memset(player, 0, sizeof(player));
	player->player = _pm;
	player->enemy = NULL;
	player->tile = NULL;
	//_mZorder.insert(pair<float*, tagZorder*>(_pm->getPlayerY(), player));
	 //_mZorder.emplace(pair<tagClass*, float*>(player, (float*)_pm->getPlayerY()));
	_zOrderVector.push_back(new zOrder(_pm->getPlayerY(), player));
	
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
	_zOrderVector = ZorderUpdate(_zOrderVector);
}

void stageScene::render()
{
	////¶¥ ·»´õ
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
	////ÇÃ·¹ÀÌ¾î ·»´õ 
	//_pm->render();
	////¸ó½ºÅÍ ·»´õ 
	//_em->render();

	//Á¦Æ®¿À´õ ·£´õ 
	
	for (int i=0; i< _zOrderVector.size(); ++i)
	{
		if (_zOrderVector[i]->Object->tile != NULL)
		{
			if (_zOrderVector[i]->Object->tile->terrain != TR_NONE)
			{
				IMAGEMANAGER->findImage("terrainTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _zOrderVector[i]->Object->tile->rc.left, _zOrderVector[i]->Object->tile->rc.top, _zOrderVector[i]->Object->tile->terrainFrameX, _zOrderVector[i]->Object->tile->terrainFrameY, _zOrderVector[i]->Object->tile->alphaValue);
				
			}
			if (_zOrderVector[i]->Object->tile->wall != W_NONE)
			{
				IMAGEMANAGER->findImage("wallTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _zOrderVector[i]->Object->tile->rc.left, _zOrderVector[i]->Object->tile->rc.top, _zOrderVector[i]->Object->tile->wallFrameX, _zOrderVector[i]->Object->tile->wallFrameX, _zOrderVector[i]->Object->tile->alphaValue);	
			}
			if (_zOrderVector[i]->Object->tile->trap != TRAP_NONE)
			{
				IMAGEMANAGER->findImage("trapTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _zOrderVector[i]->Object->tile->rc.left, _zOrderVector[i]->Object->tile->rc.top, _zOrderVector[i]->Object->tile->trapFrameX, _zOrderVector[i]->Object->tile->trapFrameY,_zOrderVector[i]->Object->tile->alphaValue);
			}
			continue;
		}
		if (_zOrderVector[i]->Object->player != NULL)
		{
			_zOrderVector[i]->Object->player->render();
			continue;
		}
		if (_zOrderVector[i]->Object->enemy != NULL)
		{
			_zOrderVector[i]->Object->enemy->render();
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

vector<zOrder*> stageScene::ZorderUpdate(vector<zOrder*> num)
{
	zOrder* instance=new zOrder();
	for (int j = 0;j < num.size();j++) 
	{
		for (int i = j+1;i < num.size();i++)
		{
			if (*(num[j]->y) > *(num[i]->y))
			{
				if (num[i]->Object->player != NULL
					&&num[i]->y+
					(num[i]->Object->player->getPlayerInfo()->getPlayer().rc.top-
					num[i]->Object->player->getPlayerInfo()->getPlayer().rc.bottom))
				{
					instance = num[j];
					num[j] = num[i];
					num[i] = instance;
				}
				else
				{
					instance = num[j];
					num[j] = num[i];
					num[i] = instance;
				}
			}
		}
	}

	return num;
}

void stageScene::load()
{
	_isLoad = true;

	HANDLE file;
	DWORD read;

	file = CreateFile("SaveFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * 20 *20, &read, NULL);

	CloseHandle(file);
}




