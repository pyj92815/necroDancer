#include "stdafx.h"
#include "miniMap.h"

miniMap::miniMap()
{
}

miniMap::~miniMap()
{
}

HRESULT miniMap::init()
{
	// 가로 세로 52 -> 2로 변환  40 x 40 타일의 개수  
	// 
	// 미니맵의 크기 ( )
	// x, y -> rc left top  비율로 줄여 => 그리기  




	return S_OK;
}

void miniMap::release()
{

}

void miniMap::update()
{
}

void miniMap::render()
{
	int i = -1;

	for (_viStageMap = _vStageMap.begin(); _viStageMap != _vStageMap.end(); ++_viStageMap)
	{
		i++;
		if ((*_viStageMap)->type == TYPE_NONE) continue;
		if ((*_viStageMap)->terrain != TR_NONE)
		{
			if ((*_viStageMap)->alphaValue <= 0)
			{
				IMAGEMANAGER->findImage("terrainTiles")->frameRender(CAMERAMANAGER->getWorldDC(), 
					(*_viStageMap)->rc.left, (*_viStageMap)->rc.top, (*_viStageMap)->terrainFrameX, (*_viStageMap)->terrainFrameY);

			}
			else
			{
				IMAGEMANAGER->findImage("terrainTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(),
					(*_viStageMap)->rc.left, (*_viStageMap)->rc.top, (*_viStageMap)->terrainFrameX, (*_viStageMap)->terrainFrameY, (*_viStageMap)->alphaValue);
				//안밝혀진 부분
			}
			continue;
		}
	}
	//// 이외의 렌더 
	for (_viStageMap = _vStageMap.begin(); _viStageMap != _vStageMap.end(); ++_viStageMap)
	{
		if ((*_viStageMap)->type == TYPE_NONE) continue;
		if ((*_viStageMap)->alphaValue <= 0)
		{
			if ((*_viStageMap)->wall != W_NONE)
			{
				IMAGEMANAGER->findImage("wallTiles")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viStageMap)->rc.left, (*_viStageMap)->rc.top - 52, (*_viStageMap)->wallFrameX, (*_viStageMap)->wallFrameY);
				continue;
			}
			if ((*_viStageMap)->trap != TRAP_NONE)
			{
				IMAGEMANAGER->findImage("trapTiles")->frameRender(CAMERAMANAGER->getWorldDC(), (*_viStageMap)->rc.left, (*_viStageMap)->rc.top, (*_viStageMap)->trapFrameX, (*_viStageMap)->trapFrameY);
				continue;
			}

			//if ((*_viStageMap)->terrain != TR_BASIC_STAGE_TILE, TR_BASIC_COMBO_TILE,
			//		TR_BOSS_STAGE_TILE, TR_BOSS_COMBO_TILE,
			//		TR_STAIR, TR_SHOP,
			//		TR_NONE,
			//		TR_END,
			//		TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER)
			//{
			//	HBRUSH brush = CreateSolidBrush(RGB(255, 1, 2));
			//	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			//	RECT temp;
			//	//temp = RectMake(750+(i%130*4), 450+(i/130*4),
			//		//4, 4);
			//	temp = RectMake(750 + (*_viStageMap)->rc.left / 10, 450 + (*_viStageMap)->rc.top / 10,
			//		4, 4);
			//	Rectangle(getMemDC(), temp);
			//	SelectObject(getMemDC(), oldBrush);
			//	DeleteObject(brush);
			//}

		}
		else
		{
			if ((*_viStageMap)->wall != W_NONE)
			{
				IMAGEMANAGER->findImage("wallTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), (*_viStageMap)->rc.left, (*_viStageMap)->rc.top, (*_viStageMap)->wallFrameX, (*_viStageMap)->wallFrameY, (*_viStageMap)->alphaValue);
				continue;
			}
			if ((*_viStageMap)->trap != TRAP_NONE)
			{
				IMAGEMANAGER->findImage("trapTiles")->alphaFrameRender(CAMERAMANAGER->getWorldDC(), (*_viStageMap)->rc.left, (*_viStageMap)->rc.top, (*_viStageMap)->trapFrameX, (*_viStageMap)->trapFrameY, (*_viStageMap)->alphaValue);
				continue;
			}
		}

		//enum TERRAIN
		//{
		//	TR_BASIC_STAGE_TILE, TR_BASIC_COMBO_TILE,
		//	TR_BOSS_STAGE_TILE, TR_BOSS_COMBO_TILE,
		//	TR_STAIR, TR_SHOP,
		//	TR_NONE,
		//	TR_END,
		//	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER
		//};

		////벽 
		//enum WALL
		//{
		//	W_WALL, W_ITEM_WALL, W_WALL2, W_SHOP_WALL,		//기본 벽, 아이템이 들어있는 벽, 
		//	W_END_WALL, W_BOSS_WALL,						//부셔지지 않는 벽
		//	W_DOOR,											//문. 토치, 불 기둥
		//	W_NONE											//나중에 지울용도
		//};

		//enum TRAP
		//{
		//	TRAP_FAST_BEAT, TRAP_SLOW_BEAT, TRAP_MUTE,		//리듬 템포 함정 및 음소거 함정
		//	TRAP_LT_JUMP, TRAP_T_JUMP, TRAP_RT_JUMP,		// 대각선 포함 상하좌우 점프 함정
		//	TRAP_L_JUMP, TRAP_R_JUMP,
		//	TRAP_LB_JUMP, TRAP_B_JUMP, TRAP_RB_JUMP,
		//	TRAP_CONFUSE,									//혼란 함정
		//	TRAP_BOMB,										//폭탄 함정
		//	TRAP_NIDDLE,									//가시 함정
		//	TRAP_SHADOW, TRAP_NIDDLE_SHADOW,				//함정 그림자
		//	TRAP_NONE
		//};
	}

}
