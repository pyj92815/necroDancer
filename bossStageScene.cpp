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
	_addBossImage->add_BossImage();
	_addBossImage->add_BossAnimation();

	_addSlaveImage->add_SlaveImage();
	_addSlaveImage->add_SlaveAnimation();

	bossStageMap_Load();													// ���Ͽ� �ִ� ���� �������� ���� �ҷ��ͼ� ���ͷ� �������ش�.

	_deathMetal = new deathMetal;
	_deathMetal->init("������Ż", 17, 16, TESTTILESIZE, TESTTILESIZE);		// �ӽ÷� ������Ż�� �ش� ��ġ�� ��ġ�ߴ�.

	_player = _stageScene->getPlayerAddress();								// �÷��̾� ��ũ
	_ui = _stageScene->getUiAddress();										// ui ��ũ

	playerPos_Setting();													// ���� ���������� ���� �� �÷��̾��� ��ġ�� ���� ��ġ�� ����ش�.

	distanceCheck = false;

	_sm = new slaveManager;
	_sm->init();

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
	_sm->update();
	
	// �÷��̾ ���� ��ó�� �ִ��� �������� ã���ش�. (������ ����)
	closePlayer(_player, _deathMetal);

	// �÷��̾ �����̺� ��ó�� �ִ��� �������� ã���ش�.	(������ ����)
	searchSlave(_sm->get_SlaveList(), _player);

	// ���� ������ ����
	boss_Move_Player();

	// �����̺� ������ ����
	slave_Move_Player();

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

	if (KEYMANAGER->isToggleKey('V'))
	{
		BEATMANAGER->update();
	}

}

void bossStageScene::render()
{
	// ���� ������ش�.
	if (_vTotalList.size() > 0)
	{
		for (_viTotalList = _vTotalList.begin(); _viTotalList != _vTotalList.end(); _viTotalList++)
		{
			// Ÿ���� Ÿ���� TYPE_NONE�� �ƴ϶�� �׷��ش�.
			if ((*_viTotalList).type != TYPE_NONE)
			{
	
				// Ÿ���� �Ӽ��� ���� �̹����� �Ѹ���.
				findTileImage();

			}
	
		}
	}

	// ������ �÷��̾��� ���� ������ ã�´�.
	z_Order_Player_Boss();

	// ������ ���� ������ ������ ����Ʈ�� �׷��ش�. (size�� 0 �̻��̶��)
	if (_vEffect.size() > 0)	boss_Base_Attack_Render();

	_sm->render();

	// �����̹����� �ѷ��ش�.
	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);

	// UI ���
	_ui->render();

	// �׽�Ʈ ��Ʈ ��� ���
	if (KEYMANAGER->isToggleKey('V'))
	{
		BEATMANAGER->render();
	}
}

