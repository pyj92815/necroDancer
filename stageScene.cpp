#include "stdafx.h"
#include "stageScene.h"
#include "bossStageScene.h"

HRESULT stageScene::init()
{
	stageMapLoad();

	_pm = new playerManager;
	_pm->init();

	_em = new EnemyManager;
	_em->init();

	_ui = new UImanager;
	_ui->init();


	ZorderSetup();
	return S_OK;
}

void stageScene::release()
{
}

void stageScene::update()
{
	_pm->update();
	_em->update();
	BEATMANAGER->update();
	_ui->update();
	ZorderSetup();
	_zOrderVector = ZorderUpdate(_zOrderVector);
	stageCollision();
	setVision(PointMake(_pm->getPlayerInfo()->getPlayer().idx, _pm->getPlayerInfo()->getPlayer().idy), _pm->getPlayerInfo()->getPlayer().sight);
}

void stageScene::render()
{
	// �ٴ� ���� 
	for (_viTotalList = _vTotalList.begin(); _viTotalList != _vTotalList.end(); ++_viTotalList)
	{
		RECT temp;
		if (IntersectRect(&temp, &CAMERAMANAGER->getCamera_Rect(), &(*_viTotalList)->rc))
		{
			if ((*_viTotalList)->type == TYPE_NONE) continue;

			if ((*_viTotalList)->terrain != TR_NONE)
			{
				if ((*_viTotalList)->alphaValue <= 0)
				{
					IMAGEMANAGER->findImage("terrainTiles")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->terrainFrameX, (*_viTotalList)->terrainFrameY);
				}
				else
				{
					//IMAGEMANAGER->findImage("terrainTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->terrainFrameX, (*_viTotalList)->terrainFrameY, (*_viTotalList)->alphaValue);
				}
				continue;
			}
		}
	}
	//// �̿��� ���� 
	//for (_viTotalList = _vTotalList.begin(); _viTotalList != _vTotalList.end(); ++_viTotalList)
	//{
	//	if ((*_viTotalList)->type == TYPE_NONE) continue;
	//	if ((*_viTotalList)->alphaValue <= 0)
	//	{
	//		if ((*_viTotalList)->wall != W_NONE)
	//		{
	//			IMAGEMANAGER->findImage("wallTiles")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->wallFrameX, (*_viTotalList)->wallFrameY);
	//			continue;
	//		}
	//		if ((*_viTotalList)->trap != TRAP_NONE)
	//		{
	//			IMAGEMANAGER->findImage("trapTiles")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->trapFrameX, (*_viTotalList)->trapFrameY);
	//			continue;
	//		}
	//	}
	//	else
	//	{
	//		if ((*_viTotalList)->wall != W_NONE)
	//		{
	//			IMAGEMANAGER->findImage("wallTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->wallFrameX, (*_viTotalList)->wallFrameY, (*_viTotalList)->alphaValue);
	//			continue;
	//		}
	//		if ((*_viTotalList)->trap != TRAP_NONE)
	//		{
	//			IMAGEMANAGER->findImage("trapTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->trapFrameX, (*_viTotalList)->trapFrameY, (*_viTotalList)->alphaValue);
	//			continue;
	//		}
	//	}
	//}

	//�÷��̾� ���� 
	/*pm->render();*/
	//���� ���� 
	_em->render();

	//��Ʈ���� ���� 
	//for (int i = 0; i < _zOrderVector.size(); ++i)
	//{
	//	if (_zOrderVector[i]->Object->tile != NULL)
	//	{
	//		if (_zOrderVector[i]->Object->tile->terrain != TR_NONE)
	//		{
	//			IMAGEMANAGER->findImage("terrainTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _zOrderVector[i]->Object->tile->rc.left, _zOrderVector[i]->Object->tile->rc.top, _zOrderVector[i]->Object->tile->terrainFrameX, _zOrderVector[i]->Object->tile->terrainFrameY, _zOrderVector[i]->Object->tile->alphaValue);
	//		}
	//	}
	//}
	//��Ʈ���� ���� 
	for (int i = 0; i < _zOrderVector.size(); ++i)
	{
		if (_zOrderVector[i]->Object->tile != NULL)
		{
			if (_zOrderVector[i]->Object->tile->alphaValue <= 0)
			{
				if (_zOrderVector[i]->Object->tile->wall != W_NONE)
				{
					IMAGEMANAGER->findImage("wallTiles")->frameRender(CAMERAMANAGER->getWorldDC(), _zOrderVector[i]->Object->tile->rc.left, _zOrderVector[i]->Object->tile->rc.top - 30, _zOrderVector[i]->Object->tile->wallFrameX, _zOrderVector[i]->Object->tile->wallFrameY);
				}
				if (_zOrderVector[i]->Object->tile->trap != TRAP_NONE)
				{
					IMAGEMANAGER->findImage("trapTiles")->frameRender(CAMERAMANAGER->getWorldDC(), _zOrderVector[i]->Object->tile->rc.left, _zOrderVector[i]->Object->tile->rc.top, _zOrderVector[i]->Object->tile->trapFrameX, _zOrderVector[i]->Object->tile->trapFrameY);
				}

			}
	/*		else
			{
				if (_zOrderVector[i]->Object->tile->wall != W_NONE)
				{
					IMAGEMANAGER->findImage("wallTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _zOrderVector[i]->Object->tile->rc.left, _zOrderVector[i]->Object->tile->rc.top - 30, _zOrderVector[i]->Object->tile->wallFrameX, _zOrderVector[i]->Object->tile->wallFrameY, _zOrderVector[i]->Object->tile->alphaValue);
				}
				if (_zOrderVector[i]->Object->tile->trap != TRAP_NONE)
				{
					IMAGEMANAGER->findImage("trapTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), _zOrderVector[i]->Object->tile->rc.left, _zOrderVector[i]->Object->tile->rc.top, _zOrderVector[i]->Object->tile->trapFrameX, _zOrderVector[i]->Object->tile->trapFrameY, _zOrderVector[i]->Object->tile->alphaValue);
				}
			}*/
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
	EFFECTMANAGER->render(CAMERAMANAGER->getWorldDC());
	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);

	//ENEMYMANAGER->render(getMemDC());
	BEATMANAGER->render();
	_ui->render();
}

