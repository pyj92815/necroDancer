#include "stdafx.h"
#include "Enemy_Slime_Orange.h"

void Enemy_Slime_Orange::Action()
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
	//

}

void Enemy_Slime_Orange::Move()
{
	if (!_enemyInfo->Move)_enemyInfo->worldTimeCount = TIMEMANAGER->getWorldTime();
	_enemyInfo->Attack = false;
	//한 박자마다 오른쪽->아래->왼쪽->위 순서를 반복하며 움직인다.
	switch (_enemyInfo->direction)
	{
	case Direction::RIGHT:
		//오른쪽으로 이동 (이동 경로에 플레이어가 있으면 공격)
		if (_enemyInfo->idx + 1 == _playerInfo->idx && _enemyInfo->idy == _playerInfo->idy)
		{
			//오른쪽 공격
			_enemyInfo->state = enemyState::STATE_ATTACK;
			_enemyInfo->AttackDirection = Direction::RIGHT;
			break;
		}
		//_enemyInfo->x += 52;
		_enemyInfo->idx += 1;

		
		enemyAngle();
		_enemyInfo->direction = Direction::DOWN;
		break;
	case Direction::DOWN:
		//아래로 이동 (이동 경로에 플레이어가 있으면 공격)
		if (_enemyInfo->idx == _playerInfo->idx && _enemyInfo->idy + 1 == _playerInfo->idy)
		{
			//아래쪽 공격
			_enemyInfo->state = enemyState::STATE_ATTACK;
			_enemyInfo->AttackDirection = Direction::DOWN;
			break;
		}
		//_enemyInfo->y += 52;
		_enemyInfo->idy += 1;

		
		enemyAngle();
		_enemyInfo->direction = Direction::LEFT;
		break;
	case Direction::LEFT:
		//왼쪽으로 이동 (이동 경로에 플레이어가 있으면 공격)
		if (_enemyInfo->idx - 1 == _playerInfo->idx && _enemyInfo->idy == _playerInfo->idy)
		{
			//왼쪽 공격
			_enemyInfo->state = enemyState::STATE_ATTACK;
			_enemyInfo->AttackDirection = Direction::LEFT;
			break;
		}
		//_enemyInfo->x -= 52;
		_enemyInfo->idx -= 1;

		
		enemyAngle();
		_enemyInfo->direction = Direction::UP;
		break;
	case Direction::UP:
		//위로 이동 (이동 경로에 플레이어가 있으면 공격)
		if (_enemyInfo->idx == _playerInfo->idx && _enemyInfo->idy - 1 == _playerInfo->idy)
		{
			//위쪽 공격
			_enemyInfo->state == enemyState::STATE_ATTACK;
			_enemyInfo->AttackDirection = Direction::UP;
			break;
		}
		//_enemyInfo->y -= 52;
		_enemyInfo->idy -= 1;
		enemyAngle();
		_enemyInfo->direction = Direction::RIGHT;
		break;
	}
	_enemyInfo->Move = true;
}

void Enemy_Slime_Orange::AniChange()
{
	if (_enemyInfo->Light)_enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_slime_orange_IDLE_Ani");
	else _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_slime_orange_Shadow_IDLE_Ani");
	_enemyInfo->aniChange = true;
}
