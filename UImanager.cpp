#include "stdafx.h"
#include "UImanager.h"

HRESULT UImanager::init()
{
	//왼쪽 인벤토리
	_attackInven.image = IMAGEMANAGER->addImage("attack_Inven", "./image/UI/hud_slot_2.bmp", 60, 66, true, RGB(255, 0, 255));
	_shovelInven.image = IMAGEMANAGER->addImage("shovel_Inven", "./image/UI/hud_slot_1.bmp", 60, 66, true, RGB(255, 0, 255));
	_itemInven.image = IMAGEMANAGER->addImage("item_Inven", "./image/UI/hud_slot_action1.bmp", 60, 84, true, RGB(255, 0, 255));
	_bombInven.image = IMAGEMANAGER->addImage("bomb_Inven", "./image/UI/hud_slot_bomb.bmp", 60, 84, true, RGB(255, 0, 255));
	_throwInven.image = IMAGEMANAGER->addImage("throw_Inven", "./image/UI/hud_slot_throw.bmp", 60, 84, true, RGB(255, 0, 255));
	_bodyInven.image = IMAGEMANAGER->addImage("body_Inven", "./image/UI/hud_slot_3.bmp", 60, 66, true, RGB(255, 0, 255));
	_headInven.image = IMAGEMANAGER->addImage("head_Inven", "./image/UI/hud_slot_4.bmp", 60, 66, true, RGB(255, 0, 255));
	_feetInven.image = IMAGEMANAGER->addImage("feet_Inven", "./image/UI/hud_slot_5.bmp", 60, 66, true, RGB(255, 0, 255));
	_torchInven.image = IMAGEMANAGER->addImage("torch_Inven", "./image/UI/hud_slot_6.bmp", 60, 66, true, RGB(255, 0, 255));
	_ringInven.image = IMAGEMANAGER->addImage("ring_Inven", "./image/UI/hud_slot_7.bmp", 60, 66, true, RGB(255, 0, 255));

	//오른쪽 인벤토리
	_coinInven.image = IMAGEMANAGER->addImage("coin_Inven", "./image/UI/hud_coins.bmp", 48, 48, true, RGB(255, 0, 255));
	_daiaInven.image = IMAGEMANAGER->addImage("daia_Inven", "./image/UI/diamond.bmp", 50, 48, true, RGB(255, 0, 255));

	_scoreNum = IMAGEMANAGER->addFrameImage("number", "./image/UI/number.bmp", 80, 20, 10, 1, true, RGB(255, 0, 255));
	_scoreX = IMAGEMANAGER->addImage("numberX", "./image/UI/x.bmp", 8, 8, true, RGB(255, 0, 255));
	_daiaNum = IMAGEMANAGER->addFrameImage("number", "./image/UI/number.bmp", 80, 20, 10, 1, true, RGB(255, 0, 255));

	//글자들
	_downLeft.image = IMAGEMANAGER->addImage("down_Left", "./image/UI/down_left_x2.bmp", 46, 48, true, RGB(255, 0, 255));
	_upDown.image = IMAGEMANAGER->addImage("up_Down", "./image/UI/up_down_x2.bmp", 46, 48, true, RGB(255, 0, 255));
	_upLeft.image = IMAGEMANAGER->addImage("up_Left", "./image/UI/up_left_x2.bmp", 46, 48, true, RGB(255, 0, 255));

	//하트
	IMAGEMANAGER->addFrameImage("heart_full", "./image/UI/heart_full.bmp", 109, 50, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heart_half", "./image/UI/heart_half.bmp", 109, 50, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heart_null", "./image/UI/heart_null.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255));

	for (int i = 0; i < 3; i++)
	{
		_heart[i].state = HEARTSTATE_FULL;								//하트상태 초기화
		_heart[i].image = IMAGEMANAGER->findImage("heart_full");		//하트상태 이미지
	}

	//애니메이션 ================================

	int heartFull[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("heart_full_ani", "heart_full", heartFull, 2, 10, true);
	int heartFull_move[] = { 0,1 };		//애니메이션매니저에 프레임이미지 기준 연산 초기화								
	KEYANIMANAGER->addArrayFrameAnimation("heart_full_ani_move", "heart_full", heartFull_move, 2, 10, true);

	for (int i = 0; i < 3; i++)
	{
		_heart[i].anime = KEYANIMANAGER->findAnimation("heart_full_ani_move");				//애니메이션 첫번째 키값 초기화
	/*	_heart[1].anime = KEYANIMANAGER->findAnimation("heart_full_ani");
		_heart[2].anime = KEYANIMANAGER->findAnimation("heart_full_ani");*/
		//위의 [1],[2]처럼 애니메이션 각자 정해놓으면 배열 땜에 터질 수도 있다
		//어차피 밑에 업데이트에서 상태 정의해놓으면 되므로 그냥 _heart[i].anime로 해야 되더라..
		_heart[i].anime->start();															//에니메이션 스타트
	}
	//============================================

	hp = 6;

	_coinTest = 233;								//코인 테스트
	_diaTest = 2369;								//다이아 테스트

	_heartBeatCnt = 0;								//하트비트 카운트

	interval = 0;
	//인벤토리 해제 불값=============================

	_attackInven.open = false;
	_shovelInven.open = false;
	_itemInven.open = false;
	_bombInven.open = false;
	_throwInven.open = false;
	_bodyInven.open = false;
	_headInven.open = false;
	_feetInven.open = false;
	_torchInven.open = false;
	_ringInven.open = false;
	_heatBeatStop = false;
	_heatBeatStop2 = true;

	//인벤토리 고정할 위치
	_x1Slot = 20, _y1Slot = 5;
	_x2Slot = 90, _y2Slot = 81;
	_x3Slot = 160, _y3Slot = 195;
	_x4Slot = 230, _y4Slot = 299;
	_x5Slot = 300;
	_x6Slot = 370;
	_x7Slot = 440;

	//인벤토리 이미지 좌표 셋팅
	_itemInven.image->setX(_itemInven.x);
	_itemInven.image->setY(_itemInven.y);
	_itemInven.x = 20;

	_attackInven.image->setX(_attackInven.x);
	_attackInven.image->setY(_attackInven.y);
	_attackInven.y = 5;

	_throwInven.image->setY(_throwInven.x);
	_throwInven.image->setY(_throwInven.y);
	_throwInven.x = 20;

	_bodyInven.image->setX(_bodyInven.x);
	_bodyInven.image->setY(_bodyInven.y);
	_bodyInven.y = 5;

	_bombInven.image->setX(_bombInven.x);
	_bombInven.image->setY(_bombInven.y);
	_bombInven.x = 20;

	_headInven.image->setX(_headInven.x);
	_headInven.image->setY(_headInven.y);
	_headInven.y = 5;

	_feetInven.image->setX(_feetInven.x);
	_feetInven.image->setY(_feetInven.y);
	_feetInven.y = 5;

	_torchInven.image->setX(_torchInven.x);
	_torchInven.image->setY(_torchInven.y);
	_torchInven.y = 5;

	_ringInven.image->setX(_ringInven.x);
	_ringInven.image->setY(_ringInven.y);
	_ringInven.y = 5;
	return S_OK;
}

void UImanager::release()
{

}

void UImanager::update()
{
	//=========테스트용 조작 키====================
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		hp--;
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		hp++;
	}

	/*if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_heartBeatCnt++;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_heartBeatCnt--;
	}*/


	if (BEATMANAGER->getInterval())
	{
		interval++;
		if (interval > 10) //노트가 10개 이므로
		{
			_heartBeatCnt++;

			if (_heartBeatCnt > 2)
			{
				_heartBeatCnt = 0;
			}
			interval = 0;
		}

	}


	if (KEYMANAGER->isToggleKey('L'))
	{
		_bombInven.open = true;
		_bodyInven.open = true;
		_feetInven.open = true;

		_torchInven.open = true;
		_ringInven.open = true;

	}
	if (KEYMANAGER->isToggleKey('K'))
	{
		_shovelInven.open = true;

		_attackInven.open = true;
		_itemInven.open = true;
		_headInven.open = true;
		/*_throwInven.open = true;*/


	}
	//=======================================

	//HP에 따른 하트의 상태 설정
	switch (hp)
	{
	case 6:
		_heart[0].state = HEARTSTATE_FULL;
		_heart[1].state = HEARTSTATE_FULL;
		_heart[2].state = HEARTSTATE_FULL;
		break;
	case 5:
		_heart[0].state = HEARTSTATE_FULL;
		_heart[1].state = HEARTSTATE_FULL;
		_heart[2].state = HEARTSTATE_HALF;
		break;
	case 4:
		_heart[0].state = HEARTSTATE_FULL;
		_heart[1].state = HEARTSTATE_FULL;
		_heart[2].state = HEARTSTATE_NULL;
		break;
	case 3:
		_heart[0].state = HEARTSTATE_FULL;
		_heart[1].state = HEARTSTATE_HALF;
		_heart[2].state = HEARTSTATE_NULL;
		break;
	case 2:
		_heart[0].state = HEARTSTATE_FULL;
		_heart[1].state = HEARTSTATE_NULL;
		_heart[2].state = HEARTSTATE_NULL;
		break;
	case 1:
		_heart[0].state = HEARTSTATE_HALF;
		_heart[1].state = HEARTSTATE_NULL;
		_heart[2].state = HEARTSTATE_NULL;
		break;
	case 0:
		_heart[0].state = HEARTSTATE_NULL;
		_heart[1].state = HEARTSTATE_NULL;
		_heart[2].state = HEARTSTATE_NULL;
		break;
	}

	//하트 상태에 따라 해당 이미지 찾기
	for (int i = 0; i < 3; i++)
	{
		if (_heart[i].state == HEARTSTATE_FULL)
		{
			_heart[i].image = IMAGEMANAGER->findImage("heart_full");
		}
		if (_heart[i].state == HEARTSTATE_HALF)
		{
			_heart[i].image = IMAGEMANAGER->findImage("heart_half");
		}
		if (_heart[i].state == HEARTSTATE_NULL)
		{
			_heart[i].image = IMAGEMANAGER->findImage("heart_null");
		}
	}

	//하트비트를 받아오면 적용할 곳=========================================
	//하트비트가 들어오면 ++해줄것
	//하트비트에 따라 하트가 뛰는 위치가 다르게 상태 설정
	switch (_heartBeatCnt)
	{
	case 0:
		_heart[0].turn = TURN_ON;
		_heart[1].turn = TURN_OFF;
		_heart[2].turn = TURN_OFF;
		break;
	case 1:
		_heart[0].turn = TURN_OFF;
		_heart[1].turn = TURN_ON;
		_heart[2].turn = TURN_OFF;
		if (hp < 3)
		{
			_heartBeatCnt = 0;		//살아있는 하트만 첫번째 하트부터 애니메이션 되도록 예외처리
		}
		break;
	case 2:
		_heart[0].turn = TURN_OFF;
		_heart[1].turn = TURN_OFF;
		_heart[2].turn = TURN_ON;
		if (hp < 5)
		{
			_heartBeatCnt = 0;
		}
		break;
	}

	for (int i = 0; i < 3; i++)				//뛰는 상태와,아닌 상태의 애니메이션 넣기
	{
		if (_heart[i].turn == TURN_ON)
		{
			_heart[i].anime = KEYANIMANAGER->findAnimation("heart_full_ani_move");
		}
		else if (_heart[i].turn == TURN_OFF)
		{
			_heart[i].anime = KEYANIMANAGER->findAnimation("heart_full_ani");
		}

	}



	////인벤토리 고정할 위치
	//_x1Slot = 20, _y1Slot = 5;
	//_x2Slot = 90, _y2Slot = 81;
	//_x3Slot = 160, _y3Slot = 195;
	//_x4Slot = 230, _y4Slot = 299;
	//_x5Slot = 300;
	//_x6Slot = 370;

	////인벤토리 이미지 좌표 셋팅
	//_itemInven.image->setX(_itemInven.x);
	//_attackInven.image->setX(_attackInven.x);
	//_itemInven.image->setY(_itemInven.y);
	//_throwInven.image->setY(_throwInven.y);
	//_bombInven.image->setY(_bodyInven.y);
	//_bodyInven.image->setX(_bodyInven.x);
	//_headInven.image->setX(_headInven.x);
	//_feetInven.image->setX(_feetInven.x);
	//_torchInven.image->setX(_torchInven.x);
	//_ringInven.image->setX(_ringInven.x);

	//인벤토리 이동 예외처리========================
//x축 기준
	if (!_shovelInven.open)
	{
		_attackInven.x = _x1Slot;
		if (!_attackInven.open)
		{
			_bodyInven.x = _x1Slot;
			if (!_bodyInven.open)
			{
				_headInven.x = _x1Slot;
				if (!_headInven.open)
				{
					_feetInven.x = _x1Slot;
					if (!_feetInven.open)
					{
						_torchInven.x = _x1Slot;
						if (!_torchInven.open)_ringInven.x = _x1Slot;
					}
				}
			}
		}
	}
	if (_shovelInven.open)
	{
		if (_x2Slot >= _attackInven.x)_attackInven.x++;
		if (_x2Slot >= _bodyInven.x)_bodyInven.x++;
		if (_x2Slot >= _headInven.x)_headInven.x++;
		if (_x2Slot >= _feetInven.x)_feetInven.x++;
		if (_x2Slot >= _torchInven.x)_torchInven.x++;
		if (_x2Slot >= _ringInven.x)_ringInven.x++;
		if (_attackInven.open)
		{
			if (_x3Slot >= _bodyInven.x)_bodyInven.x++;
			if (_x3Slot >= _headInven.x)_headInven.x++;
			if (_x3Slot >= _feetInven.x)_feetInven.x++;
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_bodyInven.open)
			{
				if (_x4Slot >= _headInven.x)_headInven.x++;
				if (_x4Slot >= _feetInven.x)_feetInven.x++;
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_headInven.open)
				{
					if (_x5Slot >= _feetInven.x)_feetInven.x++;
					if (_x5Slot >= _torchInven.x)_torchInven.x++;
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
					if (_feetInven.open)
					{
						if (_x6Slot >= _torchInven.x)_torchInven.x++;
						if (_x6Slot >= _ringInven.x)_ringInven.x++;
						if (_torchInven.open)
						{
							if (_x7Slot >= _ringInven.x)_ringInven.x++;
						}
					}
					if (_torchInven.open)
					{
						if (_x6Slot >= _ringInven.x)_ringInven.x++;
					}
				}
				if (_feetInven.open)
				{
					if (_x5Slot >= _torchInven.x)_torchInven.x++;
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
					if (_torchInven.open)
					{
						if (_x6Slot >= _ringInven.x)_ringInven.x++;
					}
				}
				if (_torchInven.open)
				{
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
				}

			}
			if (_headInven.open)
			{
				if (_x4Slot >= _feetInven.x)_feetInven.x++;
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_feetInven.open)
				{
					if (_x5Slot >= _torchInven.x)_torchInven.x++;
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
					if (_torchInven.open)
					{
						if (_x6Slot >= _ringInven.x)_ringInven.x++;
					}
				}
			}
			if (_feetInven.open)
			{
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_torchInven.open)
				{
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
				}
			}
			if (_torchInven.open)
			{
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
			}
		}
		if (_bodyInven.open)
		{
			if (_x3Slot >= _headInven.x)_headInven.x++;
			if (_x3Slot >= _feetInven.x)_feetInven.x++;
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_headInven.open)
			{
				if (_x4Slot >= _feetInven.x)_feetInven.x++;
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_feetInven.open)
				{
					if (_x5Slot >= _torchInven.x)_torchInven.x++;
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
					if (_torchInven.open)
					{
						if (_x6Slot >= _ringInven.x)_ringInven.x++;
					}
				}
			}
		}
		if (_headInven.open)
		{
			if (_x3Slot >= _feetInven.x)_feetInven.x++;
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_feetInven.open)
			{
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_torchInven.open)
				{
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
				}
			}
		}
		if (_feetInven.open)
		{
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_torchInven.open)
			{
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
			}
		}
		if (_torchInven.open)
		{
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
		}
	}

	//==============================================

	if (_attackInven.open)
	{
		if (_x2Slot >= _bodyInven.x)_bodyInven.x++;
		if (_x2Slot >= _headInven.x)_headInven.x++;
		if (_x2Slot >= _feetInven.x)_feetInven.x++;
		if (_x2Slot >= _torchInven.x)_torchInven.x++;
		if (_x2Slot >= _ringInven.x)_ringInven.x++;
		if (_bodyInven.open)
		{
			if (_x3Slot >= _headInven.x)_headInven.x++; //여기서 해드가 없으면 
			if (_x3Slot >= _feetInven.x)_feetInven.x++;	//밑에 얘네들이 x3에 머무는구나
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_headInven.open)
			{
				if (_x4Slot >= _feetInven.x)_feetInven.x++;
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_feetInven.open)
				{
					if (_x5Slot >= _torchInven.x)_torchInven.x++;
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
					if (_torchInven.open)
					{
						if (_x6Slot >= _ringInven.x)_ringInven.x++;
					}

				}

			}

			if (_feetInven.open)
			{
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_torchInven.open)
				{
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
				}
			}
			if (_torchInven.open)
			{
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
			}
		}
		if (_headInven.open)
		{
			if (_x3Slot >= _feetInven.x)_feetInven.x++;
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_feetInven.open)
			{
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_torchInven.open)
				{
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
				}

			}

		}
		if (_feetInven.open)
		{
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_torchInven.open)
			{
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
			}

		}
		if (_torchInven.open)
		{
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
		}
	}


	//=================================================



	if (_bodyInven.open)
	{
		if (_x2Slot >= _headInven.x)_headInven.x++;
		if (_x2Slot >= _feetInven.x)_feetInven.x++;
		if (_x2Slot >= _torchInven.x)_torchInven.x++;
		if (_x2Slot >= _ringInven.x)_ringInven.x++;
		if (_headInven.open)
		{
			if (_x3Slot >= _feetInven.x)_feetInven.x++;
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_feetInven.open)
			{
				if (_x4Slot >= _torchInven.x)_torchInven.x++;
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
				if (_torchInven.open)
				{
					if (_x5Slot >= _ringInven.x)_ringInven.x++;
				}
			}
			if (_torchInven.open)
			{
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
			}

		}
		if (_feetInven.open)
		{
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_torchInven.open)
			{
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
			}
		}
		if (_torchInven.open)
		{
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
		}
	}

	//===================================

	if (_headInven.open)
	{
		if (_x2Slot >= _feetInven.x)_feetInven.x++;
		if (_x2Slot >= _torchInven.x)_torchInven.x++;
		if (_x2Slot >= _ringInven.x)_ringInven.x++;
		if (_feetInven.open)
		{
			if (_x3Slot >= _torchInven.x)_torchInven.x++;
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
			if (_torchInven.open)
			{
				if (_x4Slot >= _ringInven.x)_ringInven.x++;
			}
		}
		if (_torchInven.open)
		{
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
		}
	}
	//=============================
	if (_feetInven.open)
	{
		if (_x2Slot >= _torchInven.x)_torchInven.x++;
		if (_x2Slot >= _ringInven.x)_ringInven.x++;
		if (_torchInven.open)
		{
			if (_x3Slot >= _ringInven.x)_ringInven.x++;
		}
	}

	//==========================
	if (_torchInven.open)
	{
		if (_x2Slot >= _ringInven.x)_ringInven.x++;
	}

	//y축 기준====================

	_itemInven.y = _y2Slot;
	if (!_itemInven.open)
	{
		_throwInven.y = _y2Slot;
		if (!_throwInven.open)
		{
			_bombInven.y = _y2Slot;
		}
	}

	if (_itemInven.open)
	{
		if (_y3Slot >= _throwInven.y)_throwInven.y++;
		if (_y3Slot >= _bombInven.y)_bombInven.y++;
		if (_throwInven.open)
		{
			if (_y4Slot >= _bombInven.y)_bombInven.y++;
		}
		else if (!_throwInven.open)
		{
			_bombInven.y = _y3Slot;
		}
	}

	if (_throwInven.open)
	{
		if (_y3Slot >= _bombInven.y)_bombInven.y++;
	}



	//====================================================================
	for (int i = 0; i < _vInven.size(); i++)
	{

		if (_vInven[i]->armor == A_ARMOR_1 || _vInven[i]->armor == A_ARMOR_2 || _vInven[i]->armor == A_ARMOR_3 || _vInven[i]->armor == A_ARMOR_4)
		{
			_bodyInven.open = true;
			//IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _bodyInven.x * i / i + 5, _bodyInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
		}
		else if (_vInven[i]->armor == A_HELMET)
		{
			_headInven.open = true;
			//IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _headInven.x * i / i + 5, _headInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
		}
		else if (_vInven[i]->armor == A_SHOVEL)
		{
			_shovelInven.open = true;
			//IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _shovelInven.x * i / i + 5, _shovelInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
		}
		else if (_vInven[i]->armor == A_TORCH_1 || _vInven[i]->armor == A_TORCH_2 || _vInven[i]->armor == A_TORCH_3)
		{
			_torchInven.open = true;
			//IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _torchInven.x * i / i + 5, _torchInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
		}
		else if (_vInven[i]->armor == A_RING)
		{
			_ringInven.open = true;
			//IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _ringInven.x * i / i + 5, _ringInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
		}

		if (_vInven[i]->weapon != WP_NONE && _vInven[i]->weapon != WP_DAGGER_1 && _vInven[i]->weapon != WP_DAGGER_2)
		{
			_attackInven.open = true;
			_throwInven.open = false;
			//IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), _attackInven.x * i / i + 5, _attackInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
		}
		else if (_vInven[i]->weapon == WP_DAGGER_1 || _vInven[i]->weapon == WP_DAGGER_2)
		{
			_attackInven.open = true;
			_throwInven.open = true;
			//IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), _attackInven.x * i / i + 5, _attackInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
			if (_throwInven.open)_throwInven.image->render(getMemDC(), 20, _throwInven.y), _upDown.image->render(getMemDC(), 30, _throwInven.y + 60);
			//IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), _throwInven.x * i / i + 5, _throwInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
		}
		//if (_vInven[i]->stuff != ST_NONE && _vInven[i]->stuff == ST_DIAMOND)
		//{
		//	
		//	_itemInven.open = true;
		//	//IMAGEMANAGER->findImage("stuffTiles")->frameRender(getMemDC(), _itemInven.x * i / i + 5, _itemInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
		//}
		if (_vInven[i]->stuff == ST_ONE_COIN)
		{
			_coinTest++;
		}
	}
}

