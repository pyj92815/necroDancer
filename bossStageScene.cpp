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
	bossStageMap_Load();	// ���Ͽ� �ִ� ���� �������� ���� �ҷ��ͼ� ���ͷ� �������ش�.

	_deathMetal = new deathMetal;
	_deathMetal->init("������Ż", 5, 5, TESTTILESIZE, TESTTILESIZE);		// �ӽ÷� ������Ż�� �ش� ��ġ�� ��ġ�ߴ�.

	_player = _stageScene->getPlayerAddress();							// �÷��̾� ��ũ
	_ui = _stageScene->getUiAddress();									// ui ��ũ

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
				//// Ÿ���� Ÿ��, �Ӽ��� ���� �̹����� ã�Ƽ� ��ǥ�� �ѷ��ִ� �Լ�
				//findTileImage();
				//
				//if ((*_viTotalList).idY > _deathMetal->getBoss_Index().y)
				//{
				//	// �÷��̾�� ������ �ε��� y�� ���Ͽ� ���� ���� �׷����� �������ִ� �Լ�
				//	z_Order_Player_Boss();
				//
				//	// Ÿ���� Ÿ��, �Ӽ��� ���� �̹����� ã�Ƽ� ��ǥ�� �ѷ��ִ� �Լ�
				//	findTileImage();
				//}
				//
				//if ((*_viTotalList).idY > _player->getPlayer().idy)
				//{
				//	// �÷��̾�� ������ �ε��� y�� ���Ͽ� ���� ���� �׷����� �������ִ� �Լ�
				//	z_Order_Player_Boss();
				//
				//	// Ÿ���� Ÿ��, �Ӽ��� ���� �̹����� ã�Ƽ� ��ǥ�� �ѷ��ִ� �Լ�
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

	file = CreateFile("BossStageFile.map", GENERIC_READ, 0, NULL,
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
