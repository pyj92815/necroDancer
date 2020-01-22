#include "stdafx.h"
#include "UImanager.h"

HRESULT UImanager::init()
{
	//���� �κ��丮
	_attackInven.image = IMAGEMANAGER->addImage("attack_Inven", "./image/UI/hud_slot_2.bmp", 60, 66, true, RGB(255, 0, 255));
	_shovelInven.image = IMAGEMANAGER->addImage("shovel_Inven", "./image/UI/hud_slot_1.bmp", 60, 66, true, RGB(255, 0, 255));
	_itemInven.image = IMAGEMANAGER->addImage("item_Inven", "./image/UI/hud_slot_action1.bmp", 60, 84, true, RGB(255, 0, 255));
	_bombInven.image = IMAGEMANAGER->addImage("bomb_Inven", "./image/UI/hud_slot_bomb.bmp", 60, 84, true, RGB(255, 0, 255));
	_throwInven.image = IMAGEMANAGER->addImage("throw_Inven", "./image/UI/hud_slot_throw.bmp", 60, 84, true, RGB(255, 0, 255));
	_bodyInven.image = IMAGEMANAGER->addImage("body_Inven", "./image/UI/hud_slot_3.bmp", 60, 66, true, RGB(255, 0, 255));
	_headInven.image = IMAGEMANAGER->addImage("head_Inven", "./image/UI/hud_slot_4.bmp", 60, 66, true, RGB(255, 0, 255));

	//������ �κ��丮
	_coinInven.image = IMAGEMANAGER->addImage("coin_Inven", "./image/UI/hud_coins.bmp", 48, 48, true, RGB(255, 0, 255));
	_daiaInven.image = IMAGEMANAGER->addImage("daia_Inven", "./image/UI/diamond.bmp", 50, 48, true, RGB(255, 0, 255));

	_scoreNum = IMAGEMANAGER->addFrameImage("number", "./image/UI/number.bmp", 80, 20, 10, 1, true, RGB(255, 0, 255));
	_scoreX = IMAGEMANAGER->addImage("numberX", "./image/UI/x.bmp", 8, 8, true, RGB(255, 0, 255));
	_daiaNum = IMAGEMANAGER->addFrameImage("number", "./image/UI/number.bmp", 80, 20, 10, 1, true, RGB(255, 0, 255));

	//���ڵ�
	_downLeft.image = IMAGEMANAGER->addImage("down_Left", "./image/UI/down_left_x2.bmp", 46, 48, true, RGB(255, 0, 255));
	_upDown.image = IMAGEMANAGER->addImage("up_Down", "./image/UI/up_down_x2.bmp", 46, 48, true, RGB(255, 0, 255));
	_upLeft.image = IMAGEMANAGER->addImage("up_Left", "./image/UI/up_left_x2.bmp", 46, 48, true, RGB(255, 0, 255));

	//��Ʈ
	IMAGEMANAGER->addFrameImage("heart_full", "./image/UI/heart_full.bmp", 109, 50, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heart_half", "./image/UI/heart_half.bmp", 109, 50, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("heart_null", "./image/UI/heart_null.bmp", 96, 44, 2, 1, true, RGB(255, 0, 255));

	for (int i = 0; i < 3; i++)
	{
		_heart[i].state = HEARTSTATE_FULL;								//��Ʈ���� �ʱ�ȭ
		_heart[i].image = IMAGEMANAGER->findImage("heart_full");		//��Ʈ���� �̹���
	}

	//�ִϸ��̼� ================================

		int heartFull[] = { 0 };
		KEYANIMANAGER->addArrayFrameAnimation("heart_full_ani", "heart_full", heartFull, 2, 10, true);		
		int heartFull_move[] = { 0,1 };		//�ִϸ��̼ǸŴ����� �������̹��� ���� ���� �ʱ�ȭ								
		KEYANIMANAGER->addArrayFrameAnimation("heart_full_ani_move", "heart_full", heartFull_move, 2, 10, true);
	
	for (int i = 0; i < 3; i++)
	{
		_heart[i].anime = KEYANIMANAGER->findAnimation("heart_full_ani_move");				//�ִϸ��̼� ù��° Ű�� �ʱ�ȭ
	/*	_heart[1].anime = KEYANIMANAGER->findAnimation("heart_full_ani");
		_heart[2].anime = KEYANIMANAGER->findAnimation("heart_full_ani");*/
		//���� [1],[2]ó�� �ִϸ��̼� ���� ���س����� �迭 ���� ���� ���� �ִ�
		//������ �ؿ� ������Ʈ���� ���� �����س����� �ǹǷ� �׳� _heart[i].anime�� �ؾ� �Ǵ���..
		_heart[i].anime->start();															//���ϸ��̼� ��ŸƮ
	}
	//============================================

	hp = 6;
	
	_coinTest = 7259;								//���� �׽�Ʈ
	_diaTest = 2369;								//���̾� �׽�Ʈ

	_heartBeatCnt = 0;								//��Ʈ��Ʈ ī��Ʈ

	return S_OK;
}

void UImanager::release()
{

}

void UImanager::update()
{
	//=========�׽�Ʈ�� ���� Ű====================
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		hp--;
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		hp++;
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_heartBeatCnt++;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_heartBeatCnt--;
	}
	//=======================================

	//HP�� ���� ��Ʈ�� ���� ����
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

	//��Ʈ ���¿� ���� �ش� �̹��� ã��
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
	
	//��Ʈ��Ʈ�� �޾ƿ��� ������ ��=========================================
	//��Ʈ��Ʈ�� ������ ++���ٰ�
	//��Ʈ��Ʈ�� ���� ��Ʈ�� �ٴ� ��ġ�� �ٸ��� ���� ����
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
			_heartBeatCnt = 0;		//����ִ� ��Ʈ�� ù��° ��Ʈ���� �ִϸ��̼� �ǵ��� ����ó��
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

	for (int i = 0; i < 3; i++)				//�ٴ� ���¿�,�ƴ� ������ �ִϸ��̼� �ֱ�
	{
		if (_heart[i].turn ==TURN_ON)
		{
			_heart[i].anime = KEYANIMANAGER->findAnimation("heart_full_ani_move");
		}
		else if (_heart[i].turn == TURN_OFF)
		{
			_heart[i].anime = KEYANIMANAGER->findAnimation("heart_full_ani");
		}
		
	}

	//====================================================================
}

