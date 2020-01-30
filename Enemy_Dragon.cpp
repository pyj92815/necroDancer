#include "stdafx.h"
#include "Enemy_Dragon.h"

void Enemy_Dragon::Action()
{
	switch (_enemyInfo->state)
	{
	case enemyState::STATE_IDLE:
		break;
	case enemyState::STATE_MOVE:
		if (_enemyInfo->beatCount >= 2)
		{
			Move();
			_enemyInfo->beatCount = 0;
		}
		break;
	case enemyState::STATE_ATTACK:
		Attack();
		break;
	case enemyState::STATE_DIE:
		break;
	default:
		break;
	}
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
	_enemyInfo->aniChange = true;
}
