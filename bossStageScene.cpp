#include "stdafx.h"
#include "bossStageScene.h"
#include "stageScene.h"
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
	bossStageMap_Load();													// 파일에 있는 보스 스테이지 맵을 불러와서 벡터로 저장해준다.

	_deathMetal = new deathMetal;
	_deathMetal->init("데스메탈", 12, 14, TESTTILESIZE, TESTTILESIZE);		// 임시로 데스메탈을 해당 위치에 배치했다.

	_player = _stageScene->getPlayerAddress();								// 플레이어 링크
	_ui = _stageScene->getUiAddress();										// ui 링크

	playerPos_Setting();													// 보스 스테이지에 입장 한 플레이어의 위치를 생성 위치를 잡아준다.

	distanceCheck = false;

	return S_OK;
}

void bossStageScene::release()
{
}

void bossStageScene::update()
{
	_deathMetal->update();
	_player->update();
	_ui->update();

	// 플레이어가 보스 근처에 있는지 없는지를 찾아준다.
	closePlayer(_player, _deathMetal);

	// 보스 움직임 연산
	boss_Move_Player();


	if (KEYMANAGER->isToggleKey('V'))
	{
		BEATMANAGER->update();
	}

	// 비트 
	//cout << BEATMANAGER->getInterval() << endl;
}

void bossStageScene::render()
{
	// 맵을 출력해준다.
	if (_vTotalList.size() > 0)
	{
		for (_viTotalList = _vTotalList.begin(); _viTotalList != _vTotalList.end(); _viTotalList++)
		{
			// 타일의 타입이 TYPE_NONE이 아니라면 그려준다.
			if ((*_viTotalList).type != TYPE_NONE)
			{
				//// 타일의 타입, 속성에 따라 이미지를 찾아서 좌표에 뿌려주는 함수
				//findTileImage();
				//
				//if ((*_viTotalList).idY > _deathMetal->getBoss_Index().y)
				//{
				//	// 플레이어와 보스의 인덱스 y를 비교하여 누가 먼저 그려질지 연산해주는 함수
				//	z_Order_Player_Boss();
				//
				//	// 타일의 타입, 속성에 따라 이미지를 찾아서 좌표에 뿌려주는 함수
				//	findTileImage();
				//}
				//
				//if ((*_viTotalList).idY > _player->getPlayer().idy)
				//{
				//	// 플레이어와 보스의 인덱스 y를 비교하여 누가 먼저 그려질지 연산해주는 함수
				//	z_Order_Player_Boss();
				//
				//	// 타일의 타입, 속성에 따라 이미지를 찾아서 좌표에 뿌려주는 함수
				//	findTileImage();
				//}

				//if (_deathMetal->getBoss_Index().y == (*_viTotalList).idY - 1)
				//{
				//	findTileImage();
				//	_deathMetal->render();
				//}
				//else
				//{
				//	_deathMetal->render();
				//	findTileImage();
				//}


				findTileImage();

			}
	
		}
	}
	z_Order_Player_Boss();

	// 월드이미지를 뿌려준다.
	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);

	// UI 출력
	_ui->render();

	// 테스트 비트 출력 토글
	if (KEYMANAGER->isToggleKey('V'))
	{
		BEATMANAGER->render();
	}

}

