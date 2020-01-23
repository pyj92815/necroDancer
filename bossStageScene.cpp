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
	bossStageMap_Load();	// 파일에 있는 보스 스테이지 맵을 불러와서 벡터로 저장해준다.

	_deathMetal = new deathMetal;
	_deathMetal->init("데스메탈", 5, 5, TESTTILESIZE, TESTTILESIZE);

	_player = _stageScene->getPlayerAddress();
	_ui = _stageScene->getUiAddress();

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
				// 타일의 타입, 속성에 따라 이미지를 찾아서 좌표에 뿌려주는 함수
				findTileImage();
			}
	
		}
	}

	_deathMetal->render();
	_player->render();
	CAMERAMANAGER->getWorldImage()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraX(), CAMERAMANAGER->get_CameraY(), WINSIZEX, WINSIZEY);
	_ui->render();

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
