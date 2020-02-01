#include "stdafx.h"
#include "Enemy_Ghost.h"

void Enemy_Ghost::Action()
{
	switch (_enemyInfo->state)
	{
	case enemyState::STATE_IDLE:
		break;
	case enemyState::STATE_MOVE:
		if (_enemyInfo->beatCount >= 1)
		{
			Move();
			_enemyInfo->beatCount = 0;
		}	
		break;
	case enemyState::STATE_ATTACK:
		if (_enemyInfo->beatCount >= 2)
		{
			Attack();
			_enemyInfo->beatCount = 0;
		}

	
		break;
	case enemyState::STATE_DIE:
		break;
	default:
		break;
	}
}

void Enemy_Ghost::AniChange()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->Light)_enemyInfo->Animation = KEYANIMANAGER->findAnimation("Ghost_L_IDLE_Ani");
		else _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Ghost_L_Shadow_IDLE_Ani");
		break;
	case Direction::RIGHT:
		if (_enemyInfo->Light)_enemyInfo->Animation = KEYANIMANAGER->findAnimation("Ghost_R_IDLE_Ani");
		else _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Ghost_R_Shadow_IDLE_Ani");
		break;
	}
	_enemyInfo->aniChange = true;
}
