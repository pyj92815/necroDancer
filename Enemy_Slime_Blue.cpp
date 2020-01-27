#include "stdafx.h"
#include "Enemy_Slime_Blue.h"

HRESULT Enemy_Slime_Blue::init()
{
	_enemyInfo->image = IMAGEMANAGER->findImage("Enemy_slime_blueL");
	_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_L_Shadow_IDLE_Ani");
	return S_OK;
}

void Enemy_Slime_Blue::AniChange()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_L_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_L_Shadow_IDLE_Ani");
		break;
	case Direction::RIGHT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_R_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_R_Shadow_IDLE_Ani");
		break;
	}
}