void UImanager::render()
{
	//���� �κ��丮
	_shovelInven.image->render(getMemDC(), 20, 5);
	_attackInven.image->render(getMemDC(), 90, 5);
	_itemInven.image->render(getMemDC(), 20, 81);
	_throwInven.image->render(getMemDC(), 20, 195);
	_bombInven.image->render(getMemDC(), 20, 299);

	//������ �κ��丮
	_coinInven.image->render(getMemDC(), WINSIZEX - 125, 5);
	_daiaInven.image->render(getMemDC(), WINSIZEX - 125, 65);
	_scoreX->render(getMemDC(),WINSIZEX -72, 30);
	_scoreX->render(getMemDC(), WINSIZEX - 72, 90);

	//���ڵ�
	_downLeft.image->render(getMemDC(), 30, 359);
	_upDown.image->render(getMemDC(), 30, 255);
	_upLeft.image->render(getMemDC(), 30, 141);

	//��Ʈ �̹��� & �ִϸ��̼�
	for (int i = 0; i < 3; i++)
	{
		_heart[i].image->frameRender(getMemDC(), 573 + i * 60, 12,0,0);
		_heart[i].image->aniRender(getMemDC(), 600 + i * 60, 35, _heart[i].anime);

	}

	
	//���� ���ھ� ������
	if (_coinTest >= 1000)
	{
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 60, 20, _coinTest / 1000 % 10, 0);
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 50, 20, _coinTest / 100 % 10, 0);
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 40, 20, _coinTest/10 % 10, 0);
		_scoreNum->frameRender(getMemDC(), WINSIZEX - 30, 20, _coinTest % 10, 0);
	}
	if (_coinTest >= 100 && _coinTest <1000)
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

	//���̾� ���ھ� ������
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


}
