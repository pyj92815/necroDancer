#include "stdafx.h"
#include "Enemy_Zombie.h"

HRESULT Enemy_Zombie::init()
{
	_enemyInfo->image = IMAGEMANAGER->findImage("Enemy_zombie");
	_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_zombie_Shadow_LEFT_Ani");

	return S_OK;
}

void Enemy_Zombie::AniChange()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_zombie_LEFT_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_zombie_Shadow_LEFT_Ani");
		break;
	case Direction::RIGHT:
		if(_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_zombie_RIGHT_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_zombie_Shadow_RIGHT_Ani");
		break;
	case Direction::UP:
		if(_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_zombie_UP_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_zombie_Shadow_UP_Ani");
		break;
	case Direction::DOWN:
		if(_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_zombie_DOWN_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_zombie_Shadow_DOWN_Ani");
		break;
	}
	
}

