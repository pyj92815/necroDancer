#include "stdafx.h"
#include "bossStageScene.h"

#include "player.h"
#include "UImanager.h"

bossStageScene::bossStageScene()
{
}

bossStageScene::~bossStageScene()
{
}

HRESULT bossStageScene::init()
{
	_stageScene->release();
	_addBossImage->add_BossImage();
	_addBossImage->add_BossAnimation();

	_addSlaveImage->add_SlaveImage();
	_addSlaveImage->add_SlaveAnimation();

	_player = _stageScene->getPlayerAddress();								// 플레이어 링크
	_player->collisionSettingStage();
	_ui = _stageScene->getUiAddress();										// ui 링크

	bossStageMap_Load();													// 파일에 있는 보스 스테이지 맵을 불러와서 벡터로 저장해준다.

	playerPos_Setting();													// 보스 스테이지에 입장 한 플레이어의 위치를 생성 위치를 잡아준다.

	distanceCheck = false;
	introSound = false;

	_sm = new slaveManager;
	_sm->init();

	start_Slave_Create();													// 기본으로 보스방에 있는 슬레이브 생성

	_zOrder = new zOrder;
	_zOrder->init();

	_floodFill = new visionFloodFill;
	_floodFill->init();

	// 보스 등장 씬에 관련 변수 초기화
	bossSceneSetting();

	_player->setBossStage(); // 보스스테이지 락훈 추가 
	BEATMANAGER->init();
	BEATMANAGER->AllStopMusic();
	return S_OK;
}

void bossStageScene::release()
{
}

void bossStageScene::update()
{


	// 플레이어 인덱스 출력
	cout << _player->getPlayer().idx << ", " << _player->getPlayer().idy << endl;
	endScene();
	// 보스 등장 씬이 끝나면 플레이가 가능하다.
	bossSceneStart();

	if (_scene_Starter.isOpen)
	{
		_player->update();

		// 플레이어가 문을 지났는지 연산
		bossSceneDoorOpen();
		BEATMANAGER->SetMusicID(5);

		// 플레이어가 보스방문을 열고 안으로 들어오면 이 값이 true로 바뀐다.
		if (_scene_Starter.isDoorOpen)
		{
			if (!_deathMetal->getBoss_Dead()) _deathMetal->update();
			if (!_deathMetal->getBoss_Dead())  boss_PhaseMove();	// 보스 페이즈 연산
			_ui->update();
			_sm->update();

			// 플레이어가 보스 근처에 있는지 없는지를 찾아준다. (쉐도우 벗기)
			if (!_deathMetal->getBoss_Dead())  closePlayer(_player, _deathMetal);

			// 플레이어가 슬레이브 근처에 있는지 없는지를 찾아준다.	(쉐도우 벗기)
			searchSlave(_sm->get_SlaveList(), _player);

			// 보스 움직임 연산
			if (!_deathMetal->getBoss_Dead())  boss_Move_Player();

			// 슬레이브 움직임 연산
			slave_Move_Player();

			//cout << _deathMetal->getBoss_Index().x << ": y:" << _deathMetal->getBoss_Index().y << endl;

			// 슬레이브 테스트용 소환
			if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
			{
				_sm->create_Slave(SLAVE_TYPE::SLAVE_BAT, _deathMetal->getBoss_Index().x - 1, _deathMetal->getBoss_Index().y - 1);
				//_sm->create_Slave(SLAVE_TYPE::SLAVE_BAT, _deathMetal->getBoss_Index().x + 1, _deathMetal->getBoss_Index().y - 1);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
			{
				_sm->create_Slave(SLAVE_TYPE::SLAVE_GHOST, _deathMetal->getBoss_Index().x - 1, _deathMetal->getBoss_Index().y - 1);
				_sm->create_Slave(SLAVE_TYPE::SLAVE_GHOST, _deathMetal->getBoss_Index().x + 1, _deathMetal->getBoss_Index().y - 1);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD3))
			{
				_sm->create_Slave(SLAVE_TYPE::SLAVE_SKELETON, _deathMetal->getBoss_Index().x - 1, _deathMetal->getBoss_Index().y - 1);
				_sm->create_Slave(SLAVE_TYPE::SLAVE_SKELETON, _deathMetal->getBoss_Index().x + 1, _deathMetal->getBoss_Index().y - 1);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
			{
				_sm->create_Slave(SLAVE_TYPE::SLAVE_SKELETON_YELLOW, _deathMetal->getBoss_Index().x - 1, _deathMetal->getBoss_Index().y - 1);
				_sm->create_Slave(SLAVE_TYPE::SLAVE_SKELETON_YELLOW, _deathMetal->getBoss_Index().x + 1, _deathMetal->getBoss_Index().y - 1);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
			{
				_deathMetal->setBoss_Shield_Hit_True();
				
			}

			if (KEYMANAGER->isOnceKeyDown('O'))
			{
				_deathMetal->setBoss_HP_Hit();
			}
		}

		BEATMANAGER->update();

		if (_deathMetal->getBoss_HP() <= 0)
		{
			bossClear();	// 보스 체력이 0이라면 클리어라는 뜻이다.
			_deathMetal->setBoss_Index(0, 0);
			_deathMetal->settingBossPos(0, 0, TILESIZE, TILESIZE);
		}



	}
	_player->setDeathMetal(_collision.collision_player_Metal_tile(_deathMetal, _player));
	_player->setSlaveTile(_collision.collision_player_slave_tile(&_sm->get_SlaveList(), _player));


	_zOrder->zOrderSetup(_player->getPlayer().idx, _player->getPlayer().idy, _tiles, _player, _sm, _deathMetal);
	_zOrder->update();
	_floodFill->setVision(_tiles, _player->getPlayer().idx, _player->getPlayer().idy, _player->getPlayer().sight);
	_player->setPlayerTile(_collision.collision_player_tile(&_vTotalList, _player));
}

void bossStageScene::render()
{
	// 맵을 출력해준다.
	if (_vTotalList.size() > 0)
	{
		for (_viTotalList = _vTotalList.begin(); _viTotalList != _vTotalList.end(); _viTotalList++)
		{
			// 타일의 타입이 TYPE_NONE이 아니라면 그려준다.
			if ((*_viTotalList)->type != TYPE_NONE)
			{
				// 타일의 속성에 따라 이미지를 뿌린다.		
				RECT temp;
				if (IntersectRect(&temp, &CAMERAMANAGER->getCamera_Rect(), &(*_viTotalList)->rc))
				{
					findTileImage();

				}
			}

		}
	}

	// 보스와 플레이어의 랜드 순서를 찾는다.
	//z_Order_Player_Boss();

	_sm->render();

	_zOrder->render();
	_player->effectRender();

	// 보스가 근접 공격을 했을때 이펙트를 그려준다. (size가 0 이상이라면)
	if (_vEffect.size() > 0 && !_deathMetal->getBoss_Dead())	boss_Base_Attack_Render();

	// 월드이미지를 뿌려준다.
	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);

	// UI 출력
	_ui->render();

	// 테스트 비트 출력 토글

	if (_scene_Starter.isOpen)
	{
		BEATMANAGER->render();
	}

	bossSceneRender();
}

void bossStageScene::bossStageMap_Load()
{
	// 보스 스테이지 맵을 불러와서 
	// _tiles에 담는다.
	HANDLE file;
	DWORD read;

	file = CreateFile("Boss_SaveFile.map", GENERIC_READ, 0, NULL,
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
			_tiles[i].alphaEyesight = false;

			if (_tiles[i].character == CHAR_BOSS)
			{
				_deathMetal = new deathMetal;
				_deathMetal->init("데스메탈", _tiles[i].idX, _tiles[i].idY, TESTTILESIZE, TESTTILESIZE);		// 임시로 데스메탈을 해당 위치에 배치했다.
			}

			if (_tiles[i].character == CHAR_PLAYER)
			{
				_player->PlayerAddress()->idx = _tiles[i].idX;
				_player->PlayerAddress()->idy = _tiles[i].idY;
			}

			if (_tiles[i].terrain == TR_STAIR)
			{
				_endX = _tiles[i].idX;
				_endY = _tiles[i].idY;
			}
			_vTotalList.push_back(&_tiles[i]);
		}

		i++;
	}


}

