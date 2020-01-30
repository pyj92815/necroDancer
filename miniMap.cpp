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

	_r = _g = _b = 0;

	_em = new EnemyManager;


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
	//enum OBJECT
	//{
	//	OBJ_WATER,										//�ٴۿ� �ѷ����� ������Ʈ
	//	OBJ_FALLING_DOOR,								//�������� �ٴ�
	//};
	
	for (_viStageMap = _vStageMap.begin(); _viStageMap != _vStageMap.end(); ++_viStageMap)
	{
		if ((*_viStageMap)->type == TYPE_NONE) continue;

		switch ((*_viStageMap)->type)
		{
		case TYPE_TERRAIN:
			if ((*_viStageMap)->terrain == TR_STAIR)
			{
				_r = 255;
				_g = 10;
				_b = 255;
			}
			else if ((*_viStageMap)->terrain == TR_SHOP ) //else if�� �ϸ� �����Ÿ� ����ó�� �� �ʿ䰡 ������..
			{
				_r = 255;
				_g = 255;
				_b = 0;
			}
			else if ((*_viStageMap)->terrain == TR_END)
			{
				_r = 153;
				_g = 153;
				_b = 153;
			}
			else
			{
				_r = 220;
				_g = 220;
				_b = 220;
			}
			break;
		case TYPE_WALL:
			if ((*_viStageMap)->wall == W_ITEM_WALL || (*_viStageMap)->wall == W_SHOP_WALL)
			{
				_r = 255;
				_g = 255;
				_b = 0;
			}
			else if ((*_viStageMap)->wall == W_WALL2 || (*_viStageMap)->wall == W_BOSS_WALL)
			{
				_r = 102;
				_g = 51;
				_b = 0;
			}
			else if ((*_viStageMap)->wall == W_DOOR)
			{
				_r = 0;
				_g = 255;
				_b = 0;
			}
			else if ((*_viStageMap)->wall == W_END_WALL)
			{
				_r = 153;
				_g = 153;
				_b = 153;
			}
			else
			{
				_r = 153;
				_g = 102;
				_b = 0;
			}
			break;
		case TYPE_TRAP:
			if ((*_viStageMap)->trap == TRAP_SHADOW || (*_viStageMap)->trap == TRAP_NIDDLE_SHADOW)
			{
				_r = 0;
				_g = 0;
				_b = 0;

			}
			else
			{
				_r = 210;
				_g = 255;
				_b = 255;
			}
			break;
		case TYPE_ITEM_ARMOR:
			if ((*_viStageMap)->armor == A_NONE)
			{

			}
			else
			{
				_r = 255;
				_g = 255;
				_b = 0;
			}
			break;
		case TYPE_ITEM_WEAPON:
			if ((*_viStageMap)->weapon == WP_NONE)
			{

			}
			else
			{
				_r = 255;
				_g = 255;
				_b = 0;
			}
			break;
		case TYPE_ITEM_STUFF:
			if ((*_viStageMap)->stuff == ST_NONE)
			{

			}
			else
			{
				_r = 255;
				_g = 255;
				_b = 0;
			}
			break;
		case TYPE_OBJECT:
			if ((*_viStageMap)->obj == OBJ_WATER)
			{
				_r = 50;
				_g = 50;
				_b = 255;
			}
			else if ((*_viStageMap)->obj == OBJ_FALLING_DOOR)
			{
				_r = 210;
				_g = 255;
				_b = 255;
			}
			break;
		case TYPE_ENEMY:
			_r = 255;
			_g = 0;
			_b = 0;
			break;
		case TYPE_CHARACTER:
			_r = 255;
			_g = 0;
			_b = 0;
			break;
		case TYPE_NONE:
			break;
		default:
			break;
		}
		if ((*_viStageMap)->alphaValue <= 0)
		{
		HBRUSH brush = CreateSolidBrush(RGB(_r, _g, _b));
		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		HPEN pen = CreatePen(PS_SOLID,2,RGB(_r, _g, _b));
		HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
		RECT temp = RectMake(750 + (*_viStageMap)->rc.left / 10, 450 + (*_viStageMap)->rc.top / 10, 7, 7);
		Rectangle(getMemDC(), temp);
		SelectObject(getMemDC(), oldBrush);
		SelectObject(getMemDC(), oldPen);
		DeleteObject(brush);
		DeleteObject(pen);
		
		}

		// �⺻ �� ����
		//if ((*_viStageMap)->terrain != TR_NONE && (*_viStageMap)->wall != W_END_WALL&& (*_viStageMap)->wall != W_BOSS_WALL
		//	&& (*_viStageMap)->wall != W_WALL2 && (*_viStageMap)->wall != W_SHOP_WALL&& (*_viStageMap)->trap == TRAP_NONE
		//	&& (*_viStageMap)->wall != W_DOOR && (*_viStageMap)->terrain != TR_STAIR)		//���� end��,����,������ ������ �⺻��
		//{
		//	if ((*_viStageMap)->alphaValue <= 0)
		//	{
		//		HBRUSH brush = CreateSolidBrush(RGB(153,102,0));
		//		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		//		RECT temp;
		//		temp = RectMake(750 + (*_viStageMap)->rc.left / 10, 450 + (*_viStageMap)->rc.top / 10,
		//			6,6);
		//		Rectangle(getMemDC(), temp);
		//		SelectObject(getMemDC(), oldBrush);
		//		DeleteObject(brush);
		//	
		//	}
		//	else
		//	{
		//		//�ȹ����� �κ�
		//	}
		//	continue;
		//}

		//// �� ����
		//if ((*_viStageMap)->terrain != TR_NONE && (*_viStageMap)->wall != W_END_WALL && (*_viStageMap)->wall != W_BOSS_WALL
		//	&& (*_viStageMap)->wall != W_WALL2 && (*_viStageMap)->wall != W_SHOP_WALL && (*_viStageMap)->trap == TRAP_NONE
		//	&& (*_viStageMap)->wall != W_WALL && (*_viStageMap)->terrain != TR_STAIR)
		//{
		//	if ((*_viStageMap)->alphaValue <= 0)
		//	{
		//		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
		//		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		//		RECT temp;
		//		temp = RectMake(750 + (*_viStageMap)->rc.left / 10, 450 + (*_viStageMap)->rc.top / 10,
		//			6, 6);
		//		Rectangle(getMemDC(), temp);
		//		SelectObject(getMemDC(), oldBrush);
		//		DeleteObject(brush);

		//	}
		//	else
		//	{
		//		//�ȹ����� �κ�
		//	}
		//	continue;
		//}

		//// ��� ����
		//if ((*_viStageMap)->terrain != TR_NONE && (*_viStageMap)->wall != W_END_WALL && (*_viStageMap)->wall != W_BOSS_WALL
		//	&& (*_viStageMap)->wall != W_WALL2 && (*_viStageMap)->wall != W_SHOP_WALL && (*_viStageMap)->trap == TRAP_NONE
		//	&& (*_viStageMap)->wall != W_WALL && (*_viStageMap)->wall != W_DOOR)
		//{
		//	if ((*_viStageMap)->alphaValue <= 0)
		//	{
		//		HBRUSH brush = CreateSolidBrush(RGB(255,10, 255));
		//		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		//		RECT temp;
		//		temp = RectMake(750 + (*_viStageMap)->rc.left / 10, 450 + (*_viStageMap)->rc.top / 10,
		//			6, 6);
		//		Rectangle(getMemDC(), temp);
		//		SelectObject(getMemDC(), oldBrush);
		//		DeleteObject(brush);

		//	}
		//	else
		//	{
		//		//�ȹ����� �κ�
		//	}
		//	continue;
		//}
		//// ���� ����
		//if ((*_viStageMap)->terrain != TR_NONE && (*_viStageMap)->wall != W_END_WALL && (*_viStageMap)->wall != W_BOSS_WALL
		//	&& (*_viStageMap)->wall != W_SHOP_WALL && (*_viStageMap)->trap == TRAP_NONE && (*_viStageMap)->wall != W_DOOR
		//	&& (*_viStageMap)->wall != W_WALL && (*_viStageMap)->terrain != TR_STAIR)
		//{
		//	if ((*_viStageMap)->alphaValue <= 0)
		//	{
		//		HBRUSH brush = CreateSolidBrush(RGB(102,51,0));
		//		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		//		RECT temp;
		//		temp = RectMake(750 + (*_viStageMap)->rc.left / 10, 450 + (*_viStageMap)->rc.top / 10,
		//			6, 6);
		//		Rectangle(getMemDC(), temp);
		//		SelectObject(getMemDC(), oldBrush);
		//		DeleteObject(brush);

		//	}
		//	else
		//	{
		//		//�ȹ����� �κ�
		//	}
		//	continue;
		//}
		////NPC ��
		//if ((*_viStageMap)->terrain != TR_NONE && (*_viStageMap)->wall != W_END_WALL && (*_viStageMap)->wall != W_BOSS_WALL
		//	&& (*_viStageMap)->trap == TRAP_NONE && (*_viStageMap)->wall != W_DOOR
		//	&& (*_viStageMap)->wall != W_WALL && (*_viStageMap)->terrain != TR_STAIR && (*_viStageMap)->wall != W_WALL2)
		//{
		//	if ((*_viStageMap)->alphaValue <= 0)
		//	{
		//		HBRUSH brush = CreateSolidBrush(RGB(255,255, 0));
		//		HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
		//		RECT temp;
		//		temp = RectMake(750 + (*_viStageMap)->rc.left / 10, 450 + (*_viStageMap)->rc.top / 10,
		//			6, 6);
		//		Rectangle(getMemDC(), temp);
		//		SelectObject(getMemDC(), oldBrush);
		//		DeleteObject(brush);

		//	}
		//	else
		//	{
		//		//�ȹ����� �κ�
		//	}
		//	continue;
		//}



		//if ((*_viStageMap)->terrain != TR_NONE && (*_viStageMap)->wall != W_END_WALL )
		//{

		//}
	
	}
	for(_em->getViEnemy())
	//// �̿��� ���� 
	/*
	for (_viStageMap = _vStageMap.begin(); _viStageMap != _vStageMap.end(); ++_viStageMap)
	{
		if ((*_viStageMap)->type == TYPE_NONE) continue;
		if ((*_viStageMap)->alphaValue <= 0)
		{
			if ((*_viStageMap)->wall != W_NONE)
			{
				continue;
			}
			if ((*_viStageMap)->trap != TRAP_NONE)
			{
				
				continue;
			}

			if ((*_viStageMap)->terrain != TR_NONE &&(*_viStageMap)->terrain != TR_STAIR) //�⺻ ��
			{
				HBRUSH brush2 = CreateSolidBrush(RGB(230,230,154));
				HBRUSH oldBrush2 = (HBRUSH)SelectObject(getMemDC(), brush2);
				RECT temp;
				temp = RectMake(750 + (*_viStageMap)->rc.left / 10, 450 + (*_viStageMap)->rc.top / 10,
					6,6);
				Rectangle(getMemDC(), temp);
				SelectObject(getMemDC(), oldBrush2);
				DeleteObject(brush2);
				continue;
			}
			if ((*_viStageMap)->wall != W_NONE) 
			{
			
				continue;
			}

		}
		else
		{
			if ((*_viStageMap)->wall != W_NONE)
			{
				
				continue;
			}
			if ((*_viStageMap)->trap != TRAP_NONE)
			{
				
				continue;
			}
		}


		
//������
enum ARMOR
{
	//��
	A_HELMET, A_SHOVEL,
	A_ARMOR_1, A_ARMOR_2, A_ARMOR_3, A_ARMOR_4,
	A_BOOTS,
	A_RING,
	A_TORCH_1, A_TORCH_2, A_TORCH_3, 
	A_NONE
};
enum WEAPON
{
	//����
	WP_DAGGER_1, WP_DAGGER_2, WP_RAPIER, WP_BROAD_SWORD,
	WP_BOMB, WP_RIFLE, WP_SHOTGUN,
	WP_SPEAR, WP_MACE,WP_LONG_SWORD,
	WP_WHIP, WP_NINETAILS_WHIP,
	WP_BOW, WP_CROSS_BOW,
	WP_NONE
};

enum STUFF
{
	ST_DIAMOND,
	ST_ONE_COIN, ST_ONE_HALF_COIN,
	ST_COINS, ST_MORE_COINS,
	ST_APPLE, ST_CHEESE, ST_MEAT,
	ST_NONE,
};

enum OBJECT
{
	OBJ_WATER,										//�ٴۿ� �ѷ����� ������Ʈ
	OBJ_FALLING_DOOR,								//�������� �ٴ�
};

enum CHARACTER
{
	CHAR_ENEMY,										//��
	CHAR_PLAYER,									//�÷��̾�
};
*/
}
