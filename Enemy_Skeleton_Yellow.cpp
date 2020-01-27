#include "stdafx.h"
#include "Enemy_Skeleton_Yellow.h"

HRESULT Enemy_Skeleton_Yellow::init()
{
	_enemyInfo->image = IMAGEMANAGER->findImage("Enemy_skeleton_yellowL");
	_enemyInfo->animation = KEYANIMANAGER->findAnimation("skeleton_yellow_L_Shadow_IDLE_Ani");
	return S_OK;
}

void Enemy_Skeleton_Yellow::AniChange()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("skeleton_yellow_L_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("skeleton_yellow_L_Shadow_IDLE_Ani");
		break;
	case Direction::RIGHT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("skeleton_yellow_R_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("skeleton_yellow_R_Shadow_IDLE_Ani");
		break;
	}
}
