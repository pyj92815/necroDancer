#include "stdafx.h"
#include "Enemy_Slime_Blue.h"

HRESULT Enemy_Slime_Blue::init()
{
	_enemyInfo->image = IMAGEMANAGER->findImage("Enemy_slime_blue");
	_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_Shadow_IDLE_Ani");
	return S_OK;
}

void Enemy_Slime_Blue::Move()
{
	//�� ���ڸ��� �����̸� �� �Ʒ� 2���� Ÿ�ϸ��� �պ��ϸ� �����δ�. �̵� ��ο� ���� �ִٸ� ���ڸ� ������ �Ѵ�.
	switch (_enemyInfo->direction)
	{
	case Direction::UP:
		//���� �̵�
		_enemyInfo->direction = Direction::DOWN;
		break;
	case Direction::DOWN:
		//�Ʒ��� �̵�
		_enemyInfo->direction = Direction::UP;
		break;
	}
}

void Enemy_Slime_Blue::AniChange()
{
	if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_IDLE_Ani");
	else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_Shadow_IDLE_Ani");
}
