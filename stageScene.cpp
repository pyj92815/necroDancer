#include "stdafx.h"
#include "stageScene.h"
#include "bossStageScene.h"

HRESULT stageScene::init()
{
	stageMapLoad();

	if (_playerIdx <0 || _playerIdy <0 ||_playerIdx > TILEX || _playerIdy> TILEY)
	{
		_playerIdx = 10;
		_playerIdy = 10;
	}
	_pm = new playerManager;
	_pm->init(_playerIdx,_playerIdy);
	CAMERAMANAGER->set_CameraXY(_pm->getPlayerInfo()->getPlayer().x, _pm->getPlayerInfo()->getPlayer().y, true);
	
	
	_em = new EnemyManager;
	_em->init(_mEnemyPoint);

	_em->AddressLink(_pm->getPlayerInfo());
	_pm->getPlayerInfo()->collisionSettingBoss();

	_ui = new UImanager;
	_ui->setPlayerInfo(_pm->getPlayerInfo()->PlayerAddress());
	_ui->init();
	
	_minimap = new miniMap;
	_minimap->init();
	
	_minimap->getEnemyPoint(_em);
	
	_zOrder = new zOrder;
	_zOrder->init();

	_floodFill = new visionFloodFill;
	_floodFill->init();


	_pm->getPlayerInfo()->setStage();

	//ZorderSetup();
	return S_OK;
}

void stageScene::release()
{
}

void stageScene::update()
{
	//if(OPTION->CheckOptionOpen)
	_pm->update();
	_em->update();
	BEATMANAGER->update();
	_ui->update();
	_zOrder->zOrderSetup(_pm->getPlayerInfo()->getPlayer().idx, _pm->getPlayerInfo()->getPlayer().idy, _tiles, _pm, _em);
	_zOrder->update();
	//ZorderSetup();
	//_zOrderVector = ZorderUpdate(_zOrderVector);
	stageCollision();
	//setVision(PointMake(_pm->getPlayerInfo()->getPlayer().idx, _pm->getPlayerInfo()->getPlayer().idy), _pm->getPlayerInfo()->getPlayer().sight);

	_floodFill->setVision(_tiles, _pm->getPlayerInfo()->getPlayer().idx, _pm->getPlayerInfo()->getPlayer().idy, _pm->getPlayerInfo()->getPlayer().sight);
	setVision(PointMake(_pm->getPlayerInfo()->getPlayer().idx, _pm->getPlayerInfo()->getPlayer().idy), _pm->getPlayerInfo()->getPlayer().sight);
	_minimap->getStageMap(_vTotalList);
	_minimap->getPlayerPoint(_pm);
	_ui->setInven(_pm->getPlayerInfo()->getVInven());
	
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
	// �̿��� ���� 
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
	//�÷��̾� ���� 
	/*pm->render();*/
	//���� ���� 


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
	EFFECTMANAGER->render(CAMERAMANAGER->getWorldDC());
	_em->render();
	_pm->effectRender();
	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	//ENEMYMANAGER->render(getMemDC());
	BEATMANAGER->render();
	_ui->render();
	_minimap->render();
}
//
//// ��Ʈ���� ������ �����ϱ� 
//void stageScene::ZorderSetup()
//{
//	_zOrderVector.clear();
//	int startX = _pm->getPlayerInfo()->getPlayer().idx;
//	int startY = _pm->getPlayerInfo()->getPlayer().idy - 10;
//	if (_pm->getPlayerInfo()->getPlayer().idx < 0) startX = 0;
//	if (_pm->getPlayerInfo()->getPlayer().idy - 10 < 0) startY = 0;
//
//	// 2n+ 1 �� ��ŭ
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
//	//��Ʈ���� 
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
	// ����Լ� 
	// �ʱ� ����ó�� 
	if (0 > index.x || 0 > index.y || index.x > TILEX || index.y > TILEY) return;
	if (sight <= 0) return;

	bool recursionContinue = true;  // �ʱ� ���ǰ� 
	recursionContinue &= (_tiles[index.y * TILEX + index.x].wall == W_NONE);  // ����� �ϴ� ���� 
	//if (_tiles[index.y * TILEX + index.x].type == TYPE_WALL) sight = sight - 3;	// �þ�ó���� ���� �� ������ ���� 

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

	file = CreateFile("Loby_SaveFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);

	int i = 0;
	while (i < TILEX * TILEY)
	{
		if (_tiles[i].type == TYPE_CHARACTER)
		{
			switch (_tiles[i].character)
			{
			case CHAR_PLAYER:
				_playerIdx = _tiles[i].idX;
				_playerIdy = _tiles[i].idY;
				break;
			case  CHAR_BAT:
				_mEnemyPoint.insert(pair<CHARACTER, POINT>(CHAR_BAT, PointMake(_tiles[i].idX, _tiles[i].idY)));
				break;
			case CHAR_SLIME_BLUE:
				_mEnemyPoint.insert(pair<CHARACTER, POINT>(CHAR_SLIME_BLUE, PointMake(_tiles[i].idX, _tiles[i].idY)));
				break;
			case CHAR_SLIME_ORANGE:
				_mEnemyPoint.insert(pair<CHARACTER, POINT>(CHAR_SLIME_ORANGE, PointMake(_tiles[i].idX, _tiles[i].idY)));
				break;
			case CHAR_GHOST:
				_mEnemyPoint.insert(pair<CHARACTER, POINT>(CHAR_GHOST, PointMake(_tiles[i].idX, _tiles[i].idY)));
				break;
			case  CHAR_WRAITH:
				_mEnemyPoint.insert(pair<CHARACTER, POINT>(CHAR_WRAITH, PointMake(_tiles[i].idX, _tiles[i].idY)));
				break;
			case CHAR_SKELETON:
				_mEnemyPoint.insert(pair<CHARACTER, POINT>(CHAR_SKELETON, PointMake(_tiles[i].idX, _tiles[i].idY)));
				break;
			case CHAR_SKELETON_YELLOW:
				_mEnemyPoint.insert(pair<CHARACTER, POINT>(CHAR_SKELETON_YELLOW, PointMake(_tiles[i].idX, _tiles[i].idY)));
				break;
			case CHAR_ZOMBIE:
				_mEnemyPoint.insert(pair<CHARACTER, POINT>(CHAR_ZOMBIE, PointMake(_tiles[i].idX, _tiles[i].idY)));
				break;
			case CHAR_MINO:
				_mEnemyPoint.insert(pair<CHARACTER, POINT>(CHAR_MINO, PointMake(_tiles[i].idX, _tiles[i].idY)));
				break;
			case CHAR_DRAGON:
				_mEnemyPoint.insert(pair<CHARACTER, POINT>(CHAR_DRAGON, PointMake(_tiles[i].idX, _tiles[i].idY)));
				break;
			}
		}
		// Ÿ���� Ÿ���� NONE�� �ƴ϶�� ���Ϳ� ��´�.
		if (_tiles[i].type != TYPE_NONE)
		{
			_tiles[i].alphaValue = 255;
			_vTotalList.push_back(&_tiles[i]);
		}
		i++;
	}
}

