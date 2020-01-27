#include "stdafx.h"
#include "Enemy_Ghost.h"

HRESULT Enemy_Ghost::init()
{
	_enemyInfo->image = IMAGEMANAGER->findImage("Enemy_ghostL");
	_enemyInfo->animation = KEYANIMANAGER->findAnimation("Ghost_L_Shadow_IDLE_Ani");
	return S_OK;
}

void Enemy_Ghost::AniChange()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Ghost_L_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Ghost_L_Shadow_IDLE_Ani");
		break;
	case Direction::RIGHT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Ghost_R_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Ghost_R_Shadow_IDLE_Ani");
		break;
	}
}