void bossStageScene::bossStageMap_Load()
{
	// 보스 스테이지 맵을 불러와서 
	// _tiles에 담는다.
	HANDLE file;
	DWORD read;

	file = CreateFile("BossStageFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);

	int i = 0;

	while (i < TILEX * TILEY)
	{
		// 타일의 타입이 NONE이 아니라면 벡터에 담는다.
		if (_tiles[i].type != TYPE_NONE)
		{
			_vTotalList.push_back(_tiles[i]);
		}

		i++;
	}


}

void bossStageScene::findTileImage()
{
	// 지형이 NONE이 아니라면 출력
	if ((*_viTotalList).terrain != TR_NONE)
	{
		//	TR_BASIC_STAGE_TILE, TR_BASIC_COMBO_TILE,
		//	TR_BOSS_STAGE_TILE, TR_BOSS_COMBO_TILE,
		//	TR_STAIR, TR_SHOP,
		//	TR_NONE,
		//	TR_END,
		//	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER
		IMAGEMANAGER->frameRender("terrainTiles", CAMERAMANAGER->getWorldDC(),
			(*_viTotalList).rc.left, (*_viTotalList).rc.top,
			(*_viTotalList).terrainFrameX, (*_viTotalList).terrainFrameY);
	}

	// 벽이 NONE이 아니라면 출력
	if ((*_viTotalList).wall != W_NONE)
	{
		//	W_WALL, W_ITEM_WALL, W_WALL2, W_SHOP_WALL,
		//	W_END_WALL, W_BOSS_WALL,
		//	W_DOOR, W_TORCH, W_FIRE_WALL,
		//	W_NONE
		IMAGEMANAGER->frameRender("wallTiles", CAMERAMANAGER->getWorldDC(),
			(*_viTotalList).rc.left, (*_viTotalList).rc.top - 32,
			(*_viTotalList).wallFrameX, (*_viTotalList).wallFrameY);
	}
	
	// 함정이 NONE이 아니라면 출력
	if ((*_viTotalList).trap != TRAP_NONE)
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
			(*_viTotalList).rc.left, (*_viTotalList).rc.top,
			(*_viTotalList).trapFrameX, (*_viTotalList).trapFrameY);
	}

}

void bossStageScene::z_Order_Player_Boss()
{
	// 보스의 인덱스y가 플레이어의 인덱스y보다 크다면 플레이어를 먼저 그려준다.
	// 그렇지 않다면 보스를 먼저 그려준다.
	if (_deathMetal->getBoss_Index().y > _player->getPlayer().idy)	// 보스가 플레이어보다 앞에 있다.
	{
		_player->render();
		_deathMetal->render();
	}
	else	// 보스가 플레이어보다 뒤에 있다.
	{
		_deathMetal->render();
		_player->render();
	}

}

void bossStageScene::playerPos_Setting()
{
	_player->PlayerAddress()->idx = 12;
	_player->PlayerAddress()->idy = 25;
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



	// 원하는 값을 모두 찾았다면 반복문을 나올때 사용
	bool find_P, find_B;
	find_P = find_B = false;



	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		// 플레이어 인덱스와 같은 타일을 찾아서 렉트의 중점을 구한다.
		if (_vTotalList[i].idX == player->getPlayer().idx && _vTotalList[i].idY == player->getPlayer().idy)
		{
			playerCenter.x = (_vTotalList[i].rc.left + _vTotalList[i].rc.right) / 2;
			playerCenter.y = (_vTotalList[i].rc.top + _vTotalList[i].rc.bottom) / 2;

			// 찾았다면 true
			find_P = true;
		}

		// 보스 인덱스와 같은 타일을 찾아서 렉트의 중점을 구한다.
		if (_vTotalList[i].idX == deathMetal->getBoss_Index().x && _vTotalList[i].idY == deathMetal->getBoss_Index().y)
		{
			bossCenter.x = (_vTotalList[i].rc.left + _vTotalList[i].rc.right) / 2;
			bossCenter.y = (_vTotalList[i].rc.top + _vTotalList[i].rc.bottom) / 2;

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
				deathMetal->ChangeAni();
			}
		}

		if (distanceCheck)
		{
			// 플레이어가 인식 범위 안에 없다면 쉐도우를 입는다.
			if (distance >= TILESIZE * BOSS_RECOGNITION_RANGE)
			{
				distanceCheck = false;
				deathMetal->setBoss_ClosePlayer(false);
				deathMetal->ChangeAni();
			}
		}
	}

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
				deathMetal->ChangeAni();
			}
		}
	
		if (distanceCheck)
		{
			// 플레이어가 인식 범위 안에 없다면 쉐도우를 입는다. 인식범위 예외처리를 해준다.
			if (distance >= (TILESIZE) * (BOSS_RECOGNITION_RANGE - 1) || distance > 165)
			{
				distanceCheck = false;
				deathMetal->setBoss_ClosePlayer(false);
				deathMetal->ChangeAni();
			}
		}
	}
}