// ��Ʈ���� ������ �����ϱ� 
void stageScene::ZorderSetup()
{
	_zOrderVector.clear();
	int startX = _pm->getPlayerInfo()->getPlayer().idx - 15;
	int startY = _pm->getPlayerInfo()->getPlayer().idy - 10;
	if (_pm->getPlayerInfo()->getPlayer().idx - 15 < 0) startX = 0;
	if (_pm->getPlayerInfo()->getPlayer().idy - 10 < 0) startY = 0;

	// 2n+ 1 �� ��ŭ
	for (int i = startY; i < startY + 21; i++)
	{
		for (int j = startX; j < startX + 31; j++)
		{
			if (i > TILEY) continue;
			if (j > TILEX) continue;

			tagClass* tile;
			tile = new tagClass;
			ZeroMemory(tile, sizeof(tile));
			tile->player = NULL;
			tile->enemy = NULL;
			tile->tile = &_tiles[i * TILEX + j];
			float* ins = new float;
			*ins = (float)_tiles[i * TILEX + j].rc.bottom;
			_zOrderVector.push_back(new zOrder(ins, tile));
		}
	}

	tagClass* player;
	player = new tagClass;
	ZeroMemory(player, sizeof(player));
	player->player = _pm;
	player->enemy = NULL;
	player->tile = NULL;
	_zOrderVector.push_back(new zOrder(_pm->getPlayerY(), player));

	//��Ʈ���� 
	/*for (int i = 0; i < 400;++i)
	{
		tagClass* tile;
		tile = new tagClass;
		ZeroMemory(tile, sizeof(tile));
		tile->player = NULL;
		tile->enemy = NULL;
		tile->tile = &_tiles[i];
		float* ins = new float;
		*ins = (float)_tiles[i].rc.bottom;
		_zOrderVector.push_back(new zOrder(ins, tile));
	}

	tagClass* player;
	player = new tagClass;
	ZeroMemory(player, sizeof(player));
	player = new tagClass;
	player->player = _pm;
	player->enemy = NULL;
	player->tile = NULL;
	_zOrderVector.push_back(new zOrder(_pm->getPlayerY(), player));*/


}
vector<zOrder*> stageScene::ZorderUpdate(vector<zOrder*> num)
{
	zOrder* instance = new zOrder();
	for (int j = 0;j < num.size();j++)
	{
		for (int i = j + 1;i < num.size();i++)
		{
			if (*(num[j]->y) > * (num[i]->y))
			{
				if (num[i]->Object->player != NULL
					&& num[i]->y +
					(num[i]->Object->player->getPlayerInfo()->getPlayer().rc.top -
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

void stageScene::stageCollision()
{
	_pm->getPlayerInfo()->setPlayerTile(_collision.collision_player_tile(&_vTotalList, _pm->getPlayerInfo()));
}

void stageScene::setVision(POINT index, int sight)
{
	// ����Լ� 
	// �ʱ� ����ó�� 
	if (0 > index.x || 0 > index.y || index.x > TILEX || index.y > TILEY) return;
	if (sight <= 0) return;

	bool recursionContinue = true;  // �ʱ� ���ǰ� 
	//recursionContinue &= (_tiles[index.y * TILEX + index.x].wall == W_NONE);  // ����� �ϴ� ���� 
	if (_tiles[index.y * TILEX + index.x].wall != W_NONE) sight = sight - 3;	// �þ�ó���� ���� �� ������ ���� 

	if (recursionContinue)
	{
		_tiles[index.y * TILEX + index.x].alphaValue = 0;
		_tiles[index.y * TILEX + index.x].alphaEyesight = true;
		setVision(PointMake(index.x, index.y - 1), sight - 1);
		setVision(PointMake(index.x, index.y + 1), sight - 1);
		setVision(PointMake(index.x - 1, index.y), sight - 1);
		setVision(PointMake(index.x + 1, index.y), sight - 1);

	}
	else _tiles[index.y * TILEX + index.x].alphaValue = 0;
	// 1. �� �Ѿ ���� �þ�ó���� ��� �ؾ����� 
	// 2. ���ĺ����� ���� �����ε� ��� ����
}

void stageScene::stageMapLoad()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("Stage_SaveFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);

	int i = 0;
	while (i < TILEX * TILEY)
	{
		// Ÿ���� Ÿ���� NONE�� �ƴ϶�� ���Ϳ� ��´�.
		if (_tiles[i].type != TYPE_NONE)
		{
			_tiles[i].alphaValue = 255;
			_vTotalList.push_back(&_tiles[i]);
		}
		i++;
	}
}




