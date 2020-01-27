#include "stdafx.h"
#include "Enemy_Slime_Orange.h"

HRESULT Enemy_Slime_Orange::init()
{
	_enemyInfo->image = IMAGEMANAGER->findImage("Enemy_slime_orangeL");
	_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_orange_L_Shadow_IDLE_Ani");
	return S_OK;
}

void Enemy_Slime_Orange::AniChange()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_orange_L_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_orange_L_Shadow_IDLE_Ani");
		break;
	case Direction::RIGHT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_orange_R_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_orange_R_Shadow_IDLE_Ani");
		break;
	}
}
