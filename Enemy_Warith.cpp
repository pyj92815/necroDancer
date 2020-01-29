#include "stdafx.h"
#include "Enemy_Warith.h"

void Enemy_Warith::Action()
{
	switch (_enemyInfo->state)
	{
	case enemyState::STATE_IDLE:
		break;
	case enemyState::STATE_MOVE:
		Move();
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

void Enemy_Warith::Move()
{
	//한 박자마다 플레이어를 쫓아 움직인다.
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