void bossStageScene::findTileImage()
{
	if ((*_viTotalList)->alphaValue <= 0)
	{
		// 지형이 NONE이 아니라면 출력
		if ((*_viTotalList)->terrain != TR_NONE)
		{
			//	TR_BASIC_STAGE_TILE, TR_BASIC_COMBO_TILE,
			//	TR_BOSS_STAGE_TILE, TR_BOSS_COMBO_TILE,
			//	TR_STAIR, TR_SHOP,
			//	TR_NONE,
			//	TR_END,
			//	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER
			IMAGEMANAGER->frameRender("terrainTiles", CAMERAMANAGER->getWorldDC(),
				(*_viTotalList)->rc.left, (*_viTotalList)->rc.top,
				(*_viTotalList)->terrainFrameX, (*_viTotalList)->terrainFrameY);
		}

		// 벽이 NONE이 아니라면 출력
		if ((*_viTotalList)->wall != W_NONE)
		{
			//	W_WALL, W_ITEM_WALL, W_WALL2, W_SHOP_WALL,
			//	W_END_WALL, W_BOSS_WALL,
			//	W_DOOR, W_TORCH, W_FIRE_WALL,
			//	W_NONE
			IMAGEMANAGER->frameRender("wallTiles", CAMERAMANAGER->getWorldDC(),
				(*_viTotalList)->rc.left, (*_viTotalList)->rc.top - 30,
				(*_viTotalList)->wallFrameX, (*_viTotalList)->wallFrameY);
		}

		// 함정이 NONE이 아니라면 출력
		if ((*_viTotalList)->trap != TRAP_NONE)
		{
			//	TRAP_FAST_BEAT, TRAP_SLOW_BEAT, TRAP_MUTE,
			//	TRAP_LT_JUMP, TRAP_T_JUMP, TRAP_RT_JUMP,
			//	TRAP_L_JUMP, TRAP_R_JUMP,
			//	TRAP_LB_JUMP, TRAP_B_JUMP, TRAP_RB_JUMP,
			//	TRAP_CONFUSE,
			//	TRAP_BOMB,
			//	TRAP_NIDDLE,
			//	TRAP_SHADOW, TRAP_NIDDLE_SHADOW,
			//	TRAP_NONE
			IMAGEMANAGER->frameRender("trapTiles", CAMERAMANAGER->getWorldDC(),
				(*_viTotalList)->rc.left, (*_viTotalList)->rc.top,
				(*_viTotalList)->trapFrameX, (*_viTotalList)->trapFrameY);
		}
	}
	else
	{
		// 지형이 NONE이 아니라면 출력
		if ((*_viTotalList)->terrain != TR_NONE)
		{
			//	TR_BASIC_STAGE_TILE, TR_BASIC_COMBO_TILE,
			//	TR_BOSS_STAGE_TILE, TR_BOSS_COMBO_TILE,
			//	TR_STAIR, TR_SHOP,
			//	TR_NONE,
			//	TR_END,
			//	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER
			IMAGEMANAGER->findImage("terrainTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(),
				(*_viTotalList)->rc.left, (*_viTotalList)->rc.top,
				(*_viTotalList)->terrainFrameX, (*_viTotalList)->terrainFrameY, (*_viTotalList)->alphaValue);
		}

		// 벽이 NONE이 아니라면 출력
		if ((*_viTotalList)->wall != W_NONE)
		{
			//	W_WALL, W_ITEM_WALL, W_WALL2, W_SHOP_WALL,
			//	W_END_WALL, W_BOSS_WALL,
			//	W_DOOR, W_TORCH, W_FIRE_WALL,
			//	W_NONE
			IMAGEMANAGER->findImage("wallTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(),
				(*_viTotalList)->rc.left, (*_viTotalList)->rc.top - 30,
				(*_viTotalList)->wallFrameX, (*_viTotalList)->wallFrameY, (*_viTotalList)->alphaValue);
		}

		// 함정이 NONE이 아니라면 출력
		if ((*_viTotalList)->trap != TRAP_NONE)
		{
			//	TRAP_FAST_BEAT, TRAP_SLOW_BEAT, TRAP_MUTE,
			//	TRAP_LT_JUMP, TRAP_T_JUMP, TRAP_RT_JUMP,
			//	TRAP_L_JUMP, TRAP_R_JUMP,
			//	TRAP_LB_JUMP, TRAP_B_JUMP, TRAP_RB_JUMP,
			//	TRAP_CONFUSE,
			//	TRAP_BOMB,
			//	TRAP_NIDDLE,
			//	TRAP_SHADOW, TRAP_NIDDLE_SHADOW,
			//	TRAP_NONE
			IMAGEMANAGER->findImage("trapTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(),
				(*_viTotalList)->rc.left, (*_viTotalList)->rc.top,
				(*_viTotalList)->trapFrameX, (*_viTotalList)->trapFrameY, (*_viTotalList)->alphaValue);
		}
	}

}

void bossStageScene::z_Order_Player_Boss()
{
	// 보스의 인덱스y가 플레이어의 인덱스y보다 크다면 플레이어를 먼저 그려준다.
	// 그렇지 않다면 보스를 먼저 그려준다.
	if (_deathMetal->getBoss_Index().y > _player->getPlayer().idy)	// 보스가 플레이어보다 앞에 있다.
	{
		//_player->render();
		//if (_deathMetal->getBoss_HP() > 0)	_deathMetal->render();

	}
	else	// 보스가 플레이어보다 뒤에 있다.
	{
		//if (_deathMetal->getBoss_HP() > 0)	_deathMetal->render();
		//_player->render();

	}

}

void bossStageScene::playerPos_Setting()
{
	_player->PlayerAddress()->x = _player->PlayerAddress()->idx * TESTTILESIZE + (TESTTILESIZE / 2);
	_player->PlayerAddress()->y = _player->PlayerAddress()->idy * TESTTILESIZE + (TESTTILESIZE / 3);
	_player->PlayerAddress()->rc = RectMakeCenter(_player->PlayerAddress()->x, _player->PlayerAddress()->y,
		_player->PlayerAddress()->bodyImage->getFrameWidth(), _player->PlayerAddress()->headImage->getFrameHeight());
	CAMERAMANAGER->set_CameraXY(_player->PlayerAddress()->idx * TESTTILESIZE + (TESTTILESIZE / 2),
		_player->PlayerAddress()->idy * TESTTILESIZE + (TESTTILESIZE / 3));
}

void bossStageScene::closePlayer(player* player, deathMetal* deathMetal)
{
	// 플레이어와 보스의 렉트 중점을 담는다.
	POINTFLOAT playerCenter;
	POINTFLOAT bossCenter;
	playerCenter.x = 0;
	playerCenter.y = 0;
	bossCenter.x = 0;
	bossCenter.y = 0;

	// 원하는 값을 모두 찾았다면 반복문을 나올때 사용
	bool find_P, find_B;
	find_P = find_B = false;



	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		// 플레이어 인덱스와 같은 타일을 찾아서 렉트의 중점을 구한다.
		if (_vTotalList[i]->idX == player->getPlayer().idx && _vTotalList[i]->idY == player->getPlayer().idy)
		{
			playerCenter.x = (_vTotalList[i]->rc.left + _vTotalList[i]->rc.right) / 2;
			playerCenter.y = (_vTotalList[i]->rc.top + _vTotalList[i]->rc.bottom) / 2;

			// 찾았다면 true
			find_P = true;
		}

		// 보스 인덱스와 같은 타일을 찾아서 렉트의 중점을 구한다.
		if (_vTotalList[i]->idX == deathMetal->getBoss_Index().x && _vTotalList[i]->idY == deathMetal->getBoss_Index().y)
		{
			bossCenter.x = (_vTotalList[i]->rc.left + _vTotalList[i]->rc.right) / 2;
			bossCenter.y = (_vTotalList[i]->rc.top + _vTotalList[i]->rc.bottom) / 2;
			// 찾았다면 true
			find_B = true;
		}

		// 둘 다 찾았다면 반복문을 나온다.
		if (find_P && find_B) break;
	}

	// 플레이어와 보스의 거리를 저장한다.
	float distance = getDistance(bossCenter.x, bossCenter.y,
		playerCenter.x, playerCenter.y);



	// 만약 타일의 사이즈인 52로 나누었을때 0이 나온다면 52(양옆위아래)로 거리를 재야 한다.
	if ((int)distance % TILESIZE == 0)
	{
		// 거리가 달라질때만 값이 바뀌기 때문에 한번만 적용이 된다.
		if (!distanceCheck)
		{
			// 플레이어가 인식 범위 안에 있다면 쉐도우를 벗는다.
			if (distance < TILESIZE * BOSS_RECOGNITION_RANGE)
			{
				distanceCheck = true;
				deathMetal->setBoss_ClosePlayer(true);
				//deathMetal->ChangeAni();
			}
		}

		if (distanceCheck)
		{
			// 플레이어가 인식 범위 안에 없다면 쉐도우를 입는다.
			if (distance >= TILESIZE * BOSS_RECOGNITION_RANGE)
			{
				distanceCheck = false;
				deathMetal->setBoss_ClosePlayer(false);
				//deathMetal->ChangeAni();
			}
		}
	}


	//cout << "distance :" << distance << endl;
	//cout << "range : " << TILESIZE * BOSS_RECOGNITION_RANGE << endl;
	//cout << distanceCheck << endl;

	// 만약 타일 사이즈인 52로 나누었을때 0이 나오지 않는다면 대각선이라는 뜻
	else
	{
		// 거리가 달라질때만 값이 바뀌기 때문에 한번만 적용이 된다.
		if (!distanceCheck)
		{
			// 플레이어가 인식 범위 안에 있다면 쉐도우를 벗는다. 인식범위 예외처리를 해준다.
			if (distance < (TILESIZE) * (BOSS_RECOGNITION_RANGE - 1) && distance < 165)
			{
				distanceCheck = true;
				deathMetal->setBoss_ClosePlayer(true);
				//deathMetal->ChangeAni();
			}
		}

		if (distanceCheck)
		{
			// 플레이어가 인식 범위 안에 없다면 쉐도우를 입는다. 인식범위 예외처리를 해준다.
			if (distance >= (TILESIZE) * (BOSS_RECOGNITION_RANGE - 1) || distance > 165)
			{
				distanceCheck = false;
				deathMetal->setBoss_ClosePlayer(false);
				//deathMetal->ChangeAni();
			}
		}
	}
}

