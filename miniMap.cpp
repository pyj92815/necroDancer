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
	//미니맵 이미지 추가
	IMAGEMANAGER->addImage("min_door", "./image/UI/min_rect_door.bmp",6,6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_end", "./image/UI/min_rect_end.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_end_else", "./image/UI/min_rect_end_else.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_enemy", "./image/UI/min_rect_enemy.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_fallingdoor", "./image/UI/min_rect_fallingdoor.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_normal", "./image/UI/min_rect_normal.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_player", "./image/UI/min_rect_player.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_shop", "./image/UI/min_rect_shop.bmp", 6,6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_stair", "./image/UI/min_rect_stair.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_trap", "./image/UI/min_rect_trap.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_wall2", "./image/UI/min_rect_wall2.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_wall3", "./image/UI/min_rect_wall3.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("min_shoping_rc", "./image/UI/min_rect_shopingRect.bmp", 6, 6, true, RGB(255, 0, 255));
	
	//플레이어 위치 정보 초기화
	_playerX = 0;
	_playerY = 0;
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
	//미니맵 타일 정보에 따른 이미지 키값 삽입
	for (_viStageMap = _vStageMap.begin(); _viStageMap != _vStageMap.end(); ++_viStageMap)
	{
		if ((*_viStageMap)->type == TYPE_NONE) continue; //타입이 없을 경우 넘기도록

		switch ((*_viStageMap)->type)
		{
		case TYPE_TERRAIN:								//지형 타입
			if ((*_viStageMap)->terrain == TR_STAIR || (*_viStageMap)->terrain == TR_BOSS_STAIR)
			{
				_imageName = "min_stair";				//init에서 초기화한 이미지 키값을 찾아서 넣어준다
			}
			else if ((*_viStageMap)->terrain == TR_SHOP )
			{
				_imageName = "min_shoping_rc";
			}
			else if ((*_viStageMap)->terrain == TR_END)
			{
				_imageName = "min_end";
			}
			else
			{
				_imageName = "min_normal";
			}
			break;
		case TYPE_WALL:									//벽 타입
			if ((*_viStageMap)->wall == W_ITEM_WALL || (*_viStageMap)->wall == W_SHOP_WALL)
			{
				_imageName = "min_wall3";
			}
			else if ((*_viStageMap)->wall == W_WALL2 || (*_viStageMap)->wall == W_BOSS_WALL)
			{
				_imageName = "min_wall2";
			}
			else if ((*_viStageMap)->wall == W_DOOR)
			{
				_imageName = "min_door";
			}
			else if ((*_viStageMap)->wall == W_END_WALL)
			{
				_imageName = "min_end";
			}
			else
			{
				_imageName = "min_end_else";
			}
			break;
		case TYPE_TRAP:									//함정 타입
			if ((*_viStageMap)->trap == TRAP_SHADOW || (*_viStageMap)->trap == TRAP_NIDDLE_SHADOW)
			{
			}
			else
			{
				_imageName = "min_trap";
			}
			break;
		case TYPE_ITEM_ARMOR:							//갑옷 아이템 타입
			if ((*_viStageMap)->armor == A_NONE)
			{
			}
			else
			{
				_imageName = "min_shop";
			}
			break;
		case TYPE_ITEM_WEAPON:
			if ((*_viStageMap)->weapon == WP_NONE)		//무기 아이템 타입
			{
			}
			else
			{
				_imageName = "min_shop";
			}
			break;
		case TYPE_ITEM_STUFF:
			if ((*_viStageMap)->stuff == ST_NONE)		//소비 아이템 타입
			{
			}
			else
			{
				_imageName = "min_shop";
			}
			break;
		case TYPE_OBJECT:
			if ((*_viStageMap)->obj == OBJ_FALLING_DOOR)//떨어지는 문 타입
			{
				_imageName = "min_fallingdoor";
			}
			break;
		case TYPE_NONE:
			break;
		default:
			break;
		}
		//시야에 들어온 존재만 보이도록
		if ((*_viStageMap)->alphaValue <= 0)								//알파랜더링값이 0인 타일의 경우(시야에 들어온 타일)
		{
			//타일 미니맵 출력
			IMAGEMANAGER->findImage(_imageName)->render(getMemDC(),
				750 + (*_viStageMap)->rc.left / 10,
				450 + (*_viStageMap)->rc.top / 10);
			//플레이어 미니맵 출력
			IMAGEMANAGER->findImage("min_player")->render(getMemDC(),
				747 + _playerX / 10,
				448 + _playerY / 10);
		}
	}
	//몬스터 미니맵 출력
	vector<Enemy*> vec = _em->getVEnemy();									//에너미 벡터 
	vector<Enemy*>::iterator ins = vec.begin();								//에너미 이터레이터
	if ((*ins)->getEnemyInfo()->Light)										//에너미 위치 확인 불값
	{
		for (; ins != vec.end();)											//이터레이터가 백터의 끝이 아닐 경우
		{
			IMAGEMANAGER->findImage("min_enemy")->render(getMemDC(),		//에너미 미니맵 이미지 출력 
				750 + (*ins)->getEnemyInfo()->rc.left / 10,
				450 + (*ins)->getEnemyInfo()->rc.top / 10);
			ins++;															//백터를 계속 돌리도록
		}
	}
}