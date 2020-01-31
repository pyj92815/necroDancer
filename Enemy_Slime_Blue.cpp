#include "stdafx.h"
#include "Enemy_Slime_Blue.h"


void Enemy_Slime_Blue::Action()
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
	}
	//
	
}

void Enemy_Slime_Blue::Move()
{
	if (!_enemyInfo->Move)_enemyInfo->worldTimeCount = TIMEMANAGER->getWorldTime();
	_enemyInfo->Attack = false;
	//두 박자마다 움직이며 위 아래 2개의 타일만을 왕복하며 움직인다. 이동 경로에 벽이 있다면 제자리 점프를 한다.
	switch (_enemyInfo->direction)
	{
	case Direction::UP:
		if (_enemyInfo->idy - 1 == _playerInfo->idy && _enemyInfo->idx == _playerInfo->idx)
		{
			_enemyInfo->state = enemyState::STATE_ATTACK;
			break;
		}
		//위로 이동
		_enemyInfo->idy -= 1;
		//_enemyInfo->direction = Direction::DOWN;
		enemyAngle();
		break;
	case Direction::DOWN:
		if (_enemyInfo->idy + 1 == _playerInfo->idy && _enemyInfo->idx == _playerInfo->idx)
		{
			_enemyInfo->state = enemyState::STATE_ATTACK;
			break;
		}
		//아래로 이동
		_enemyInfo->idy += 1;
		//_enemyInfo->direction = Direction::UP;
		enemyAngle();
		break;
	}
	_enemyInfo->Move = true;
}

void Enemy_Slime_Blue::moveAction()
{
}

void Enemy_Slime_Blue::enemyAngle()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:

		_enemyInfo->angle = getAngle(_enemyInfo->x, _enemyInfo->y, _enemyInfo->x -= 52, _enemyInfo->y);
		break;
	case Direction::RIGHT:
		_enemyInfo->angle = getAngle(_enemyInfo->x, _enemyInfo->y, _enemyInfo->x + 52, _enemyInfo->y);

		break;
	case Direction::UP:

		_enemyInfo->angle = getAngle(_enemyInfo->x, _enemyInfo->y, _enemyInfo->x, _enemyInfo->y - 52);
		_enemyInfo->direction = Direction::DOWN;

		break;
	case Direction::DOWN:

		_enemyInfo->angle = getAngle(_enemyInfo->x, _enemyInfo->y, _enemyInfo->x, _enemyInfo->y + 52);
		_enemyInfo->direction = Direction::UP;
		break;
	}
}

void Enemy_Slime_Blue::Attack()
{
	switch (_enemyInfo->direction)
	{
	case Direction::UP:
		_enemyInfo->attackImage = IMAGEMANAGER->findImage("Enemy_Attack_Up");
		_enemyInfo->attackAnimation = KEYANIMANAGER->findAnimation("Enemy_Attack_UP_Ani");
		_enemyInfo->Attack = true;
		break;
	case Direction::DOWN:
		_enemyInfo->attackImage = IMAGEMANAGER->findImage("Enemy_Attack_Down");
		_enemyInfo->attackAnimation = KEYANIMANAGER->findAnimation("Enemy_Attack_DOWN_Ani");
		_enemyInfo->Attack = true;
		break;
	}
	if (_enemyInfo->Attack)
	{
		_enemyInfo->attackAnimation->start();
	}
	_enemyInfo->state = enemyState::STATE_MOVE;
}

void Enemy_Slime_Blue::AniChange()
{
	if (_enemyInfo->Light) _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_IDLE_Ani");
	else _enemyInfo->Animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_Shadow_IDLE_Ani");
	_enemyInfo->aniChange = true;
}
