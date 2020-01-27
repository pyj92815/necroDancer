#include "stdafx.h"
#include "Enemy_Skeleton.h"

HRESULT Enemy_Skeleton::init()
{
	_enemyInfo->image = IMAGEMANAGER->findImage("Enemy_skeletonL");
	_enemyInfo->animation = KEYANIMANAGER->findAnimation("Skeleton_L_Shadow_IDLE_Ani");
	return S_OK;
}

void Enemy_Skeleton::Move()
{
	//두 박자마다 플레이어를 쫓아 움직인다.
}

void Enemy_Skeleton::AniChange()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("skeleton_L_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Skeleton_L_Shadow_IDLE_Ani");
		break;
	case Direction::RIGHT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("skeleton_R_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Skeleton_R_Shadow_IDLE_Ani");
		break;
	}
}
