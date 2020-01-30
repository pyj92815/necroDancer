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

	_em->AddressLink(_pm->getPlayerInfo());

	_ui = new UImanager;
	_ui->init();

	_minimap = new miniMap;
	_minimap->init();

	_zOrder = new zOrder;
	_zOrder->init();

	//ZorderSetup();
	return S_OK;
}

void stageScene::release()
{
}

void stageScene::update()
{
	cout << 1 << endl;
	_pm->update();
	_em->update();
	BEATMANAGER->update();
	_ui->update();
	_zOrder->zOrderSetup(_pm->getPlayerInfo()->getPlayer().idx, _pm->getPlayerInfo()->getPlayer().idy, _tiles, _pm, _em);
	_zOrder->update();
	//ZorderSetup();
	//_zOrderVector = ZorderUpdate(_zOrderVector);
	stageCollision();
	setVision(PointMake(_pm->getPlayerInfo()->getPlayer().idx, _pm->getPlayerInfo()->getPlayer().idy), _pm->getPlayerInfo()->getPlayer().sight);
	_minimap->getStageMap(_vTotalList);
}

void stageScene::render()
{
	// 바닥 렌더 
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
				
			}

			if ((*_viTotalList)->trap != TRAP_NONE)
			{
				if ((*_viTotalList)->alphaValue <= 0)
				{
					IMAGEMANAGER->findImage("trapTiles")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->trapFrameX, (*_viTotalList)->trapFrameY);
				}
				continue;
			}
			else if ((*_viTotalList)->armor != A_NONE)
			{
				IMAGEMANAGER->findImage("armorTiles")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->armorFrameX, (*_viTotalList)->armorFrameY);
				continue;
			}
			else if ((*_viTotalList)->weapon != WP_NONE)
			{
				IMAGEMANAGER->findImage("weaponTiles")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->weaponFrameX, (*_viTotalList)->weaponFrameY);
				continue;
			}
			else if ((*_viTotalList)->stuff != ST_NONE)
			{
				IMAGEMANAGER->findImage("stuffTiles")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->stuffFrameX, (*_viTotalList)->stuffFrameY);
				continue;
			}

		}
		else continue;
	}
	// 이외의 렌더 
	for (_viTotalList = _vTotalList.begin(); _viTotalList != _vTotalList.end(); ++_viTotalList)
	{
		if ((*_viTotalList)->type == TYPE_NONE) continue;

		RECT temp;
		if (IntersectRect(&temp, &CAMERAMANAGER->getCamera_Rect(), &(*_viTotalList)->rc))
		{
			if ((*_viTotalList)->alphaValue <= 0)
			{
				if ((*_viTotalList)->type == TYPE_WALL)
				{
					IMAGEMANAGER->findImage("wallTiles")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top - 30, (*_viTotalList)->wallFrameX, (*_viTotalList)->wallFrameY);
					continue;
				}
			}
		}
	}
	_zOrder->render();
	//플레이어 렌더 
	/*pm->render();*/
	//몬스터 렌더 
	_em->render();

	//제트오더 랜더 
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
	//제트오더 랜더 

	EFFECTMANAGER->render(CAMERAMANAGER->getWorldDC());

	_pm->effectRender();
	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	//ENEMYMANAGER->render(getMemDC());
	BEATMANAGER->render();
	_ui->render();
	_minimap->render();
	//for (_viTotalList = _vTotalList.begin(); _viTotalList != _vTotalList.end(); ++_viTotalList)
	//{
	//	
	//}
	
}
//
//// 제트오더 사이즈 설정하기 
//void stageScene::ZorderSetup()
//{
//	_zOrderVector.clear();
//	int startX = _pm->getPlayerInfo()->getPlayer().idx;
//	int startY = _pm->getPlayerInfo()->getPlayer().idy - 10;
//	if (_pm->getPlayerInfo()->getPlayer().idx < 0) startX = 0;
//	if (_pm->getPlayerInfo()->getPlayer().idy - 10 < 0) startY = 0;
//
//	// 2n+ 1 개 만큼
//	for (int i = startY; i < startY + 21; i++)
//	{
//		for (int j = startX; j < startX + 1; j++)
//		{
//			if (i > TILEY) continue;
//			if (j > TILEX) continue;
//
//			tagClass* tile;
//			tile = new tagClass;
//			ZeroMemory(tile, sizeof(tile));
//			tile->player = NULL;
//			tile->enemy = NULL;
//			tile->tile = &_tiles[i * TILEX + j];
//			float* ins = new float;
//			*ins = (float)_tiles[i * TILEX + j].rc.bottom;
//			_zOrderVector.push_back(new zOrder(ins, tile));
//		}
//	}
//
//	tagClass* player;
//	player = new tagClass;
//	ZeroMemory(player, sizeof(player));
//	player->player = _pm;
//	player->enemy = NULL;
//	player->tile = NULL;
//	_zOrderVector.push_back(new zOrder(_pm->getPlayerY(), player));
//
//	//제트오더 
//	/*for (int i = 0; i < 400;++i)
//	{
//		tagClass* tile;
//		tile = new tagClass;
//		ZeroMemory(tile, sizeof(tile));
//		tile->player = NULL;
//		tile->enemy = NULL;
//		tile->tile = &_tiles[i];
//		float* ins = new float;
//		*ins = (float)_tiles[i].rc.bottom;
//		_zOrderVector.push_back(new zOrder(ins, tile));
//	}
//
//	tagClass* player;
//	player = new tagClass;
//	ZeroMemory(player, sizeof(player));
//	player = new tagClass;
//	player->player = _pm;
//	player->enemy = NULL;
//	player->tile = NULL;
//	_zOrderVector.push_back(new zOrder(_pm->getPlayerY(), player));*/
//
//
//}
//vector<zOrder*> stageScene::ZorderUpdate(vector<zOrder*> num)
//{
//	zOrder* instance = new zOrder();
//	for (int j = 0;j < num.size();j++)
//	{
//		for (int i = j + 1;i < num.size();i++)
//		{
//			if (*(num[j]->y) > * (num[i]->y))
//			{
//				if (num[i]->Object->player != NULL
//					&& num[i]->y +
//					(num[i]->Object->player->getPlayerInfo()->getPlayer().rc.top -
//						num[i]->Object->player->getPlayerInfo()->getPlayer().rc.bottom))
//				{
//					instance = num[j];
//					num[j] = num[i];
//					num[i] = instance;
//				}
//				else
//				{
//					instance = num[j];
//					num[j] = num[i];
//					num[i] = instance;
//				}
//			}
//		}
//	}
//
//	return num;
//}

