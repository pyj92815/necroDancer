#include "stdafx.h"
#include "Enemy_Warith.h"

HRESULT Enemy_Warith::init()
{
	_enemyInfo->image = IMAGEMANAGER->findImage("Enemy_wraithL");
	_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_wraith_L_Shadow_IDLE_Ani");
	return S_OK;
}

void Enemy_Warith::AniChange()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_wraith_L_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_wraith_L_Shadow_IDLE_Ani");
		break;
	case Direction::RIGHT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_wraith_R_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_wraith_R_Shadow_IDLE_Ani");
		break;
	}
}
