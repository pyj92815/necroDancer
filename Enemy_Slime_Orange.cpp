#include "stdafx.h"
#include "Enemy_Slime_Orange.h"

void Enemy_Slime_Orange::Action()
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

void Enemy_Slime_Orange::Move()
{
	//한 박자마다 오른쪽->아래->왼쪽->위 순서를 반복하며 움직인다.
	switch (_enemyInfo->direction)
	{
	case Direction::RIGHT:
		//으론쪽으로 이동
		_enemyInfo->direction = Direction::DOWN;
		break;
	case Direction::DOWN:
		//아래로 이동
		_enemyInfo->direction = Direction::LEFT;
		break;
	case Direction::LEFT:
		//왼쪽으로 이동
		_enemyInfo->direction = Direction::UP;
		break;
	case Direction::UP:
		//위로 이동
		_enemyInfo->direction = Direction::RIGHT;
		break;
	}

}

void Enemy_Slime_Orange::AniChange()
{
	if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_orange_IDLE_Ani");
	else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_orange_Shadow_IDLE_Ani");
	_enemyInfo->aniChange = true;
}
