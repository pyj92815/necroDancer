#include "stdafx.h"
#include "Enemy_Warith.h"

void Enemy_Warith::Action()
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
		Attack();
		break;
	case enemyState::STATE_DIE:
		break;
	default:
		break;
	}
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
	_enemyInfo->aniChange = true;
}