void UImanager::render()
{
	////왼쪽 인벤토리
	if(_shovelInven.open)_shovelInven.image->render(getMemDC(), _x1Slot, 5);
	if(_attackInven.open)_attackInven.image->render(getMemDC(), _attackInven.x, 5);
	if(_itemInven.open)_itemInven.image->render(getMemDC(), 20, _itemInven.y),_upLeft.image->render(getMemDC(), 30, _itemInven.y+60);
	if(_bombInven.open)_bombInven.image->render(getMemDC(), 20, _bombInven.y),_downLeft.image->render(getMemDC(), 30, _bombInven.y+60);
	if(_bodyInven.open)_bodyInven.image->render(getMemDC(), _bodyInven.x, _bodyInven.y);
	if(_headInven.open)_headInven.image->render(getMemDC(), _headInven.x, _headInven.y);
	if(_feetInven.open)_feetInven.image->render(getMemDC(), _feetInven.x, 5);
	if(_torchInven.open)_torchInven.image->render(getMemDC(), _torchInven.x, 5);
	if(_ringInven.open)_ringInven.image->render(getMemDC(), _ringInven.x, 5);

	//오른쪽 인벤토리
	_coinInven.image->render(getMemDC(), WINSIZEX - 125, 5);
	_daiaInven.image->render(getMemDC(), WINSIZEX - 125, 65);
	_scoreX->render(getMemDC(), WINSIZEX - 72, 30);
	_scoreX->render(getMemDC(), WINSIZEX - 72, 90);

	//하트 이미지 & 애니메이션
	for (int i = 0; i < 3; i++)
	{
		_heart[i].image->frameRender(getMemDC(), 573 + i * 60, 12, 0, 0);
		_heart[i].image->aniRender(getMemDC(), 600 + i * 60, 35, _heart[i].anime);
	}

	//코인 스코어 프레임
	if (_coinTest >= 1000)
	{
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 60, 20, _coinTest / 1000 % 10, 0);
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 50, 20, _coinTest / 100 % 10, 0);
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 40, 20, _coinTest / 10 % 10, 0);
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 30, 20, _coinTest % 10, 0);
	}
	if (_coinTest >= 100 && _coinTest < 1000)
	{
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 60, 20, _coinTest / 100 % 10, 0);
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 50, 20, _coinTest / 10 % 10, 0);
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 40, 20, _coinTest % 10, 0);
	}
	if (_coinTest >= 10 && _coinTest < 100)
	{
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 60, 20, _coinTest / 10 % 10, 0);
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 50, 20, _coinTest % 10, 0);
	}
	if (_coinTest < 10)
	{
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 60, 20, _coinTest % 10, 0);
	}

	//다이아 스코어 프레임
	if (_coinTest >= 1000)
	{
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 60, 80, _diaTest / 1000 % 10, 0);
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 50, 80, _diaTest / 100 % 10, 0);
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 40, 80, _diaTest / 10 % 10, 0);
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 30, 80, _diaTest % 10, 0);
	}
	if (_coinTest >= 100 && _coinTest < 1000)
	{
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 60, 60, _diaTest / 100 % 10, 0);
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 50, 60, _diaTest / 10 % 10, 0);
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 40, 60, _diaTest % 10, 0);
	}
	if (_coinTest >= 10 && _coinTest < 100)
	{
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 60, 60, _diaTest / 10 % 10, 0);
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 50, 60, _diaTest % 10, 0);
	}
	if (_coinTest < 10)
	{
		_daiaNum->frameRender(getMemDC(), WINSIZEX - 60, 60, _diaTest % 10, 0);
	}

	//인벤토리에 넣을 아이템

	for (int i = 0; i < _vInven.size(); i++)
	{

			if (_vInven[i]->armor == A_ARMOR_1|| _vInven[i]->armor == A_ARMOR_2|| _vInven[i]->armor == A_ARMOR_3|| _vInven[i]->armor == A_ARMOR_4)
			{
				_bodyInven.open = true;
				IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _bodyInven.x * i / i + 5, _bodyInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
			}
			else if (_vInven[i]->armor == A_HELMET)
			{
				_headInven.open = true;
				IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _headInven.x * i / i + 5, _headInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
			}
			else if (_vInven[i]->armor == A_SHOVEL)
			{
				_shovelInven.open = true;
				IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), (_shovelInven.x * i) / (i + 5), _shovelInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
			}
			else if (_vInven[i]->armor == A_TORCH_1|| _vInven[i]->armor == A_TORCH_2|| _vInven[i]->armor == A_TORCH_3)
			{
				_torchInven.open = true;
				IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _torchInven.x * i / i + 5, _torchInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
			}
			else if (_vInven[i]->armor == A_RING)
			{
				_ringInven.open = true;
				IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), _ringInven.x * i / i + 5, _ringInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
			}

		if (_vInven[i]->weapon != WP_NONE &&_vInven[i]->weapon != WP_DAGGER_1 && _vInven[i]->weapon != WP_DAGGER_2)
		{
			_attackInven.open = true;
			_throwInven.open = false;
			IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), _attackInven.x * i / i+5, _attackInven.y +10, _vInven[i]->frameX, _vInven[i]->frameY);
		}
		else if (_vInven[i]->weapon == WP_DAGGER_1 || _vInven[i]->weapon == WP_DAGGER_2 )
		{
			_attackInven.open = true;
			_throwInven.open = true;
			IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), _attackInven.x * i / i + 5, _attackInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
			if (_throwInven.open)_throwInven.image->render(getMemDC(), 20, _throwInven.y), _upDown.image->render(getMemDC(), 30, _throwInven.y + 60);
			IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), _throwInven.x * i / i + 5, _throwInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
		}
		if (_vInven[i]->stuff != ST_NONE)
		{
			_itemInven.open = true;
			IMAGEMANAGER->findImage("stuffTiles")->frameRender(getMemDC(), _itemInven.x * i / i + 5, _itemInven.y + 10, _vInven[i]->frameX, _vInven[i]->frameY);
		}
	}


	//for (int i = 0; i < _vInven.size(); ++i)
	//{
	//	if (_vInven[i]->armor != A_NONE)
	//	{
	//		IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(), 20 + i * 70, 5, _vInven[i]->frameX, _vInven[i]->frameY);

	//		/*		if (_vInven[i]->armor == A_SHOVEL)
	//				{
	//					IMAGEMANAGER->findImage("armorTiles")->frameRender(getMemDC(),20 + i * 70, 5, _vInven[i]->frameX, _vInven[i]->frameY);
	//				}*/
	//	}
	//	else if (_vInven[i]->weapon != W_NONE)
	//	{
	//		IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), 20 + i * 70, 5, _vInven[i]->frameX, _vInven[i]->frameY);

	//		/*		if (_vInven[i]->weapon == WP_DAGGER_1)
	//				{
	//					IMAGEMANAGER->findImage("weaponTiles")->frameRender(getMemDC(), 20 + i * 70, 5, _vInven[i]->frameX, _vInven[i]->frameY);
	//				}*/
	//	}
	//	else continue;
	//}


	//}

	//for (int i = 0; i < _vInven.size(); ++i)
	//{
	//	if (_vInven[i]->stuff != ST_NONE)
	//	{
	//		IMAGEMANAGER->findImage("stuffTiles")->frameRender(getMemDC(), 20, 5 + i * 50, _vInven[i]->frameX, _vInven[i]->frameY);

	//	}
	//}
}