void bossStageScene::searchSlave(vector<slave*> vSlaveList, player* player)
{
	for (int i = 0; i < vSlaveList.size(); ++i)
	{
		closePlayer_Slave(player, vSlaveList[i]->get_Slave());
	}
}

void bossStageScene::closePlayer_Slave(player* player, SLAVE_INFO* slave)
{
	// 플레이어와 슬레이브의 렉트 중점을 담는다.
	POINTFLOAT playerCenter;
	POINTFLOAT slaveCenter;



	// 원하는 값을 모두 찾았다면 반복문을 나올때 사용
	bool find_P, find_S;
	find_P = find_S = false;



	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		// 플레이어 인덱스와 같은 타일을 찾아서 렉트의 중점을 구한다.
		if (_vTotalList[i]->idX == player->getPlayer().idx && _vTotalList[i]->idY == player->getPlayer().idy)
		{
			playerCenter.x = (_vTotalList[i]->rc.left + _vTotalList[i]->rc.right) / 2;
			playerCenter.y = (_vTotalList[i]->rc.top + _vTotalList[i]->rc.bottom) / 2;

			// 찾았다면 true
			find_P = true;
		}

		// 슬레이브 인덱스와 같은 타일을 찾아서 렉트의 중점을 구한다.
		if (_vTotalList[i]->idX == slave->pos.index.x && _vTotalList[i]->idY == slave->pos.index.y)
		{
			slaveCenter.x = (_vTotalList[i]->rc.left + _vTotalList[i]->rc.right) / 2;
			slaveCenter.y = (_vTotalList[i]->rc.top + _vTotalList[i]->rc.bottom) / 2;

			// 찾았다면 true
			find_S = true;
		}

		// 둘 다 찾았다면 반복문을 나온다.
		if (find_P && find_S) break;
	}



	// 플레이어와 슬레이브의 거리를 저장한다.
	float distance = getDistance(slaveCenter.x, slaveCenter.y,
		playerCenter.x, playerCenter.y);


	// 만약 타일의 사이즈인 52로 나누었을때 0이 나온다면 52(양옆위아래)로 거리를 재야 한다.
	if ((int)distance % TILESIZE == 0)
	{
		// 거리가 달라질때만 값이 바뀌기 때문에 한번만 적용이 된다.
		if (!slave->b_Value.distanceCheck)
		{
			// 플레이어가 인식 범위 안에 있다면 쉐도우를 벗는다.
			if (distance < TILESIZE * BOSS_RECOGNITION_RANGE)
			{
				slave->b_Value.distanceCheck = true;
				slave->b_Value.isClosePlayer = true;
			}
		}

		if (slave->b_Value.distanceCheck)
		{
			// 플레이어가 인식 범위 안에 없다면 쉐도우를 입는다.
			if (distance >= TILESIZE * BOSS_RECOGNITION_RANGE)
			{
				slave->b_Value.distanceCheck = false;
				slave->b_Value.isClosePlayer = false;
			}
		}
	}

	// 만약 타일 사이즈인 52로 나누었을때 0이 나오지 않는다면 대각선이라는 뜻
	else
	{
		// 거리가 달라질때만 값이 바뀌기 때문에 한번만 적용이 된다.
		if (!slave->b_Value.distanceCheck)
		{
			// 플레이어가 인식 범위 안에 있다면 쉐도우를 벗는다. 인식범위 예외처리를 해준다.
			if (distance < (TILESIZE) * (BOSS_RECOGNITION_RANGE - 1) && distance < 165)
			{
				slave->b_Value.distanceCheck = true;
				slave->b_Value.isClosePlayer = true;
			}
		}

		if (slave->b_Value.distanceCheck)
		{
			// 플레이어가 인식 범위 안에 없다면 쉐도우를 입는다. 인식범위 예외처리를 해준다.
			if (distance >= (TILESIZE) * (BOSS_RECOGNITION_RANGE - 1) || distance > 165)
			{
				slave->b_Value.distanceCheck = false;
				slave->b_Value.isClosePlayer = false;
			}
		}
	}

}

