#include "stdafx.h"
#include "Enemy_Bat.h"

HRESULT Enemy_Bat::init()
{
	_enemyInfo->image = IMAGEMANAGER->findImage("Enemy_batL");
	_enemyInfo->animation = KEYANIMANAGER->findAnimation("Bat_L_Shadow_IDLE_Ani");
	return S_OK;
}

void Enemy_Bat::Move()
{
	//����� �� ���ڸ��� ������������ ��ĭ�� �̵��Ѵ�.
	int rand_Num = RND->getInt(4);
	if (rand_Num == 0)
	{
		//�·� �̵�
	}
	else if (rand_Num == 1)
	{
		//��� �̵�
	}
	else if (rand_Num == 2)
	{
		//���� �̵�
	}
	else if (rand_Num == 3)
	{
		//�Ʒ��� �̵�
	}

}

void Enemy_Bat::AniChange()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Bat_L_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Bat_R_IDLE_Ani");
		break;
	case Direction::RIGHT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Bat_L_Shadow_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Bat_R_Shadow_IDLE_Ani");
		break;
	}
}