void stageScene::stageCollision()
{
	_pm->getPlayerInfo()->setPlayerTile(_collision.collision_player_tile(&_vTotalList, _pm->getPlayerInfo()));
	_pm->getPlayerInfo()->setPlayerEnemyTile(_collision.collision_player_Enemy_tile(&_em->getVEnemy(), _pm->getPlayerInfo()));
}

void stageScene::setVision(POINT index, int sight)
{
	// 재귀함수 
	// 초기 예외처리 
	if (0 > index.x || 0 > index.y || index.x > TILEX || index.y > TILEY) return;
	if (sight <= 0) return;

	bool recursionContinue = true;  // 초기 조건값 
	recursionContinue &= (_tiles[index.y * TILEX + index.x].wall == W_NONE);  // 맞춰야 하는 조건 
	//if (_tiles[index.y * TILEX + index.x].type == TYPE_WALL) sight = sight - 3;	// 시야처리에 따른 값 조정할 예정 

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
	// 1. 벽 넘어서 까지 시야처리를 어떻게 해야할지 
	// 2. 알파블렌더가 렉에 원인인데 어떻게 할지
}

void stageScene::stageMapLoad()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("Loby_SaveFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);

	int i = 0;
	while (i < TILEX * TILEY)
	{
		// 타일의 타입이 NONE이 아니라면 벡터에 담는다.
		if (_tiles[i].type != TYPE_NONE)
		{
			_tiles[i].alphaValue = 255;
			_vTotalList.push_back(&_tiles[i]);
		}
		i++;
	}
}