void bossStageScene::findPlayer(player* player, deathMetal* deathMetal, UImanager* ui)
{

	// 보스의 인덱스에서 플레이어의 인덱스를 빼서 값을 담아둔다. (플레이어의 위치를 찾고, 어느 방향이 가까운지 비교에서 사용할 것)
	int x = deathMetal->getBoss_Index().x - player->getPlayer().idx;
	int y = deathMetal->getBoss_Index().y - player->getPlayer().idy;


	// x가 짧다면 flase, y가 짧다면 true의 값을 저장한다.
	bool x_OR_y = false;

	// 부호를 없애서 어느 방향이 더 짧은지를 찾아준다. (짧은 방향부터 먼저 찾게 된다.)
	if (abs(x) > abs(y))
	{
		// y가 더 짧다면 true를 넣어준다.
		x_OR_y = true;
	}
	else
	{
		// x가 더 짧다면 false를 넣어준다.
		x_OR_y = false;
	}

	// x, y 중에 x가 더 짧다면 x부터 찾아준다.
	if (x_OR_y)
	{
		// x가 양수라면 플레이어는 왼쪽에 있다.
		if (x > 0)
		{
			// 만약 바로 앞에 플레이어가 있을 경우에는 움직임을 멈춘다. ( 또는 근접 공격을 한다.)
			if (deathMetal->getBoss_Index().x - 1 == player->getPlayer().idx
				&& deathMetal->getBoss_Index().y == player->getPlayer().idy)
			{
				if (_collision.collision_DeathMetal_Find_Player(_player, _deathMetal))
				{
					// 플레이어가 앞에 있다면 근접 공격을 해준다.
					//ui->set_HP();
					_player->playerHit(deathMetal->getBoss_Atk());
					CAMERAMANAGER->Camera_WorldDC_Shake();
				}

				// 플레이어에게 근접 공격 이펙트를 그려준다.
				boss_Base_Attack_Render("base_Attack", player);

				// 여기서 방향을 정해주고, 무브 bool 값을 켜준다.
				deathMetal->setBoss_Direction(BD_LEFT);

				//// 플레이어의 중점 좌표를 받아온다.
				//deathMetal->setBoss_BaseAttack_Pos(player->getPlayer().x, player->getPlayer().y);
				//
				//// 이펙트 이미지를 넣어준다.
				//deathMetal->setBoss_BaseSkill_Image("base_Attack");
				//
				//// 어떤 이펙트를 뿌릴지 넣어준다.
				//deathMetal->setBoss_BaseSkill("Base_Attack");
				//
				//// 이펙트를 실행 시킨다.
				//deathMetal->start_AttackAni();

				// 다음 이동을 위해 무브 카운트를 다시 채워준다.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}

			// 플레이어가 없다면 이동을 해준다.
			else
			{
				// 여기서 방향을 정해주고, 무브 bool 값을 켜준다.
				deathMetal->setBoss_Direction(BD_LEFT);

				// 선형보간에서 사용할 현재 시간을 셋팅 해준다.
				deathMetal->setBoss_WorldTime(TIMEMANAGER->getWorldTime());

				// 이동 연산에 필요한 bool 값을 true로 바꿔주는 함수
				deathMetal->setBoss_Move_BoolValue_Ture();

				// 다음 이동을 위해 무브 카운트를 다시 채워준다.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());

				deathMetal->setBoss_Angle(PI);
			}
		}
		// x가 음수라면 플레이어는 오른쪽에 있다.
		else
		{
			// 만약 바로 앞에 플레이어가 있을 경우에는 움직임을 멈춘다. ( 또는 근접 공격을 한다.)
			if (deathMetal->getBoss_Index().x + 1 == player->getPlayer().idx
				&& deathMetal->getBoss_Index().y == player->getPlayer().idy)
			{
				if (_collision.collision_DeathMetal_Find_Player(_player, _deathMetal))
				{
					// 플레이어가 앞에 있다면 근접 공격을 해준다.
					//ui->set_HP();
					_player->playerHit(deathMetal->getBoss_Atk());
					CAMERAMANAGER->Camera_WorldDC_Shake();
				}

				// 플레이어에게 근접 공격 이펙트를 그려준다.
				boss_Base_Attack_Render("base_Attack", player);

				// 여기서 방향을 정해주고, 무브 bool 값을 켜준다.
				deathMetal->setBoss_Direction(BD_RIGHT);

				//// 플레이어의 중점 좌표를 받아온다.
				//deathMetal->setBoss_BaseAttack_Pos(player->getPlayer().x, player->getPlayer().y);
				//
				//// 이펙트 이미지를 넣어준다.
				//deathMetal->setBoss_BaseSkill_Image("base_Attack");
				//
				//// 어떤 이펙트를 뿌릴지 넣어준다.
				//deathMetal->setBoss_BaseSkill("Base_Attack");
				//
				//// 이펙트를 실행 시킨다.
				//deathMetal->start_AttackAni();

				// 다음 이동을 위해 무브 카운트를 다시 채워준다.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}

			// 플레이어가 없다면 이동을 해준다.
			else
			{
				// 여기서 방향을 정해주고, 무브 bool 값을 켜준다.
				deathMetal->setBoss_Direction(BD_RIGHT);

				// 선형보간에서 사용할 현재 시간을 셋팅 해준다.
				deathMetal->setBoss_WorldTime(TIMEMANAGER->getWorldTime());

				// 이동 연산에 필요한 bool 값을 true로 바꿔주는 함수
				deathMetal->setBoss_Move_BoolValue_Ture();

				// 다음 이동을 위해 무브 카운트를 다시 채워준다.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());

				deathMetal->setBoss_Angle(0);
			}
		}
	}

	// x, y 중에 y가 더 짧다면 y부터 찾아준다.
	if (!x_OR_y)
	{
		// y가 양수라면 플레이어는 위쪽에 있다.
		if (y > 0)
		{
			// 만약 바로 앞에 플레이어가 있을 경우에는 움직임을 멈춘다. ( 또는 근접 공격을 한다.)
			if (deathMetal->getBoss_Index().x == player->getPlayer().idx
				&& deathMetal->getBoss_Index().y - 1 == player->getPlayer().idy)
			{
				if (_collision.collision_DeathMetal_Find_Player(_player, _deathMetal))
				{
					// 플레이어가 앞에 있다면 근접 공격을 해준다.
					//ui->set_HP();
					_player->playerHit(deathMetal->getBoss_Atk());
					CAMERAMANAGER->Camera_WorldDC_Shake();
				}

				// 플레이어에게 근접 공격 이펙트를 그려준다.
				boss_Base_Attack_Render("base_Attack", player);

				// 여기서 방향을 정해주고, 무브 bool 값을 켜준다.
				deathMetal->setBoss_Direction(BD_UP);

				//// 플레이어의 중점 좌표를 받아온다.
				//deathMetal->setBoss_BaseAttack_Pos(player->getPlayer().x, player->getPlayer().y);
				//
				//// 이펙트 이미지를 넣어준다.
				//deathMetal->setBoss_BaseSkill_Image("base_Attack");
				//
				//// 어떤 이펙트를 뿌릴지 넣어준다.
				//deathMetal->setBoss_BaseSkill("Base_Attack");
				//
				//// 이펙트를 실행 시킨다.
				//deathMetal->start_AttackAni();

				// 다음 이동을 위해 무브 카운트를 다시 채워준다.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}

			// 플레이어가 없다면 이동을 해준다.
			else
			{
				// 여기서 방향을 정해주고, 무브 bool 값을 켜준다.
				deathMetal->setBoss_Direction(BD_UP);

				// 선형보간에서 사용할 현재 시간을 셋팅 해준다.
				deathMetal->setBoss_WorldTime(TIMEMANAGER->getWorldTime());

				// 이동 연산에 필요한 bool 값을 true로 바꿔주는 함수
				deathMetal->setBoss_Move_BoolValue_Ture();

				// 다음 이동을 위해 무브 카운트를 다시 채워준다.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());

				deathMetal->setBoss_Angle(PI/2.f);
			}
		}
		// y가 음수라면 플레이어는 아래쪽에 있다.
		else
		{
			// 만약 바로 앞에 플레이어가 있을 경우에는 움직임을 멈춘다. ( 또는 근접 공격을 한다.)
			if (deathMetal->getBoss_Index().x == player->getPlayer().idx
				&& deathMetal->getBoss_Index().y + 1 == player->getPlayer().idy)
			{
				if (_collision.collision_DeathMetal_Find_Player(_player, _deathMetal))
				{
					// 플레이어가 앞에 있다면 근접 공격을 해준다.
					//ui->set_HP();
					_player->playerHit(deathMetal->getBoss_Atk());
					CAMERAMANAGER->Camera_WorldDC_Shake();
				}

				// 플레이어에게 근접 공격 이펙트를 그려준다.
				boss_Base_Attack_Render("base_Attack", player);

				// 여기서 방향을 정해주고, 무브 bool 값을 켜준다.
				deathMetal->setBoss_Direction(BD_DOWN);

				//// 플레이어의 중점 좌표를 받아온다.
				//deathMetal->setBoss_BaseAttack_Pos(player->getPlayer().x, player->getPlayer().y);
				//
				//// 이펙트 이미지를 넣어준다.
				//deathMetal->setBoss_BaseSkill_Image("base_Attack");
				//
				//// 어떤 이펙트를 뿌릴지 넣어준다.
				//deathMetal->setBoss_BaseSkill("Base_Attack");
				//
				//// 이펙트를 실행 시킨다.
				//deathMetal->start_AttackAni();

				// 다음 이동을 위해 무브 카운트를 다시 채워준다.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}

			// 플레이어가 없다면 이동을 해준다.
			else
			{

				// 여기서 방향을 정해주고, 무브 bool 값을 켜준다.
				deathMetal->setBoss_Direction(BD_DOWN);

				// 선형보간에서 사용할 현재 시간을 셋팅 해준다.
				deathMetal->setBoss_WorldTime(TIMEMANAGER->getWorldTime());

				// 이동 연산에 필요한 bool 값을 true로 바꿔주는 함수
				deathMetal->setBoss_Move_BoolValue_Ture();

				// 다음 이동을 위해 무브 카운트를 다시 채워준다.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());

				deathMetal->setBoss_Angle(PI + PI / 2);
			}
		}
	}

}

SLAVE_DIRECTION bossStageScene::findPlayer(player* player, SLAVE_INFO* slave)
{
	// 플레이어의 방향을 잡아서 방향을 리턴값으로 보내준다.

	// 플레이어의 방향을 찾는다.

	// x, y 중 짧은것을 선택한다.

	// 이동 시 이동 불가능 오브젝트를 찾는다.

	// 막히면 다른 방향으로

	// x, y 중 같은 라인에 도착한다면 남은 라인으로만 이동을 한다.

	// 슬레이브와 플레이어의 타일 중점을 구한다.
	POINTFLOAT playerCenter;
	POINTFLOAT slaveCenter;
	playerCenter.x = 0;
	playerCenter.y = 0;
	slaveCenter.x = 0;
	slaveCenter.y = 0;

	// 둘 다 원하는 값을 찾았으면 반복문에서 빠져나온다.
	bool findPlayer, findSlave;
	findPlayer = findSlave = false;

	// 보스맵에서 해당 인덱스를 찾기 위해 반복.
	for (_viTotalList = _vTotalList.begin(); _viTotalList != _vTotalList.end(); ++_viTotalList)
	{
		// 플레이어의 인덱스와 같은 타일을 찾는다.
		if ((*_viTotalList)->idX == player->getPlayer().idx && (*_viTotalList)->idY == player->getPlayer().idy)
		{
			// 타일의 렉트를 이용하여 중점을 저장한다.
			playerCenter.x = ((*_viTotalList)->rc.left + (*_viTotalList)->rc.right) / 2;
			playerCenter.y = ((*_viTotalList)->rc.top + (*_viTotalList)->rc.bottom) / 2;

			findPlayer = true;
		}

		// 슬레이브의 인덱스와 같은 타일을 찾는다.
		if ((*_viTotalList)->idX == slave->pos.index.x && (*_viTotalList)->idY == slave->pos.index.y)
		{
			// 타일의 렉트를 이용하여 중점을 저장한다.
			slaveCenter.x = ((*_viTotalList)->rc.left + (*_viTotalList)->rc.right) / 2;
			slaveCenter.y = ((*_viTotalList)->rc.top + (*_viTotalList)->rc.bottom) / 2;

			findSlave = true;
		}

		// 값을 모두 찾았다면 반복문에서 나온다.
		if (findPlayer && findSlave) break;
	}

	// 슬레이브와 플레이어와의 x, y의 차를 담는다. (슬레이브 기준으로 빼준다.)
	POINTFLOAT range;
	range.x = abs(slaveCenter.x - playerCenter.x);
	range.y = abs(slaveCenter.y - playerCenter.y);

	// x, y 중 짧은곳을 구한다.
	SHORT_XY short_XY = SHORT_XY::SHORT_NONE;

	// x가 짧다.
	if (range.x < range.y)
		short_XY = SHORT_XY::SHORT_X;

	// y가 짧다.
	if (range.x > range.y)
		short_XY = SHORT_XY::SHORT_Y;


	// 슬레이브와 플레이어의 인덱스 중 같은게 있다면 그 방향은 제외 하고 찾는다.
	FIND_CHOICE_XY find_Choice = FIND_CHOICE_XY::FC_XY;	// 0 = 양방향 모두, 1 = x 방향만 찾는다. 2 = y 방향만 찾는다.

	// 플레이어의 x와 슬레이브의 x가 같다면 x 방향은 도착한것 y방향을 찾도록 한다.
	if (player->getPlayer().idx == slave->pos.index.x)	find_Choice = FIND_CHOICE_XY::FC_Y;
	if (player->getPlayer().idy == slave->pos.index.y)	find_Choice = FIND_CHOICE_XY::FC_X;

	// 플레이어의 방향을 찾는다. (플레이어가 있는 각도를 구한다.)
	float player_Pos_Angle = 0;
	player_Pos_Angle = getAngle(slaveCenter.x, slaveCenter.y, playerCenter.x, playerCenter.y);

	// 만약 각도가 0 이하로 나온다면 (수정해준다. -각도를 +로)
	if (player_Pos_Angle < 0)
	{
		float tempAngle = 0;
		tempAngle = PI + player_Pos_Angle;
		player_Pos_Angle = PI + tempAngle;
	}

	// 플레이어의 방향을 저장한다.
	FIND_ANGLE find_Angle = FIND_ANGLE::FA_RT;		// 0 = 2시, 1 = 10시, 2 = 7시, 3 = 5시

	if (player_Pos_Angle > 0 && player_Pos_Angle < 1.57)	find_Angle = FIND_ANGLE::FA_RT;
	if (player_Pos_Angle > 1.57 && player_Pos_Angle < 3.14) find_Angle = FIND_ANGLE::FA_TL;
	if (player_Pos_Angle > 3.14 && player_Pos_Angle < 4.71) find_Angle = FIND_ANGLE::FA_LB;
	if (player_Pos_Angle > 4.71 && player_Pos_Angle < (PI * 2)) find_Angle = FIND_ANGLE::FA_BR;

	// 플레이어의 방향으로 이동을 시작한다.
	if (find_Choice == FIND_CHOICE_XY::FC_XY)
	{
		// x, y 중 짧은 방향으로 찾는다.
		switch (short_XY)
		{
		case SHORT_XY::SHORT_X:
			// 플레이어 방향에 따라서 왼쪽이나 오른쪽으로 이동한다.
			if (find_Angle == FIND_ANGLE::FA_TL || find_Angle == FIND_ANGLE::FA_LB)		return SLAVE_DIRECTION::SD_LEFT;
			if (find_Angle == FIND_ANGLE::FA_RT || find_Angle == FIND_ANGLE::FA_BR)		return SLAVE_DIRECTION::SD_RIGHT;
			break;

		case SHORT_XY::SHORT_Y:
			// 플레이어 방향에 따라서 위나 아래로 이동 한다.
			if (find_Angle == FIND_ANGLE::FA_RT || find_Angle == FIND_ANGLE::FA_TL) 	return SLAVE_DIRECTION::SD_UP;
			if (find_Angle == FIND_ANGLE::FA_LB || find_Angle == FIND_ANGLE::FA_BR)     return SLAVE_DIRECTION::SD_DOWN;
			break;
		}
	}

	// y 방향만 찾으면 된다.
	if (find_Choice == FIND_CHOICE_XY::FC_Y)
	{
		// 플레이어 방향에 따라서 위나 아래로 이동 한다.
		if (find_Angle == FIND_ANGLE::FA_RT || find_Angle == FIND_ANGLE::FA_TL) 	return SLAVE_DIRECTION::SD_UP;
		if (find_Angle == FIND_ANGLE::FA_LB || find_Angle == FIND_ANGLE::FA_BR)     return SLAVE_DIRECTION::SD_DOWN;
	}

	// x 방향만 찾으면 된다.
	if (find_Choice == FIND_CHOICE_XY::FC_X)
	{
		// 플레이어 방향에 따라서 왼쪽이나 오른쪽으로 이동한다.
		if (find_Angle == FIND_ANGLE::FA_TL || find_Angle == FIND_ANGLE::FA_LB)		return SLAVE_DIRECTION::SD_LEFT;
		if (find_Angle == FIND_ANGLE::FA_RT || find_Angle == FIND_ANGLE::FA_BR)		return SLAVE_DIRECTION::SD_RIGHT;
	}
}

void bossStageScene::boss_Move_Player()
{
	//// 데스메탈의 무브 카운트를 1 감소 시켜준다. (데스메탈이 비트를 받지 않았다면 이곳에 들어간다.)
	//if (BEATMANAGER->getInterval() && !_deathMetal->getBoss_Beat())
	//{
	//	_deathMetal->setBoss_Beat(true);		// 비트를 받았다면 true로 바꿔준다. (여러번 들어오는것을 방지)
	//	_deathMetal->setBoss_Move_Count();		// 무브 카운트를 1 감소한다.
	//}
	//
	//// 비트의 값이 0이 됐을때 false의 값으로 바꿔준다.
	//if (!BEATMANAGER->getInterval()) _deathMetal->setBoss_Beat(false);

	// 데스메탈의 무브 카운트를 1 감소 시켜준다. (데스메탈이 비트를 받지 않았다면 이곳에 들어간다.)
	if (BEATMANAGER->getBeating() && !_deathMetal->getBoss_Beat())
	{
		_deathMetal->setBoss_Beat(true);		// 비트를 받았다면 true로 바꿔준다. (여러번 들어오는것을 방지)
		_deathMetal->setBoss_Move_Count();		// 무브 카운트를 1 감소한다.
	}

	// 비트의 값이 0이 됐을때 false의 값으로 바꿔준다.
	if (!BEATMANAGER->getBeating()) _deathMetal->setBoss_Beat(false);

	// 데스메탈의 무브 카운트가 0 이하가 된다면 이동을 시작 한다.
	if (_deathMetal->getBoss_Move_Count() < 0)
	{
		// 데스메탈이 이동 못하는곳을 찾아준다.
		if (!_collision.collision_Charactor_Object(&_vTotalList, _deathMetal) &&
			!_collision.collision_DeathMetal_Find_Slave(_deathMetal, _sm->get_SlaveList()))
		{
			// 플레이어와 데스메탈의 정보를 이용하여 이동 할 방향을 정한다.
			findPlayer(_player, _deathMetal, _ui);
		}
	}


}

void bossStageScene::slave_Move_Player()
{
	// 슬레이브가 1마리 이상 생성 되어야만 들어간다.  
	if (_sm->get_SlaveList().size() > 0)
	{
		for (int i = 0; i < _sm->get_SlaveList().size(); ++i)
		{
			// 슬레이브의 무브 카운트를 1 감소 시켜준다. (슬레이브가 비트를 받지 않았다면 이곳에 들어간다.)
			if (BEATMANAGER->getBeating() && !_sm->get_SlaveList()[i]->get_Slave()->b_Value.beat)
			{
				_sm->get_SlaveList()[i]->get_Slave()->b_Value.beat = true;		// 비트를 받았다면 true로 바꿔준다.
				_sm->get_SlaveList()[i]->get_Slave()->operation.move_Count--;	// 무브 카운트를 1 감소한다.
			}

			// 비트 값이 0이 될때 false의 값으로 바꿔준다.
			if (!BEATMANAGER->getBeating()) _sm->get_SlaveList()[i]->get_Slave()->b_Value.beat = false;

			// 슬레이브의 무브 카운트가 0 이하가 된다면 이동을 시작한다.
			if (_sm->get_SlaveList()[i]->get_Slave()->operation.move_Count < 0)
			{
				// 슬레이브가 이동 해야 하는 방향을 받아온다.
				_sm->get_SlaveList()[i]->get_Slave()->operation.move_Count = _sm->get_SlaveList()[i]->get_Slave()->operation.save_Move_Count;

				// 플레이어가 있는 방향을 찾는다.
				// 근처에 플레이어가 있는지 찾는다.
				// 있으면 공격
				// 없으면 이동
				SLAVE_DIRECTION temp_Direction;
				temp_Direction = _sm->get_SlaveList()[i]->get_Slave()->status.direction;
				_sm->get_SlaveList()[i]->get_Slave()->status.direction = findPlayer(_player, _sm->get_SlaveList()[i]->get_Slave());

				// 플레이어가 근처에 있는지 찾는다. 만약 있다면 공격
				if (_collision.collision_Slave_Find_Player(_player, _sm->get_SlaveList()[i]->get_Slave()) &&
					!_sm->get_SlaveList()[i]->get_Slave()->b_Value.ghostJonYha)
				{
					_player->playerHit(_sm->get_SlaveList()[i]->get_Slave()->status.attack);
					//_ui->set_HP();
					// 플레이어에게 근접 공격 이펙트를 그려준다.
					boss_Base_Attack_Render("base_Attack", _player);
					CAMERAMANAGER->Camera_WorldDC_Shake();
				}

				// 데스메탈이 근처에 있는지 찾는다. 만약 있다면 이동 안함
				if (_collision.collision_Slave_Find_DeathMetal(_deathMetal, _sm->get_SlaveList()[i]->get_Slave()) ||
					_collision.collision_Charactor_Object(&_vTotalList, _sm->get_SlaveList()[i]->get_Slave()) ||
					_collision.collision_Slave_Find_Slave(_sm->get_SlaveList()[i]->get_Slave(), _sm->get_SlaveList()))
				{
					// 이동 안함
				}

				if (!_collision.collision_Slave_Find_Player(_player, _sm->get_SlaveList()[i]->get_Slave()) &&
					!_collision.collision_Slave_Find_DeathMetal(_deathMetal, _sm->get_SlaveList()[i]->get_Slave()) &&
					!_collision.collision_Charactor_Object(&_vTotalList, _sm->get_SlaveList()[i]->get_Slave()) &&
					!_collision.collision_Slave_Find_Slave(_sm->get_SlaveList()[i]->get_Slave(), _sm->get_SlaveList()))
				{
					// 충돌하는게 없다면 이동한다.
					// 플레이어가 고스트를 바라 볼때는 움직이면 안된다.
					if (_sm->get_SlaveList()[i]->get_Slave()->status.type == SLAVE_TYPE::SLAVE_GHOST)
					{
						if (_sm->get_SlaveList()[i]->get_Slave()->status.direction == SLAVE_DIRECTION::SD_LEFT &&
							_player->getPlayer().direction == PLAYERDIRECTION_RIGHT ||
							_sm->get_SlaveList()[i]->get_Slave()->status.direction == SLAVE_DIRECTION::SD_RIGHT &&
							_player->getPlayer().direction == PLAYERDIRECTION_LEFT ||
							_sm->get_SlaveList()[i]->get_Slave()->status.direction == SLAVE_DIRECTION::SD_UP &&
							_player->getPlayer().direction == PLAYERDIRECTION_DOWN ||
							_sm->get_SlaveList()[i]->get_Slave()->status.direction == SLAVE_DIRECTION::SD_DOWN &&
							_player->getPlayer().direction == PLAYERDIRECTION_UP)
						{
							// 움직이면 안돼
							// 고스트는 투명해져야한다.
							// 고스트가 투명할땐 공격이 통하지 않는다.
							_sm->get_SlaveList()[i]->get_Slave()->b_Value.ghostMoveStop = true;
							_sm->get_SlaveList()[i]->get_Slave()->b_Value.ghostJonYha = true;
						}
						else
						{
							// 고스트가 다시 색이 돌아오고 이동이 가능하다.
							// 다시 공격 가능 상태로 변한다.
							_sm->get_SlaveList()[i]->get_Slave()->b_Value.ghostMoveStop = false;
							_sm->get_SlaveList()[i]->get_Slave()->b_Value.ghostJonYha = false;
							_sm->get_SlaveList()[i]->get_Slave()->b_Value.isMove = true;
						}
					}
					else _sm->get_SlaveList()[i]->get_Slave()->b_Value.isMove = true;
				}

				// 만약 박쥐라면 벽을 제외한 방향을 
				if(_sm->get_SlaveList()[i]->get_Slave()->status.type == SLAVE_TYPE::SLAVE_BAT)
				{
					for (; ; )
					{
						// 랜덤으로 값을 받고, 그 방향에 에너미, 보스, 벽이 없다면 그 방향으로 이동하ㅔ 한다.
						int rndNum = RND->getInt(4);
						bool exit_For = false;

						switch (rndNum)
						{
							// 왼쪽
						case 0:
							_sm->get_SlaveList()[i]->get_Slave()->status.direction = SLAVE_DIRECTION::SD_LEFT;
							// 이동 가능한 방향을 찾으면 박쥐 무브에 방향을 보내준다.
							if (!_collision.collision_Slave_Find_Player(_player, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_DeathMetal(_deathMetal, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Charactor_Object(&_vTotalList, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_Slave(_sm->get_SlaveList()[i]->get_Slave(), _sm->get_SlaveList()))
							{
								_sm->get_SlaveList()[i]->get_Slave()->b_Value.isMove = true;
								exit_For = true;
							}
							break;

							// 위
						case 1:
							_sm->get_SlaveList()[i]->get_Slave()->status.direction = SLAVE_DIRECTION::SD_UP;
							// 이동 가능한 방향을 찾으면 박쥐 무브에 방향을 보내준다.
							if (!_collision.collision_Slave_Find_Player(_player, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_DeathMetal(_deathMetal, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Charactor_Object(&_vTotalList, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_Slave(_sm->get_SlaveList()[i]->get_Slave(), _sm->get_SlaveList()))
							{
								_sm->get_SlaveList()[i]->get_Slave()->b_Value.isMove = true;
								exit_For = true;
							}
							break;

							// 오른쪽
						case 2:
							_sm->get_SlaveList()[i]->get_Slave()->status.direction = SLAVE_DIRECTION::SD_RIGHT;
							// 이동 가능한 방향을 찾으면 박쥐 무브에 방향을 보내준다.
							if (!_collision.collision_Slave_Find_Player(_player, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_DeathMetal(_deathMetal, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Charactor_Object(&_vTotalList, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_Slave(_sm->get_SlaveList()[i]->get_Slave(), _sm->get_SlaveList()))
							{
								_sm->get_SlaveList()[i]->get_Slave()->b_Value.isMove = true;
								exit_For = true;
							}
							break;

							// 아래
						case 3:
							_sm->get_SlaveList()[i]->get_Slave()->status.direction = SLAVE_DIRECTION::SD_DOWN;
							// 이동 가능한 방향을 찾으면 박쥐 무브에 방향을 보내준다.
							if (!_collision.collision_Slave_Find_Player(_player, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_DeathMetal(_deathMetal, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Charactor_Object(&_vTotalList, _sm->get_SlaveList()[i]->get_Slave()) &&
								!_collision.collision_Slave_Find_Slave(_sm->get_SlaveList()[i]->get_Slave(), _sm->get_SlaveList()))
							{
								_sm->get_SlaveList()[i]->get_Slave()->b_Value.isMove = true;
								exit_For = true;
							}
							break;
						}

						// 방향을 찾았다면 나간다.
						if (exit_For) break;
					}
				}

				

			}
		}
	}
}

void bossStageScene::boss_Base_Attack_Render()
{
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->img->frameRender(CAMERAMANAGER->getWorldDC(), (*_viEffect)->rc.left, (*_viEffect)->rc.top,
			(*_viEffect)->img->getFrameX(), (*_viEffect)->img->getFrameY());

		// 이미지를 그려주고 다음 프레임으로 넘겨준다.
		(*_viEffect)->img->setFrameX((*_viEffect)->img->getFrameX() + 1);

		// 만약 최대 프레임 이상이라면 벡터를 지워준다.
		if ((*_viEffect)->img->getFrameX() >= (*_viEffect)->Max_FrameX)
		{
			_vEffect.erase(_viEffect);

			break;
		}
	}
}

void bossStageScene::boss_Base_Attack_Render(string skillName, player* player)
{
	// 보스가 공격을 했을때 그 타일 위치에 이펙트를 보여준다.
	// 애니메이션 쓰지 않고 프레임 랜더로 그리다가 마지막 이미지 출력 후
	// 벡터 삭제를 하는걸로?
	// 벡터는 어디서 생성?

	// 뿌려질 이미지와 뿌려질 좌표를 임시로 저장 하는 변수를 만든다. + 공간 할당
	// 플레이어의 렉트에 이미지를 뿌리고, 프레임이 모두 끝난다면 벡터를 삭제 해준다.
	BOSS_STAGE_EFFECT_VECTOR* temp_Effect = new BOSS_STAGE_EFFECT_VECTOR;
	temp_Effect->img = IMAGEMANAGER->findImage(skillName);
	temp_Effect->img->setFrameX(0);
	temp_Effect->img->setFrameY(0);
	temp_Effect->Max_FrameX = temp_Effect->img->getMaxFrameX();
	temp_Effect->rc = RectMake(player->getPlayer().idx * TILESIZE, player->getPlayer().idy * TILESIZE,
		TILESIZE, TILESIZE);
	// 이펙트가 뿌려질 중점 좌표와 뿌려질 이펙트 이미지를 담는 벡터
	_vEffect.push_back(temp_Effect);
}

void bossStageScene::start_Slave_Create()
{
	// 기본으로 보스방에 있는 고스트 4마리
	_sm->create_Slave(SLAVE_TYPE::SLAVE_GHOST, _deathMetal->getBoss_Index().x - 2, _deathMetal->getBoss_Index().y - 2);
	_sm->create_Slave(SLAVE_TYPE::SLAVE_GHOST, _deathMetal->getBoss_Index().x + 2, _deathMetal->getBoss_Index().y - 2);
	_sm->create_Slave(SLAVE_TYPE::SLAVE_GHOST, _deathMetal->getBoss_Index().x - 2, _deathMetal->getBoss_Index().y + 2);
	_sm->create_Slave(SLAVE_TYPE::SLAVE_GHOST, _deathMetal->getBoss_Index().x + 2, _deathMetal->getBoss_Index().y + 2);
}

void bossStageScene::bossSceneSetting()
{
	_scene_Starter.isOpen = false;
	_scene_Starter.startMoveImg = false;
	_scene_Starter.image_Speed = 10;
	_scene_Starter.main_OK = false;
	_scene_Starter.bottom_OK = false;
	_scene_Starter.top_OK = false;
	_scene_Starter.isDoorOpen = false;

	_scene_Starter.main_Img = IMAGEMANAGER->findImage("deathMetal_Main");
	_scene_Starter.top_Img = IMAGEMANAGER->findImage("deathMetal_TopBlade");
	_scene_Starter.bottom_Img = IMAGEMANAGER->findImage("deathMetal_BottomBlade");

	_scene_Starter.main_Img->setX(WINSIZEX);
	_scene_Starter.main_Img->setY(80);

	_scene_Starter.top_Img->setX(-WINSIZEX);
	_scene_Starter.top_Img->setY(100);

	_scene_Starter.bottom_Img->setX(WINSIZEX + 100);
	_scene_Starter.bottom_Img->setY(WINSIZEY - 150);
}

void bossStageScene::bossSceneStart()
{
	


	if (!_scene_Starter.isOpen)
	{
		// 데스메탈 사운드가 들린다.
		if (!introSound)
		{
			// 여기에서 사운드 한번 실행
			SOUNDMANAGER->play("deathmetal_intro");
			introSound = true;
		}

		// 처음 보스 등장 씬이 날아온다. 정해진 위치까지 도착하면, 엔터를 누르면 더 빠르게 위치로 날아간다.
		// 그리고 엔터를 다시 누르면 등장 씬은 다시 왔던길로 되돌아가고 다 돌아갔으면 게임이 시작된다.
		if (!_scene_Starter.startMoveImg)
		{
			// 이미지를 전부 보여줬으면 더 이상 이동하면 안된다.
			if (_scene_Starter.top_Img->getX() + _scene_Starter.image_Speed <= 0)
			{
				_scene_Starter.top_Img->setX(_scene_Starter.top_Img->getX() + _scene_Starter.image_Speed);
			}
			// 이미지가 도착했으면 true
			else _scene_Starter.top_OK = true;

			if (_scene_Starter.main_Img->getX() - _scene_Starter.image_Speed >= 0)
			{
				_scene_Starter.main_Img->setX(_scene_Starter.main_Img->getX() - _scene_Starter.image_Speed);
			}
			// 이미지가 도착했으면 true
			else _scene_Starter.main_OK = true;

			if (_scene_Starter.main_Img->getX() < WINSIZEX - 130)
			{
				if (_scene_Starter.bottom_Img->getX() - _scene_Starter.image_Speed > WINSIZEX - _scene_Starter.bottom_Img->getWidth())
				{
					_scene_Starter.bottom_Img->setX(_scene_Starter.bottom_Img->getX() - _scene_Starter.image_Speed);
				}
				// 이미지가 도착했으면 true
				else _scene_Starter.bottom_OK = true;
			}

			// 모든 이미지가 도착 했을때 엔터를 누르면 사라지는 연산을 시작한다.
			if (_scene_Starter.main_OK && _scene_Starter.bottom_OK && _scene_Starter.top_OK)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
				{
					// 이미지 무브가 모두 끝났으니 true의 값을 넣는다.
					_scene_Starter.startMoveImg = true;
				}
			}
			else if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_scene_Starter.image_Speed = 16;
			}
		}

		if (_scene_Starter.startMoveImg)
		{
			// 이미지가 모두 사라질때까지 반복한다.
			if (_scene_Starter.top_Img->getX() + _scene_Starter.top_Img->getWidth() >= 0)
			{
				_scene_Starter.top_Img->setX(_scene_Starter.top_Img->getX() - _scene_Starter.image_Speed);
			}
			// 이미지가 사라졌으면 false
			else _scene_Starter.top_OK = false;

			if (_scene_Starter.main_Img->getX() <= WINSIZEX)
			{
				_scene_Starter.main_Img->setX(_scene_Starter.main_Img->getX() + _scene_Starter.image_Speed);
			}
			// 이미지가 사라졌으면 false
			else _scene_Starter.main_OK = false;


			if (_scene_Starter.bottom_Img->getX() <= WINSIZEX)
			{
				_scene_Starter.bottom_Img->setX(_scene_Starter.bottom_Img->getX() + _scene_Starter.image_Speed);
			}
			// 이미지가 사라졌으면 false
			else _scene_Starter.bottom_OK = false;


			// 모든 이미지가 사라진다면 게임이 시작 된다.
			if (!_scene_Starter.main_OK && !_scene_Starter.bottom_OK && !_scene_Starter.top_OK)
			{
				_scene_Starter.isOpen = true;
			}
		}
	}
	// 보스 스테이지 볼륨 조절, 문이 열리는 여부에 따라 소리 조절함
	setVolumeBossStage();
}

void bossStageScene::bossSceneRender()
{
	if (!_scene_Starter.isOpen)
	{
		_scene_Starter.top_Img->render(getMemDC(), _scene_Starter.top_Img->getX(), _scene_Starter.top_Img->getY());
		_scene_Starter.bottom_Img->render(getMemDC(), _scene_Starter.bottom_Img->getX(), _scene_Starter.bottom_Img->getY());
		_scene_Starter.main_Img->render(getMemDC(), _scene_Starter.main_Img->getX(), _scene_Starter.main_Img->getY());
	}
}

void bossStageScene::bossSceneDoorOpen()
{


	// 플레이어가 문에 있는 위치에 도착하면 문이 사라진다.
	if (_player->getPlayer().idx == 12 && _player->getPlayer().idy == 21 ||
		_player->getPlayer().idx == 13 && _player->getPlayer().idy == 21 ||
		_player->getPlayer().idx == 14 && _player->getPlayer().idy == 21)
	{
		// 문이였던 지역이 땅으로 바뀐다.
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			// 인덱스와 같은 타일을 찾는다.
			if (_vTotalList[i]->idX == 12 && _vTotalList[i]->idY == 20 ||
				_vTotalList[i]->idX == 13 && _vTotalList[i]->idY == 20 ||
				_vTotalList[i]->idX == 14 && _vTotalList[i]->idY == 20)
			{
				//_vTotalList[i]->type = TYPE_NONE;
				_vTotalList[i]->wall = W_NONE;
			}
		}
	}

	// 문을 지나가면 보스가 월컴을 외친다.
	// 플레이어가 문을 지나 가면 문이 있던 자리에 벽이 생긴다.
	if (_player->getPlayer().idx == 12 && _player->getPlayer().idy == 19 ||
		_player->getPlayer().idx == 13 && _player->getPlayer().idy == 19 ||
		_player->getPlayer().idx == 14 && _player->getPlayer().idy == 19)
	{
		// 웰컴을 한번 외친다.
		if (introSound)
		{
			// 웰컴 사운드
			SOUNDMANAGER->play("deathmetal_welcome");
			introSound = false;
		}

		// 문이였던 지역을 벽으로 바꿔준다.
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			// 인덱스과 같은 타일에 벽을 세워준다.
			if (_vTotalList[i]->idX == 12 && _vTotalList[i]->idY == 20 ||
				_vTotalList[i]->idX == 13 && _vTotalList[i]->idY == 20 ||
				_vTotalList[i]->idX == 14 && _vTotalList[i]->idY == 20)
			{
				_vTotalList[i]->type = TYPE_WALL;
				_vTotalList[i]->wall = W_BOSS_WALL;
				_vTotalList[i]->wallFrameX = 3;
				_vTotalList[i]->wallFrameY = 2;
			}
		}

		// 보스방에 있는 아이들이 움직이기 시작한다.
		_scene_Starter.isDoorOpen = true;
	}

}

void bossStageScene::bossClear()
{

	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		// 벽이 사라져야 하는 인덱스 이타일을 찾는다.
		if (_vTotalList[i]->idX == 11 && _vTotalList[i]->idY == 10 ||
			_vTotalList[i]->idX == 12 && _vTotalList[i]->idY == 10 ||
			_vTotalList[i]->idX == 13 && _vTotalList[i]->idY == 10 ||
			_vTotalList[i]->idX == 14 && _vTotalList[i]->idY == 10 ||
			_vTotalList[i]->idX == 15 && _vTotalList[i]->idY == 10)
		{
			_vTotalList[i]->wall = W_NONE;
		}
	}
}

void bossStageScene::boss_PhaseMove()
{
	// 페이즈별 행동
	switch (_deathMetal->getBoss_Phase())
	{
	case BP_PHASE_1:
		// 관통 무기가 아닌 무기로 데스 메탈의 정면을 공격하면 튕기기만 함 (데미지x)
		// 박쥐 2마리 소환

		// 실드가 피격을 당했다면 뒤로 밀려난다.
		if (_deathMetal->getBoss_isShield_Hit())
		{
			// 해당 방향에 뒤쪽으로 밀려난다.
			switch (_deathMetal->getBoss_Direction())
			{
			case BD_LEFT:
				// 캐릭터가 바라보는 방향 뒤쪽에 오브젝트를 찾아준다. (뒤에 아무것도 없다면 false)
				if (!_collision.collision_Charactor_Object_Back(&_vTotalList, _deathMetal))
				{
					_deathMetal->setBoss_Index(_deathMetal->getBoss_Index().x + 1, _deathMetal->getBoss_Index().y);
				}

				break;

			case BD_UP:
				// 캐릭터가 바라보는 방향 뒤쪽에 오브젝트를 찾아준다. (뒤에 아무것도 없다면 false)
				if (!_collision.collision_Charactor_Object_Back(&_vTotalList, _deathMetal))
				{
					_deathMetal->setBoss_Index(_deathMetal->getBoss_Index().x, _deathMetal->getBoss_Index().y + 1);
				}

				break;

			case BD_RIGHT:
				// 캐릭터가 바라보는 방향 뒤쪽에 오브젝트를 찾아준다. (뒤에 아무것도 없다면 false)
				if (!_collision.collision_Charactor_Object_Back(&_vTotalList, _deathMetal))
				{
					_deathMetal->setBoss_Index(_deathMetal->getBoss_Index().x - 1, _deathMetal->getBoss_Index().y);
				}

				break;

			case BD_DOWN:
				// 캐릭터가 바라보는 방향 뒤쪽에 오브젝트를 찾아준다. (뒤에 아무것도 없다면 false)
				if (!_collision.collision_Charactor_Object_Back(&_vTotalList, _deathMetal))
				{
					_deathMetal->setBoss_Index(_deathMetal->getBoss_Index().x, _deathMetal->getBoss_Index().y - 1);
				}

				break;
			}

			// 보스 주변으로 랜덤으로 박쥐 소환 (2마리)
			int tempX, tempY;
			tempX = tempY = 0;
			int rndX, rndY;
			rndX = rndY = 0;

			// 2마리를 소환해야 하기 때문에 2번을 돈다.
			for (int i = 0; i < 2; ++i)
			{

				rndX = RND->getInt(9) + 8;
				rndY = RND->getInt(7) + 11;

				// 타일맵에서 오브젝트가 아닌 부분을 찾는다.
				for (int j = 0; j < _vTotalList.size(); ++j)
				{
					// 보스방 범위에서만 소환이 가능해야 한다.
					if (_vTotalList[j]->idX >= 8 && _vTotalList[j]->idX <= 18 &&
						_vTotalList[j]->idY >= 11 && _vTotalList[j]->idY <= 18)
					{
						// 보스가 있는 위치에는 나오면 안돼
						if (_deathMetal->getBoss_Index().x != rndX &&
							_deathMetal->getBoss_Index().y != rndY)
						{
							tempX = rndX;
							tempY = rndY;

							break;
						}

						// 기존에 슬레이브가 있는 위치에는 나오면 안돼
						for (int k = 0; j < _sm->get_SlaveList().size(); ++k)
						{
							if (_sm->get_SlaveList()[k]->get_Slave()->pos.index.x != rndX &&
								_sm->get_SlaveList()[j]->get_Slave()->pos.index.y != rndY)
							{
								tempX = rndX;
								tempY = rndY;
								break;
							}
						}

						// 플레이어 위치에는 나오면 안돼
						if (_player->getPlayer().idx != rndX &&
							_player->getPlayer().idy != rndY)
						{
							tempX = rndX;
							tempY = rndY;
							break;
						}
					}

					if (tempX && tempY) break;
				}

				// 소환 가능한 인덱스를 찾았다면 그곳에 소환한다. 
				if (tempX && tempY)	_sm->create_Slave(SLAVE_TYPE::SLAVE_BAT, tempX, tempY);
			
		
			}


			// 연산이 끝나면 피격을 false로 수정한다.
			_deathMetal->setBoss_isShield_Hit(false);
		}

		// 방패 맞았을때는 보스 체력이 달면 안돼

		break;

	case BP_PHASE_2:
		// 손을 들어올리고 4 박자 동안 공격을 받지 않으면 해골 1 ~ 3마리 소환
		// 공격 받으면 반대편으로 순간이동

		// 무브 카운트가 처음이라면 데스메탈은 손을 든다.
		if (_deathMetal->getBoss_Move_Count() == _deathMetal->getBoss_Move_Count_Value())
		{

		}

		// 무브 카운트가 0이라면 해골 소환 1 ~ 3
		if(_deathMetal->getBoss_Move_Count() == 0)

		break;

	case BP_PHASE_3:
		// 해골이 노란 해골로 교체

		break;

	case BP_PHASE_4:
		// 한박자로 왼쪽 오른쪽 벽에 붙고, 벽에 붙었으면 네 박자마다 파이어볼 발사

		break;
	}
}

void bossStageScene::setVolumeBossStage()
{
	if (_scene_Starter.isDoorOpen)
	{
		SOUNDMANAGER->setVolume("BGM_BOSS", 1.5f);
	}
	else
	{
		SOUNDMANAGER->setVolume("BGM_BOSS", 0.35f);
	}
}

void bossStageScene::endScene()
{
	if (_player->getPlayer().idx == _endX && _player->getPlayer().idy == _endY)
	{
		BEATMANAGER->AllStopMusic();
		SCENEMANAGER->changeScene("End");
	}
}
