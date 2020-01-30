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
	
	_r = _g = _b = 0;
	

	return S_OK;
}

void miniMap::release()
{

}

void miniMap::update()
{
	cout<<_em->getVEnemy()[0]->getEnemyInfo()->idx<<"adsfdafsadfsadfs"<<endl;
}

void miniMap::render()
{
	
	
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
			else if ((*_viStageMap)->terrain == TR_SHOP ) //else if로 하면 그전거를 예외처리 할 필요가 없구낭..
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
		//타일
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


		////플레이어
		HBRUSH brush3 = CreateSolidBrush(RGB(0, 0, 255));
		HBRUSH oldBrush3 = (HBRUSH)SelectObject(getMemDC(), brush3);
		HPEN pen3 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		HPEN oldPen3 = (HPEN)SelectObject(getMemDC(), pen3);
		RECT temp3 = RectMake(750 + _pm->getPlayerInfo()->getPlayer().rc.left / 10,
			450 + _pm->getPlayerInfo()->getPlayer().rc.top / 10, 4, 4);
		Rectangle(getMemDC(), temp3);
		SelectObject(getMemDC(), oldBrush3);
		SelectObject(getMemDC(), oldPen3);
		DeleteObject(brush3);
		DeleteObject(pen3);

		}

		
	
	}
	

	//에너미

	/*vector<Enemy*> vec = _em->getVEnemy();
	vector<Enemy*>::iterator ins = vec.begin();
	for (; ins != vec.end(); )
	{
		RECT temp2;
		if (IntersectRect(&temp2, &CAMERAMANAGER->getCamera_Rect(), &(*ins)->getEnemyInfo()->rc))
		{
			HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
			HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), brush);
			HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
			RECT temp;
			temp = RectMake(750 + (*ins)->getEnemyInfo()->rc.left / 10,
				450 + (*ins)->getEnemyInfo()->rc.top / 10, 4, 4);
			Rectangle(getMemDC(), temp);
			SelectObject(getMemDC(), oldBrush);
			SelectObject(getMemDC(), oldPen);
			DeleteObject(brush);
			DeleteObject(pen);
			ins++;
		}
		else continue;
	}*/
	

	


}