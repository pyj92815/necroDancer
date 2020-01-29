#include "stdafx.h"
#include "Enemy_Slime_Blue.h"

HRESULT Enemy_Slime_Blue::init()
{
	ZeroMemory(&_playerInfo, sizeof(_playerInfo));
	_playerInfo = new playerInfo;

	_enemyInfo->Beat = true;
	_enemyInfo->aniChange = true;
	_enemyInfo->Light = false;
	_enemyInfo->beatCount = 0;
	light_change = _enemyInfo->Light;
	return S_OK;
}

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
	if (light_change != _enemyInfo->Light)
	{
		AniChange();
	}
}

void Enemy_Slime_Blue::Move()
{
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
		_enemyInfo->y -= 52;
		_enemyInfo->direction = Direction::DOWN;
		break;
	case Direction::DOWN:
		if (_enemyInfo->idy + 1 == _playerInfo->idy && _enemyInfo->idx == _playerInfo->idx)
		{
			_enemyInfo->state = enemyState::STATE_ATTACK;
			break;
		}
		//아래로 이동
		_enemyInfo->y += 52;
		_enemyInfo->direction = Direction::UP;
		break;
	}
}

void Enemy_Slime_Blue::Attack()
{
	switch (_enemyInfo->direction)
	{
	case Direction::UP:
		//위로 절반 이동 후 다시 제자리로
		_enemyInfo->y -= 26;

		//공격 모션 후
		_enemyInfo->state = enemyState::STATE_MOVE;
		break;
	case Direction::DOWN:
		//아래로 절반 이동 후 다시 제자리로
		_enemyInfo->y += 26;

		//공격 모션 후
		_enemyInfo->state = enemyState::STATE_MOVE;
		break;
	}
}

void Enemy_Slime_Blue::AniChange()
{
	if (_enemyInfo->Light) _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_IDLE_Ani");
	else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_Shadow_IDLE_Ani");
	_enemyInfo->aniChange = true;
	light_change = _enemyInfo->Light;
}