void bossStageScene::bossStageMap_Load()
{
	// ���� �������� ���� �ҷ��ͼ� 
	// _tiles�� ��´�.
	HANDLE file;
	DWORD read;

	file = CreateFile("Boss_SaveFile.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);

	CloseHandle(file);

	int i = 0;

	while (i < TILEX * TILEY)
	{
		// Ÿ���� Ÿ���� NONE�� �ƴ϶�� ���Ϳ� ��´�.
		if (_tiles[i].type != TYPE_NONE)
		{
			_vTotalList.push_back(_tiles[i]);
		}

		i++;
	}


}

void bossStageScene::findTileImage()
{
	// ������ NONE�� �ƴ϶�� ���
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

	// ���� NONE�� �ƴ϶�� ���
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
	
	// ������ NONE�� �ƴ϶�� ���
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
	// ������ �ε���y�� �÷��̾��� �ε���y���� ũ�ٸ� �÷��̾ ���� �׷��ش�.
	// �׷��� �ʴٸ� ������ ���� �׷��ش�.
	if (_deathMetal->getBoss_Index().y > _player->getPlayer().idy)	// ������ �÷��̾�� �տ� �ִ�.
	{
		_player->render();
		_deathMetal->render();

	}
	else	// ������ �÷��̾�� �ڿ� �ִ�.
	{
		_deathMetal->render();
		_player->render();

	}

}

void bossStageScene::playerPos_Setting()
{
	_player->PlayerAddress()->idx = 17;
	_player->PlayerAddress()->idy = 28;
	_player->PlayerAddress()->x = _player->PlayerAddress()->idx * TESTTILESIZE + (TESTTILESIZE / 2);
	_player->PlayerAddress()->y = _player->PlayerAddress()->idy * TESTTILESIZE + (TESTTILESIZE / 3);
	_player->PlayerAddress()->rc = RectMakeCenter(_player->PlayerAddress()->x, _player->PlayerAddress()->y,
		_player->PlayerAddress()->bodyImage->getFrameWidth(), _player->PlayerAddress()->headImage->getFrameHeight());
	CAMERAMANAGER->set_CameraXY(_player->PlayerAddress()->idx * TESTTILESIZE + (TESTTILESIZE / 2),
		_player->PlayerAddress()->idy * TESTTILESIZE + (TESTTILESIZE / 3));
}

void bossStageScene::closePlayer(player* player, deathMetal* deathMetal)
{
	// �÷��̾�� ������ ��Ʈ ������ ��´�.
	POINTFLOAT playerCenter;
	POINTFLOAT bossCenter;
	playerCenter.x = 0;
	playerCenter.y = 0;
	bossCenter.x = 0;
	bossCenter.y = 0;

	// ���ϴ� ���� ��� ã�Ҵٸ� �ݺ����� ���ö� ���
	bool find_P, find_B;
	find_P = find_B = false;



	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		// �÷��̾� �ε����� ���� Ÿ���� ã�Ƽ� ��Ʈ�� ������ ���Ѵ�.
		if (_vTotalList[i].idX == player->getPlayer().idx && _vTotalList[i].idY == player->getPlayer().idy)
		{
			playerCenter.x = (_vTotalList[i].rc.left + _vTotalList[i].rc.right) / 2;
			playerCenter.y = (_vTotalList[i].rc.top + _vTotalList[i].rc.bottom) / 2;

			// ã�Ҵٸ� true
			find_P = true;
		}

		// ���� �ε����� ���� Ÿ���� ã�Ƽ� ��Ʈ�� ������ ���Ѵ�.
		if (_vTotalList[i].idX == deathMetal->getBoss_Index().x && _vTotalList[i].idY == deathMetal->getBoss_Index().y)
		{
			bossCenter.x = (_vTotalList[i].rc.left + _vTotalList[i].rc.right) / 2;
			bossCenter.y = (_vTotalList[i].rc.top + _vTotalList[i].rc.bottom) / 2;
			// ã�Ҵٸ� true
			find_B = true;
		}

		// �� �� ã�Ҵٸ� �ݺ����� ���´�.
		if (find_P && find_B) break;
	}

	// �÷��̾�� ������ �Ÿ��� �����Ѵ�.
	float distance = getDistance(bossCenter.x, bossCenter.y,
		playerCenter.x, playerCenter.y);



	// ���� Ÿ���� �������� 52�� ���������� 0�� ���´ٸ� 52(�翷���Ʒ�)�� �Ÿ��� ��� �Ѵ�.
	if ((int)distance % TILESIZE == 0)
	{
		// �Ÿ��� �޶������� ���� �ٲ�� ������ �ѹ��� ������ �ȴ�.
		if (!distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� �ִٸ� �����츦 ���´�.
			if (distance < TILESIZE * BOSS_RECOGNITION_RANGE)
			{
				distanceCheck = true;
				deathMetal->setBoss_ClosePlayer(true);
				//deathMetal->ChangeAni();
			}
		}

		if (distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� ���ٸ� �����츦 �Դ´�.
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

	// ���� Ÿ�� �������� 52�� ���������� 0�� ������ �ʴ´ٸ� �밢���̶�� ��
	else
	{
		// �Ÿ��� �޶������� ���� �ٲ�� ������ �ѹ��� ������ �ȴ�.
		if (!distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� �ִٸ� �����츦 ���´�. �νĹ��� ����ó���� ���ش�.
			if (distance < (TILESIZE) * (BOSS_RECOGNITION_RANGE - 1) && distance < 165)
			{
				distanceCheck = true;
				deathMetal->setBoss_ClosePlayer(true);
				//deathMetal->ChangeAni();
			}
		}
	
		if (distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� ���ٸ� �����츦 �Դ´�. �νĹ��� ����ó���� ���ش�.
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
	// �÷��̾�� �����̺��� ��Ʈ ������ ��´�.
	POINTFLOAT playerCenter;
	POINTFLOAT slaveCenter;



	// ���ϴ� ���� ��� ã�Ҵٸ� �ݺ����� ���ö� ���
	bool find_P, find_S;
	find_P = find_S = false;



	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		// �÷��̾� �ε����� ���� Ÿ���� ã�Ƽ� ��Ʈ�� ������ ���Ѵ�.
		if (_vTotalList[i].idX == player->getPlayer().idx && _vTotalList[i].idY == player->getPlayer().idy)
		{
			playerCenter.x = (_vTotalList[i].rc.left + _vTotalList[i].rc.right) / 2;
			playerCenter.y = (_vTotalList[i].rc.top + _vTotalList[i].rc.bottom) / 2;

			// ã�Ҵٸ� true
			find_P = true;
		}

		// �����̺� �ε����� ���� Ÿ���� ã�Ƽ� ��Ʈ�� ������ ���Ѵ�.
		if (_vTotalList[i].idX == slave->pos.index.x && _vTotalList[i].idY == slave->pos.index.y)
		{
			slaveCenter.x = (_vTotalList[i].rc.left + _vTotalList[i].rc.right) / 2;
			slaveCenter.y = (_vTotalList[i].rc.top + _vTotalList[i].rc.bottom) / 2;

			// ã�Ҵٸ� true
			find_S = true;
		}

		// �� �� ã�Ҵٸ� �ݺ����� ���´�.
		if (find_P && find_S) break;
	}



	// �÷��̾�� �����̺��� �Ÿ��� �����Ѵ�.
	float distance = getDistance(slaveCenter.x, slaveCenter.y,
		playerCenter.x, playerCenter.y);


	// ���� Ÿ���� �������� 52�� ���������� 0�� ���´ٸ� 52(�翷���Ʒ�)�� �Ÿ��� ��� �Ѵ�.
	if ((int)distance % TILESIZE == 0)
	{
		// �Ÿ��� �޶������� ���� �ٲ�� ������ �ѹ��� ������ �ȴ�.
		if (!slave->b_Value.distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� �ִٸ� �����츦 ���´�.
			if (distance < TILESIZE * BOSS_RECOGNITION_RANGE)
			{
				slave->b_Value.distanceCheck = true;
				slave->b_Value.isClosePlayer = true;
			}
		}

		if (slave->b_Value.distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� ���ٸ� �����츦 �Դ´�.
			if (distance >= TILESIZE * BOSS_RECOGNITION_RANGE)
			{
				slave->b_Value.distanceCheck = false;
				slave->b_Value.isClosePlayer = false;
			}
		}
	}

	// ���� Ÿ�� �������� 52�� ���������� 0�� ������ �ʴ´ٸ� �밢���̶�� ��
	else
	{
		// �Ÿ��� �޶������� ���� �ٲ�� ������ �ѹ��� ������ �ȴ�.
		if (!slave->b_Value.distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� �ִٸ� �����츦 ���´�. �νĹ��� ����ó���� ���ش�.
			if (distance < (TILESIZE) * (BOSS_RECOGNITION_RANGE - 1) && distance < 165)
			{
				slave->b_Value.distanceCheck = true;
				slave->b_Value.isClosePlayer = true;
			}
		}

		if (slave->b_Value.distanceCheck)
		{
			// �÷��̾ �ν� ���� �ȿ� ���ٸ� �����츦 �Դ´�. �νĹ��� ����ó���� ���ش�.
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

	// ������ �ε������� �÷��̾��� �ε����� ���� ���� ��Ƶд�. (�÷��̾��� ��ġ�� ã��, ��� ������ ������� �񱳿��� ����� ��)
	int x = deathMetal->getBoss_Index().x - player->getPlayer().idx;
	int y = deathMetal->getBoss_Index().y - player->getPlayer().idy;


	// x�� ª�ٸ� flase, y�� ª�ٸ� true�� ���� �����Ѵ�.
	bool x_OR_y = false; 

	// ��ȣ�� ���ּ� ��� ������ �� ª������ ã���ش�. (ª�� ������� ���� ã�� �ȴ�.)
	if (abs(x) > abs(y))
	{
		// y�� �� ª�ٸ� true�� �־��ش�.
		x_OR_y = true;
	}
	else
	{
		// x�� �� ª�ٸ� false�� �־��ش�.
		x_OR_y = false;
	}

	// x, y �߿� x�� �� ª�ٸ� x���� ã���ش�.
	if (x_OR_y)
	{
		// x�� ������ �÷��̾�� ���ʿ� �ִ�.
		if (x > 0)
		{
			// ���� �ٷ� �տ� �÷��̾ ���� ��쿡�� �������� �����. ( �Ǵ� ���� ������ �Ѵ�.)
			if (deathMetal->getBoss_Index().x - 1 == player->getPlayer().idx
				&& deathMetal->getBoss_Index().y == player->getPlayer().idy)
			{
				// �÷��̾ �տ� �ִٸ� ���� ������ ���ش�.
				ui->set_HP();

				// �÷��̾�� ���� ���� ����Ʈ�� �׷��ش�.
				boss_Base_Attack_Render("base_Attack", player);

				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_LEFT);
				
				//// �÷��̾��� ���� ��ǥ�� �޾ƿ´�.
				//deathMetal->setBoss_BaseAttack_Pos(player->getPlayer().x, player->getPlayer().y);
				//
				//// ����Ʈ �̹����� �־��ش�.
				//deathMetal->setBoss_BaseSkill_Image("base_Attack");
				//
				//// � ����Ʈ�� �Ѹ��� �־��ش�.
				//deathMetal->setBoss_BaseSkill("Base_Attack");
				//
				//// ����Ʈ�� ���� ��Ų��.
				//deathMetal->start_AttackAni();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}

			// �÷��̾ ���ٸ� �̵��� ���ش�.
			else
			{
				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_LEFT);

				// ������������ ����� ���� �ð��� ���� ���ش�.
				deathMetal->setBoss_WorldTime(TIMEMANAGER->getWorldTime());

				// �̵� ���꿡 �ʿ��� bool ���� true�� �ٲ��ִ� �Լ�
				deathMetal->setBoss_Move_BoolValue_Ture();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}
		}
		// x�� ������� �÷��̾�� �����ʿ� �ִ�.
		else
		{
			// ���� �ٷ� �տ� �÷��̾ ���� ��쿡�� �������� �����. ( �Ǵ� ���� ������ �Ѵ�.)
			if (deathMetal->getBoss_Index().x + 1 == player->getPlayer().idx
				&& deathMetal->getBoss_Index().y == player->getPlayer().idy)
			{
				// �÷��̾ �տ� �ִٸ� ���� ������ ���ش�.
				ui->set_HP();

				// �÷��̾�� ���� ���� ����Ʈ�� �׷��ش�.
				boss_Base_Attack_Render("base_Attack", player);

				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_RIGHT);

				//// �÷��̾��� ���� ��ǥ�� �޾ƿ´�.
				//deathMetal->setBoss_BaseAttack_Pos(player->getPlayer().x, player->getPlayer().y);
				//
				//// ����Ʈ �̹����� �־��ش�.
				//deathMetal->setBoss_BaseSkill_Image("base_Attack");
				//
				//// � ����Ʈ�� �Ѹ��� �־��ش�.
				//deathMetal->setBoss_BaseSkill("Base_Attack");
				//
				//// ����Ʈ�� ���� ��Ų��.
				//deathMetal->start_AttackAni();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}

			// �÷��̾ ���ٸ� �̵��� ���ش�.
			else
			{
				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_RIGHT);

				// ������������ ����� ���� �ð��� ���� ���ش�.
				deathMetal->setBoss_WorldTime(TIMEMANAGER->getWorldTime());

				// �̵� ���꿡 �ʿ��� bool ���� true�� �ٲ��ִ� �Լ�
				deathMetal->setBoss_Move_BoolValue_Ture();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}
		}
	}

	// x, y �߿� y�� �� ª�ٸ� y���� ã���ش�.
	if (!x_OR_y)
	{
		// y�� ������ �÷��̾�� ���ʿ� �ִ�.
		if (y > 0)
		{
			// ���� �ٷ� �տ� �÷��̾ ���� ��쿡�� �������� �����. ( �Ǵ� ���� ������ �Ѵ�.)
			if (deathMetal->getBoss_Index().x == player->getPlayer().idx
				&& deathMetal->getBoss_Index().y - 1 == player->getPlayer().idy)
			{
				// �÷��̾ �տ� �ִٸ� ���� ������ ���ش�.
				ui->set_HP();

				// �÷��̾�� ���� ���� ����Ʈ�� �׷��ش�.
				boss_Base_Attack_Render("base_Attack", player);

				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_UP);

				//// �÷��̾��� ���� ��ǥ�� �޾ƿ´�.
				//deathMetal->setBoss_BaseAttack_Pos(player->getPlayer().x, player->getPlayer().y);
				//
				//// ����Ʈ �̹����� �־��ش�.
				//deathMetal->setBoss_BaseSkill_Image("base_Attack");
				//
				//// � ����Ʈ�� �Ѹ��� �־��ش�.
				//deathMetal->setBoss_BaseSkill("Base_Attack");
				//
				//// ����Ʈ�� ���� ��Ų��.
				//deathMetal->start_AttackAni();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}

			// �÷��̾ ���ٸ� �̵��� ���ش�.
			else
			{
				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_UP);

				// ������������ ����� ���� �ð��� ���� ���ش�.
				deathMetal->setBoss_WorldTime(TIMEMANAGER->getWorldTime());

				// �̵� ���꿡 �ʿ��� bool ���� true�� �ٲ��ִ� �Լ�
				deathMetal->setBoss_Move_BoolValue_Ture();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}
		}
		// y�� ������� �÷��̾�� �Ʒ��ʿ� �ִ�.
		else
		{
			// ���� �ٷ� �տ� �÷��̾ ���� ��쿡�� �������� �����. ( �Ǵ� ���� ������ �Ѵ�.)
			if (deathMetal->getBoss_Index().x == player->getPlayer().idx
				&& deathMetal->getBoss_Index().y + 1 == player->getPlayer().idy)
			{
				// �÷��̾ �տ� �ִٸ� ���� ������ ���ش�.
				ui->set_HP();

				// �÷��̾�� ���� ���� ����Ʈ�� �׷��ش�.
				boss_Base_Attack_Render("base_Attack", player);

				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_DOWN);

				//// �÷��̾��� ���� ��ǥ�� �޾ƿ´�.
				//deathMetal->setBoss_BaseAttack_Pos(player->getPlayer().x, player->getPlayer().y);
				//
				//// ����Ʈ �̹����� �־��ش�.
				//deathMetal->setBoss_BaseSkill_Image("base_Attack");
				//
				//// � ����Ʈ�� �Ѹ��� �־��ش�.
				//deathMetal->setBoss_BaseSkill("Base_Attack");
				//
				//// ����Ʈ�� ���� ��Ų��.
				//deathMetal->start_AttackAni();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}

			// �÷��̾ ���ٸ� �̵��� ���ش�.
			else
			{

				// ���⼭ ������ �����ְ�, ���� bool ���� ���ش�.
				deathMetal->setBoss_Direction(BD_DOWN);

				// ������������ ����� ���� �ð��� ���� ���ش�.
				deathMetal->setBoss_WorldTime(TIMEMANAGER->getWorldTime());

				// �̵� ���꿡 �ʿ��� bool ���� true�� �ٲ��ִ� �Լ�
				deathMetal->setBoss_Move_BoolValue_Ture();

				// ���� �̵��� ���� ���� ī��Ʈ�� �ٽ� ä���ش�.
				deathMetal->setBoss_Move_Count(deathMetal->getBoss_Move_Count_Value());
			}
		}
	}

}

SLAVE_DIRECTION bossStageScene::findPlayer(player* player, SLAVE_INFO* slave)
{
	// �÷��̾��� ������ ��Ƽ� ������ ���ϰ����� �����ش�.

	// �÷��̾��� ������ ã�´�.

	// x, y �� ª������ �����Ѵ�.

	// �̵� �� �̵� �Ұ��� ������Ʈ�� ã�´�.
	
	// ������ �ٸ� ��������

	// x, y �� ���� ���ο� �����Ѵٸ� ���� �������θ� �̵��� �Ѵ�.

	// �����̺�� �÷��̾��� Ÿ�� ������ ���Ѵ�.
	POINTFLOAT playerCenter;
	POINTFLOAT slaveCenter;
	playerCenter.x = 0;
	playerCenter.y = 0;
	slaveCenter.x = 0;
	slaveCenter.y = 0;

	// �� �� ���ϴ� ���� ã������ �ݺ������� �������´�.
	bool findPlayer, findSlave;
	findPlayer = findSlave = false;

	// �����ʿ��� �ش� �ε����� ã�� ���� �ݺ�.
	for (_viTotalList = _vTotalList.begin(); _viTotalList != _vTotalList.end(); ++_viTotalList)
	{
		// �÷��̾��� �ε����� ���� Ÿ���� ã�´�.
		if ((*_viTotalList).idX == player->getPlayer().idx && (*_viTotalList).idY == player->getPlayer().idy)
		{
			// Ÿ���� ��Ʈ�� �̿��Ͽ� ������ �����Ѵ�.
			playerCenter.x = ((*_viTotalList).rc.left + (*_viTotalList).rc.right) / 2;
			playerCenter.y = ((*_viTotalList).rc.top + (*_viTotalList).rc.bottom) / 2;

			findPlayer = true;
		}

		// �����̺��� �ε����� ���� Ÿ���� ã�´�.
		if ((*_viTotalList).idX == slave->pos.index.x && (*_viTotalList).idY == slave->pos.index.y)
		{
			// Ÿ���� ��Ʈ�� �̿��Ͽ� ������ �����Ѵ�.
			slaveCenter.x = ((*_viTotalList).rc.left + (*_viTotalList).rc.right) / 2;
			slaveCenter.y = ((*_viTotalList).rc.top + (*_viTotalList).rc.bottom) / 2;

			findSlave = true;
		}

		// ���� ��� ã�Ҵٸ� �ݺ������� ���´�.
		if (findPlayer && findSlave) break;
	}

	// �����̺�� �÷��̾���� x, y�� ���� ��´�. (�����̺� �������� ���ش�.)
	POINTFLOAT range;
	range.x = slaveCenter.x - playerCenter.x;
	range.y = slaveCenter.y - playerCenter.y;

	// x, y �� ª������ ���Ѵ�.
	SHORT_XY short_XY = SHORT_XY::SHORT_NONE;

	// x�� ª��.
	if (range.x < range.y)
	short_XY = SHORT_XY::SHORT_X;

	// y�� ª��.
	if (range.x > range.y)
	short_XY = SHORT_XY::SHORT_Y;


	// �����̺�� �÷��̾��� �ε��� �� ������ �ִٸ� �� ������ ���� �ϰ� ã�´�.
	FIND_CHOICE_XY find_Choice = FIND_CHOICE_XY::FC_XY;	// 0 = ����� ���, 1 = x ���⸸ ã�´�. 2 = y ���⸸ ã�´�.

	// �÷��̾��� x�� �����̺��� x�� ���ٸ� x ������ �����Ѱ� y������ ã���� �Ѵ�.
	if (player->getPlayer().idx == slave->pos.index.x)	find_Choice = FIND_CHOICE_XY::FC_Y;
	if (player->getPlayer().idy == slave->pos.index.y)	find_Choice = FIND_CHOICE_XY::FC_X;

	// �÷��̾��� ������ ã�´�. (�÷��̾ �ִ� ������ ���Ѵ�.)
	float player_Pos_Angle = 0;
	player_Pos_Angle = getAngle(slaveCenter.x, slaveCenter.y, playerCenter.x, playerCenter.y);

	// ���� ������ 0 ���Ϸ� ���´ٸ� (�������ش�. -������ +��)
	if (player_Pos_Angle < 0)
	{
		float tempAngle = 0;
		tempAngle = PI + player_Pos_Angle;
		player_Pos_Angle = PI + tempAngle;
	}

	// �÷��̾��� ������ �����Ѵ�.
	FIND_ANGLE find_Angle = FIND_ANGLE::FA_RT;		// 0 = 2��, 1 = 10��, 2 = 7��, 3 = 5��

	if (player_Pos_Angle > 0 && player_Pos_Angle < 1.57)	find_Angle = FIND_ANGLE::FA_RT;
	if (player_Pos_Angle > 1.57 && player_Pos_Angle < 3.14) find_Angle = FIND_ANGLE::FA_TL;
	if (player_Pos_Angle > 3.14 && player_Pos_Angle < 4.71) find_Angle = FIND_ANGLE::FA_LB;
	if (player_Pos_Angle > 4.71 && player_Pos_Angle < (PI * 2)) find_Angle = FIND_ANGLE::FA_BR;

	// �÷��̾��� �������� �̵��� �����Ѵ�.
	// x, y �� ª�� �������� ã�´�.
	if (find_Choice == FIND_CHOICE_XY::FC_XY)
	{

	}

	// y ���⸸ ã���� �ȴ�.
	if (find_Choice == FIND_CHOICE_XY::FC_Y)
	{

	}

	// x ���⸸ ã���� �ȴ�.
	if (find_Choice == FIND_CHOICE_XY::FC_X)
	{

	}

	// ���� ������Ʈ�� �߰� �Ѵٸ� �̵��� ���߰ų�

	return SLAVE_DIRECTION::SD_DOWN;
}

void bossStageScene::boss_Move_Player()
{
	//// ������Ż�� ���� ī��Ʈ�� 1 ���� �����ش�. (������Ż�� ��Ʈ�� ���� �ʾҴٸ� �̰��� ����.)
	//if (BEATMANAGER->getInterval() && !_deathMetal->getBoss_Beat())
	//{
	//	_deathMetal->setBoss_Beat(true);		// ��Ʈ�� �޾Ҵٸ� true�� �ٲ��ش�. (������ �����°��� ����)
	//	_deathMetal->setBoss_Move_Count();		// ���� ī��Ʈ�� 1 �����Ѵ�.
	//}
	//
	//// ��Ʈ�� ���� 0�� ������ false�� ������ �ٲ��ش�.
	//if (!BEATMANAGER->getInterval()) _deathMetal->setBoss_Beat(false);

	// ������Ż�� ���� ī��Ʈ�� 1 ���� �����ش�. (������Ż�� ��Ʈ�� ���� �ʾҴٸ� �̰��� ����.)
	if (BEATMANAGER->getBeating() && !_deathMetal->getBoss_Beat())
	{
		_deathMetal->setBoss_Beat(true);		// ��Ʈ�� �޾Ҵٸ� true�� �ٲ��ش�. (������ �����°��� ����)
		_deathMetal->setBoss_Move_Count();		// ���� ī��Ʈ�� 1 �����Ѵ�.
	}

	// ��Ʈ�� ���� 0�� ������ false�� ������ �ٲ��ش�.
	if (!BEATMANAGER->getBeating()) _deathMetal->setBoss_Beat(false);

	// ������Ż�� ���� ī��Ʈ�� 0 ���ϰ� �ȴٸ� �̵��� ���� �Ѵ�.
	if (_deathMetal->getBoss_Move_Count() < 0)
	{
		// �÷��̾�� ������Ż�� ������ �̿��Ͽ� �̵� �� ������ ���Ѵ�.
		findPlayer(_player, _deathMetal, _ui);
	}


}

void bossStageScene::slave_Move_Player()
{
	// �����̺갡 1���� �̻� ���� �Ǿ�߸� ����.
	if (_sm->get_SlaveList().size() > 0)
	{
		for (int i = 0; i < _sm->get_SlaveList().size(); ++i)
		{
			// �����̺��� ���� ī��Ʈ�� 1 ���� �����ش�. (�����̺갡 ��Ʈ�� ���� �ʾҴٸ� �̰��� ����.)
			if (BEATMANAGER->getBeating() && !_sm->get_SlaveList()[i]->get_Slave()->b_Value.beat)
			{
				_sm->get_SlaveList()[i]->get_Slave()->b_Value.beat = true;		// ��Ʈ�� �޾Ҵٸ� true�� �ٲ��ش�.
				_sm->get_SlaveList()[i]->get_Slave()->operation.move_Count--;	// ���� ī��Ʈ�� 1 �����Ѵ�.
			}

			// ��Ʈ ���� 0�� �ɶ� false�� ������ �ٲ��ش�.
			if (!BEATMANAGER->getBeating()) _sm->get_SlaveList()[i]->get_Slave()->b_Value.beat = false;

			// �����̺��� ���� ī��Ʈ�� 0 ���ϰ� �ȴٸ� �̵��� �����Ѵ�.
			if (_sm->get_SlaveList()[i]->get_Slave()->operation.move_Count < 0)
			{
				// �����̺� ������ ������, ������ �����ְ� �̵�?
				//_sm->get_SlaveList()[i]->move(findPlayer(_player, _sm->get_SlaveList()[i]->get_Slave()));
				findPlayer(_player, _sm->get_SlaveList()[i]->get_Slave());
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

		// �̹����� �׷��ְ� ���� ���������� �Ѱ��ش�.
		(*_viEffect)->img->setFrameX((*_viEffect)->img->getFrameX() + 1);

		// ���� �ִ� ������ �̻��̶�� ���͸� �����ش�.
		if ((*_viEffect)->img->getFrameX() >= (*_viEffect)->Max_FrameX)
		{
			_vEffect.erase(_viEffect);

			break;
		}
	}
}

void bossStageScene::boss_Base_Attack_Render(string skillName, player* player)
{
	// ������ ������ ������ �� Ÿ�� ��ġ�� ����Ʈ�� �����ش�.
	// �ִϸ��̼� ���� �ʰ� ������ ������ �׸��ٰ� ������ �̹��� ��� ��
	// ���� ������ �ϴ°ɷ�?
	// ���ʹ� ��� ����?

	// �ѷ��� �̹����� �ѷ��� ��ǥ�� �ӽ÷� ���� �ϴ� ������ �����. + ���� �Ҵ�
	// �÷��̾��� ��Ʈ�� �̹����� �Ѹ���, �������� ��� �����ٸ� ���͸� ���� ���ش�.
	BOSS_STAGE_EFFECT_VECTOR* temp_Effect = new BOSS_STAGE_EFFECT_VECTOR;
	temp_Effect->img = IMAGEMANAGER->findImage(skillName);
	temp_Effect->img->setFrameX(0);
	temp_Effect->img->setFrameY(0);
	temp_Effect->Max_FrameX = temp_Effect->img->getMaxFrameX();
	temp_Effect->rc = RectMake(player->getPlayer().idx * TILESIZE, player->getPlayer().idy * TILESIZE,
		TILESIZE, TILESIZE);
	// ����Ʈ�� �ѷ��� ���� ��ǥ�� �ѷ��� ����Ʈ �̹����� ��� ����
	_vEffect.push_back(temp_Effect);
}
