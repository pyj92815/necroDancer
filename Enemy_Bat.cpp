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
	//박쥐는 두 박자마다 랜덤방향으로 한칸씩 이동한다.
	int rand_Num = RND->getInt(4);
	if (rand_Num == 0)
	{
		//좌로 이동
	}
	else if (rand_Num == 1)
	{
		//우로 이동
	}
	else if (rand_Num == 2)
	{
		//위로 이동
	}
	else if (rand_Num == 3)
	{
		//아래로 이동
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
