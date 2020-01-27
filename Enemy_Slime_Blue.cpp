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
	//두 박자마다 움직이며 위 아래 2개의 타일만을 왕복하며 움직인다. 이동 경로에 벽이 있다면 제자리 점프를 한다.
	switch (_enemyInfo->direction)
	{
	case Direction::UP:
		//위로 이동
		_enemyInfo->direction = Direction::DOWN;
		break;
	case Direction::DOWN:
		//아래로 이동
		_enemyInfo->direction = Direction::UP;
		break;
	}
}

void Enemy_Slime_Blue::AniChange()
{
	if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_IDLE_Ani");
	else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_Shadow_IDLE_Ani");
}
