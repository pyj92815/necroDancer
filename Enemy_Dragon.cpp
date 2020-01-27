#include "stdafx.h"
#include "Enemy_Dragon.h"

HRESULT Enemy_Dragon::init()
{
	_enemyInfo->image = IMAGEMANAGER->findImage("Enemy_dragonL");
	_enemyInfo->animation = KEYANIMANAGER->findAnimation("Dragon_L_Shadow_IDLE_Ani");
	return S_OK;
}

void Enemy_Dragon::AniChange()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Dragon_L_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Dragon_L_Shadow_IDLE_Ani");
		break;
	case Direction::RIGHT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Dragon_R_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Dragon_R_Shadow_IDLE_Ani");
		break;
	}
}