void bossStageScene::closePlayer(player* player, slave* slave)
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
		if (_vTotalList[i].idX == player->getPlayer().idx && _vTotalList[i].idY == player->getPlayer().idy)
		{
			playerCenter.x = (_vTotalList[i].rc.left + _vTotalList[i].rc.right) / 2;
			playerCenter.y = (_vTotalList[i].rc.top + _vTotalList[i].rc.bottom) / 2;

			// 찾았다면 true
			find_P = true;
		}

		// 슬레이브 인덱스와 같은 타일을 찾아서 렉트의 중점을 구한다.
		if (_vTotalList[i].idX == slave->get_Slave()->pos.index.x && _vTotalList[i].idY == slave->get_Slave()->pos.index.y)
		{
			slaveCenter.x = (_vTotalList[i].rc.left + _vTotalList[i].rc.right) / 2;
			slaveCenter.y = (_vTotalList[i].rc.top + _vTotalList[i].rc.bottom) / 2;

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
		if (!distanceCheck)
		{
			// 플레이어가 인식 범위 안에 있다면 쉐도우를 벗는다.
			if (distance < TILESIZE * BOSS_RECOGNITION_RANGE)
			{
				distanceCheck = true;
				slave->get_Slave()->b_Value.close_Player = true;
				slave->get_Slave()->b_Value.changeAni = true;
			}
		}

		if (distanceCheck)
		{
			// 플레이어가 인식 범위 안에 없다면 쉐도우를 입는다.
			if (distance >= TILESIZE * BOSS_RECOGNITION_RANGE)
			{
				distanceCheck = false;
				slave->get_Slave()->b_Value.close_Player = false;
				slave->get_Slave()->b_Value.changeAni = true;
			}
		}
	}

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
				slave->get_Slave()->b_Value.close_Player = true;
				slave->get_Slave()->b_Value.changeAni = true;
			}
		}

		if (distanceCheck)
		{
			// 플레이어가 인식 범위 안에 없다면 쉐도우를 입는다. 인식범위 예외처리를 해준다.
			if (distance >= (TILESIZE) * (BOSS_RECOGNITION_RANGE - 1) || distance > 165)
			{
				distanceCheck = false;
				slave->get_Slave()->b_Value.close_Player = false;
				slave->get_Slave()->b_Value.changeAni = true;
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
				// 플레이어가 앞에 있다면 근접 공격을 해준다.
				ui->set_HP();

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
			}
		}
		// x가 음수라면 플레이어는 오른쪽에 있다.
		else
		{
			// 만약 바로 앞에 플레이어가 있을 경우에는 움직임을 멈춘다. ( 또는 근접 공격을 한다.)
			if (deathMetal->getBoss_Index().x + 1 == player->getPlayer().idx
				&& deathMetal->getBoss_Index().y == player->getPlayer().idy)
			{
				// 플레이어가 앞에 있다면 근접 공격을 해준다.
				ui->set_HP();

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
				// 플레이어가 앞에 있다면 근접 공격을 해준다.
				ui->set_HP();

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
			}
		}
		// y가 음수라면 플레이어는 아래쪽에 있다.
		else
		{
			// 만약 바로 앞에 플레이어가 있을 경우에는 움직임을 멈춘다. ( 또는 근접 공격을 한다.)
			if (deathMetal->getBoss_Index().x == player->getPlayer().idx
				&& deathMetal->getBoss_Index().y + 1 == player->getPlayer().idy)
			{
				// 플레이어가 앞에 있다면 근접 공격을 해준다.
				ui->set_HP();

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
			}
		}
	}

}

void bossStageScene::findPlayer(player* player, slave* slave)
{
}

void bossStageScene::boss_Move_Player()
{
	// 데스메탈의 무브 카운트를 1 감소 시켜준다. (데스메탈이 비트를 받지 않았다면 이곳에 들어간다.)
	if (BEATMANAGER->getInterval() && !_deathMetal->getBoss_Beat())
	{
		_deathMetal->setBoss_Beat(true);		// 비트를 받았다면 true로 바꿔준다. (여러번 들어오는것을 방지)
		_deathMetal->setBoss_Move_Count();		// 무브 카운트를 1 감소한다.
	}

	// 비트의 값이 0이 됐을때 false의 값으로 바꿔준다.
	if (!BEATMANAGER->getInterval()) _deathMetal->setBoss_Beat(false);

	// 데스메탈의 무브 카운트가 0이 된다면 이동을 시작 한다.
	if (_deathMetal->getBoss_Move_Count() == 0)
	{
		// 플레이어와 데스메탈의 정보를 이용하여 이동 할 방향을 정한다.
		findPlayer(_player, _deathMetal, _ui);
	}

	cout << _deathMetal->getBoss_Move_Count() << endl;
}
