#include "stdafx.h"
#include "Enemy_Zombie.h"

void Enemy_Zombie::Action()
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

void Enemy_Zombie::Move()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		//왼쪽으로 이동(이동 경로에 벽이 있으면 상태를 RIGHT로 바꿈)
		//_enemyInfo->direction = Direction::RIGHT;
		break;
	case Direction::RIGHT:
		//오른쪽으로 이동(이동 경로에 벽이 있으면 상태를 LEFT로 바꿈)
		//_enemyInfo->direction = Direction::LEFT;
		break;
	case Direction::UP:
		//위로 이동(이동 경로에 벽이 있으면 상태를 DOWN으로 바꿈)
		//_enemyInfo->direction = Direction::DOWN;
		break;
	case Direction::DOWN:
		//아래로 이동(이동 경로에 벽이 있으면 상태를 UP으로 바꿈)
		//_enemyInfo->direction = Direction::UP;
		break;
	}
}

void Enemy_Zombie::AniChange()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->Light) _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_zombie_LEFT_Ani");
		else _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_zombie_Shadow_LEFT_Ani");
		break;
	case Direction::RIGHT:
		if (_enemyInfo->Light) _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_zombie_RIGHT_Ani");
		else _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_zombie_Shadow_RIGHT_Ani");
		break;
	case Direction::UP:
		if (_enemyInfo->Light) _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_zombie_UP_Ani");
		else _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_zombie_Shadow_UP_Ani");
		break;
	case Direction::DOWN:
		if (_enemyInfo->Light) _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_zombie_DOWN_Ani");
		else _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_zombie_Shadow_DOWN_Ani");
		break;
	}
	_enemyInfo->aniChange = true;
}

