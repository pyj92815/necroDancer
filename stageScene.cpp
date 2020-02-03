#include "stdafx.h"
#include "stageScene.h"
#include "bossStageScene.h"
#include "EnemyManager.h"

HRESULT stageScene::init()
{
	stageMapLoad(fileName);			 // 스테이지 맵 로드 

	// 만약 플레이어의 위치가 없으면 
	if (_playerIdx <0 || _playerIdy <0 || _playerIdx > TILEX || _playerIdy> TILEY)
	{
		_playerIdx = 10;
		_playerIdy = 10;
	}

	_pm = new playerManager;
	_pm->init(_playerIdx, _playerIdy);

	CAMERAMANAGER->set_CameraXY(_pm->getPlayerInfo()->getPlayer().x, _pm->getPlayerInfo()->getPlayer().y, true);  // 플레이어의 위치 셋팅 
	// Enemy
	_em = new EnemyManager;
	_em->init(_mEnemyPoint);
	_em->AddressLink(_pm->getPlayerInfo());

	_pm->getPlayerInfo()->collisionSettingBoss();
	//UI
	_ui = new UImanager;
	_ui->setPlayerInfo(_pm->getPlayerInfo()->PlayerAddress());
	_ui->init();
	//MiniMap
	_minimap = new miniMap;
	_minimap->init();
	_minimap->getEnemyPoint(_em);
	//Z-Order
	_zOrder = new zOrder;
	_zOrder->init();
	//시야처리 
	_floodFill = new visionFloodFill;
	_floodFill->init();

	_pm->getPlayerInfo()->setStage();

	TIMEMANAGER->setCountLoadingTimeSwitch(true);
	BEATMANAGER->AllStopMusic();
	BEATMANAGER->SetMusicID(1);

	IMAGEMANAGER->addImage("Shopkeeper", "image/ETC/Shopkeeper.bmp", 104, 104, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Shopkeeper_Shadow", "image/ETC/Shopkeeper_Shadow.bmp", 104, 104, true, RGB(255, 0, 255));
	return S_OK;
}

void stageScene::release()
{
	_vTotalList.clear(); // 맵 삭제
}

void stageScene::update()
{
	if (!OPTION->getplayerDie())
	{
		_pm->update();
		//enemy
		_em->setVtile(_vTotalList);
		_em->update();

		BEATMANAGER->update();
		//Z-order
		_zOrder->zOrderSetup(_pm->getPlayerInfo()->getPlayer().idx, _pm->getPlayerInfo()->getPlayer().idy, _tiles, _pm, _em);
		_zOrder->update();

		stageCollision();

		_floodFill->setVision(_tiles, _pm->getPlayerInfo()->getPlayer().idx, _pm->getPlayerInfo()->getPlayer().idy, _pm->getPlayerInfo()->getPlayer().sight);
		// 미니맵 
		_minimap->getStageMap(_vTotalList);
		_minimap->setPlayerXY(_pm->getPlayerInfo()->getPlayer().x, _pm->getPlayerInfo()->getPlayer().y);
		_minimap->getEnemyPoint(_em);
		// UI
		_ui->update();
		_ui->setInven(_pm->getPlayerInfo()->getVInven());
		
		nextPage(); // 다음 스테이지로 넘어가기 위한 값 
		tileOnOff();// 타일  
	}

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

			if ((*_viTotalList)->alphaValue <= 0)
			{
				if ((*_viTotalList)->terrain != TR_NONE)
				{
					IMAGEMANAGER->findImage("terrainTiles")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->terrainFrameX, (*_viTotalList)->terrainFrameY);
				}
				if ((*_viTotalList)->trap != TRAP_NONE)
				{
					IMAGEMANAGER->findImage("trapTiles")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->trapFrameX, (*_viTotalList)->trapFrameY);
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
			else
			{
				if ((*_viTotalList)->terrain != TR_NONE)
				{
					IMAGEMANAGER->findImage("terrainTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->terrainFrameX, (*_viTotalList)->terrainFrameY, (*_viTotalList)->alphaValue);
				}
				if ((*_viTotalList)->trap != TRAP_NONE)
				{
					IMAGEMANAGER->findImage("trapTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->trapFrameX, (*_viTotalList)->trapFrameY, (*_viTotalList)->alphaValue);
					continue;
				}
				else if ((*_viTotalList)->armor != A_NONE)
				{
					IMAGEMANAGER->findImage("armorTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->armorFrameX, (*_viTotalList)->armorFrameY, (*_viTotalList)->alphaValue);
					continue;
				}
				else if ((*_viTotalList)->weapon != WP_NONE)
				{
					IMAGEMANAGER->findImage("weaponTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->weaponFrameX, (*_viTotalList)->weaponFrameY, (*_viTotalList)->alphaValue);
					continue;
				}
				else if ((*_viTotalList)->stuff != ST_NONE)
				{
					IMAGEMANAGER->findImage("stuffTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top, (*_viTotalList)->stuffFrameX, (*_viTotalList)->stuffFrameY, (*_viTotalList)->alphaValue);
					continue;
				}
			}


		}
		else continue;
	}
	// 이외의 렌더 
	for (_viTotalList = _vTotalList.begin(); _viTotalList != _vTotalList.end(); ++_viTotalList)
	{
		if ((*_viTotalList)->type == TYPE_NONE) continue;
		if ((*_viTotalList)->type == TYPE_WALL)
		{
			RECT temp;
			if (IntersectRect(&temp, &CAMERAMANAGER->getCamera_Rect(), &(*_viTotalList)->rc))
			{
				if ((*_viTotalList)->alphaValue <= 0)
				{
					
					IMAGEMANAGER->findImage("wallTiles")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top - 30, (*_viTotalList)->wallFrameX, (*_viTotalList)->wallFrameY);
					continue;
				}
				else
				{
					IMAGEMANAGER->findImage("wallTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), (*_viTotalList)->rc.left, (*_viTotalList)->rc.top - 30, (*_viTotalList)->wallFrameX, (*_viTotalList)->wallFrameY, (*_viTotalList)->alphaValue);
					continue;
				}
			}
		}

		if ((*_viTotalList)->type == TYPE_CHARACTER)
		{
			if ((*_viTotalList)->character == CHAR_SHOPKEEPER)
			{
				if (!BEATMANAGER->Get_FindShopkeeperPos())
				{
					_tiles[BEATMANAGER->Get_ShopkeeperID().y * BEATMANAGER->Get_ShopkeeperID().x].XY.x = 1740;
					_tiles[BEATMANAGER->Get_ShopkeeperID().y * BEATMANAGER->Get_ShopkeeperID().x].XY.y = 1152;
					//BEATMANAGER->Set_ShopkeeperPos({ (_tiles[BEATMANAGER->Get_ShopkeeperID().y * BEATMANAGER->Get_ShopkeeperID().x].rc.right + _tiles[BEATMANAGER->Get_ShopkeeperID().y * BEATMANAGER->Get_ShopkeeperID().x].rc.left) / 2 ,
					//	(_tiles[BEATMANAGER->Get_ShopkeeperID().y * BEATMANAGER->Get_ShopkeeperID().x].rc.bottom + _tiles[BEATMANAGER->Get_ShopkeeperID().y * BEATMANAGER->Get_ShopkeeperID().x].rc.top) / 2 });
					BEATMANAGER->Set_ShopkeeperPos({ _tiles[BEATMANAGER->Get_ShopkeeperID().y * BEATMANAGER->Get_ShopkeeperID().x].XY.x,
						_tiles[BEATMANAGER->Get_ShopkeeperID().y * BEATMANAGER->Get_ShopkeeperID().x].XY.y });
					BEATMANAGER->Set_FindShopkeeperPos(true);
				}
				else
				{
					//RECT temp = RectMakeCenter(BEATMANAGER->Get_ShopkeeperPos().x, BEATMANAGER->Get_ShopkeeperPos().y, 52, 52);
					//Rectangle(CAMERAMANAGER->getWorldDC(), temp);
					IMAGEMANAGER->findImage("Shopkeeper")->render(CAMERAMANAGER->getWorldDC(), BEATMANAGER->Get_ShopkeeperPos().x - (IMAGEMANAGER->findImage("Shopkeeper")->getWidth() / 2), BEATMANAGER->Get_ShopkeeperPos().y - (IMAGEMANAGER->findImage("Shopkeeper")->getHeight() / 2));
				}
			}
		}
	}

	_zOrder->render();
	EFFECTMANAGER->render(CAMERAMANAGER->getWorldDC());
	_em->render();
	_pm->effectRender();
	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	BEATMANAGER->render();
	_ui->render();
	_minimap->render();
	OPTION->render(getMemDC());
}

void stageScene::stageCollision()
{
	_pm->getPlayerInfo()->setPlayerTile(_collision.collision_player_tile(&_vTotalList, _pm->getPlayerInfo()));
	_pm->getPlayerInfo()->setPlayerEnemyTile(_collision.collision_player_Enemy_tile(&_em->getVEnemy(), _pm->getPlayerInfo()));
}

void stageScene::nextPage()
{
	if (_bossIdx == _pm->getPlayerInfo()->getPlayer().idx && _bossIdy == _pm->getPlayerInfo()->getPlayer().idy)
	{
		_pm->getPlayerInfo()->setJump();
		SCENEMANAGER->changeScene("Boss");
	}
	if (_stageIdx == _pm->getPlayerInfo()->getPlayer().idx && _stageIdy == _pm->getPlayerInfo()->getPlayer().idy)
	{
		_vTotalList.clear();
		_mEnemyPoint.clear();
		fileName = "Stage_SaveFile.map";
		this->init();

		BEATMANAGER->AllStopMusic();
		BEATMANAGER->SetMusicID(3);
	}

}

//바닥 타일 값을 변하기 위한 함수 
void stageScene::tileOnOff()
{
	if (_pm->getPlayerInfo()->getCombo())
	{
		if (BEATMANAGER->getTurnOnOff())
		{
			_tileFirstX = 4;
			_tileFirstY = 2;

			_tileSecondX = 5;
			_tileSecondY = 2;
		}
		else
		{
			_tileFirstX = 5;
			_tileFirstY = 2;

			_tileSecondX = 4;
			_tileSecondY = 2;

		}

	}
	else
	{
		if (BEATMANAGER->getTurnOnOff())
		{
			_tileFirstX = 0;
			_tileFirstY = 1;

			_tileSecondX = 1;
			_tileSecondY = 1;
		}
		else
		{
			_tileFirstX = 1;
			_tileFirstY = 1;

			_tileSecondX = 0;
			_tileSecondY = 1;
		}

	}

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0;j < TILEX; ++j)
		{
			if (_tiles[i * TILEX + j].type == TYPE_NONE) continue;
			if (_tiles[i * TILEX + j].terrain != TR_BASIC_STAGE_TILE &&
				_tiles[i * TILEX + j].terrain != TR_BASIC_COMBO_TILE) continue;

			if (j % 2 == 0)
			{
				if (i % 2 == 1)
				{
					_tiles[i * TILEX + j].terrainFrameX = _tileFirstX;
					_tiles[i * TILEX + j].terrainFrameY = _tileFirstY;
				}
				else
				{
					_tiles[i * TILEX + j].terrainFrameX = _tileSecondX;
					_tiles[i * TILEX + j].terrainFrameY = _tileSecondY;
				}
			}
			else
			{
				if (i % 2 == 1)
				{
					_tiles[i * TILEX + j].terrainFrameX = _tileSecondX;
					_tiles[i * TILEX + j].terrainFrameY = _tileSecondY;
				}
				else
				{
					_tiles[i * TILEX + j].terrainFrameX = _tileFirstX;
					_tiles[i * TILEX + j].terrainFrameY = _tileFirstY;
				}
			}



		}
	}

}

void stageScene::stageMapLoad(const char* fileName)
{
	HANDLE file;
	DWORD read;

	file = CreateFile(fileName, GENERIC_READ, 0, NULL,
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
			case CHAR_SHOPKEEPER:
				if (!BEATMANAGER->Get_FindShopkeeperPos())
				{
					BEATMANAGER->Set_ShopkeeperID({ _tiles[i].idX, _tiles[i].idY });				}
				break;
			}
		}
		if (_tiles[i].type == TYPE_TERRAIN)
		{
			switch (_tiles[i].terrain)
			{
				case TR_SHOP:
					break;
				default:
					break;
			}
		}

		if (_tiles[i].terrain == TR_BOSS_STAIR)
		{
			_bossIdx = _tiles[i].idX;
			_bossIdy = _tiles[i].idY;
		}
		if (_tiles[i].terrain == TR_STAIR)
		{
			_stageIdx = _tiles[i].idX;
			_stageIdy = _tiles[i].idY;
		}
		// 타일의 타입이 NONE이 아니라면 벡터에 담는다.
		if (_tiles[i].type != TYPE_NONE)
		{
			_tiles[i].alphaValue = 255;
			_vTotalList.push_back(&_tiles[i]);
		}
		i++;
	}
}

