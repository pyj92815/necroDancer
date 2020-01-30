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
	// ���� ���� 52 -> 2�� ��ȯ  40 x 40 Ÿ���� ����  
	// 
	// �̴ϸ��� ũ�� ( )
	// x, y -> rc left top  ������ �ٿ� => �׸���  




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
				//�ȹ����� �κ�
			}
			continue;
		}
	}
	//// �̿��� ���� 
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

		////�� 
		//enum WALL
		//{
		//	W_WALL, W_ITEM_WALL, W_WALL2, W_SHOP_WALL,		//�⺻ ��, �������� ����ִ� ��, 
		//	W_END_WALL, W_BOSS_WALL,						//�μ����� �ʴ� ��
		//	W_DOOR,											//��. ��ġ, �� ���
		//	W_NONE											//���߿� ����뵵
		//};

		//enum TRAP
		//{
		//	TRAP_FAST_BEAT, TRAP_SLOW_BEAT, TRAP_MUTE,		//���� ���� ���� �� ���Ұ� ����
		//	TRAP_LT_JUMP, TRAP_T_JUMP, TRAP_RT_JUMP,		// �밢�� ���� �����¿� ���� ����
		//	TRAP_L_JUMP, TRAP_R_JUMP,
		//	TRAP_LB_JUMP, TRAP_B_JUMP, TRAP_RB_JUMP,
		//	TRAP_CONFUSE,									//ȥ�� ����
		//	TRAP_BOMB,										//��ź ����
		//	TRAP_NIDDLE,									//���� ����
		//	TRAP_SHADOW, TRAP_NIDDLE_SHADOW,				//���� �׸���
		//	TRAP_NONE
		//};
	}

}
