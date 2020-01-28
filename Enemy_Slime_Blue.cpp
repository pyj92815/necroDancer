#include "stdafx.h"
#include "Enemy_Slime_Blue.h"

HRESULT Enemy_Slime_Blue::init()
{
	return S_OK;
}

void Enemy_Slime_Blue::Action()
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

void Enemy_Slime_Blue::Move()
{
	//두 박자마다 움직이며 위 아래 2개의 타일만을 왕복하며 움직인다. 이동 경로에 벽이 있다면 제자리 점프를 한다.
	if (BEATMANAGER->getInterval())
	{
		switch (_enemyInfo->direction)
		{
		case Direction::UP:
			//이동 경로에 플레이어가 있으면
			//_enemyInfo->state = enemyState::STATE_ATTACK;
			//위로 이동
			_enemyInfo->y -= 10;
			_enemyInfo->direction = Direction::DOWN;
			break;
		case Direction::DOWN:
			//이동 경로에 플레이어가 있으면
			//_enemyInfo->state = enemyState::STATE_ATTACK;
			//아래로 이동
			_enemyInfo->y += 10;
			_enemyInfo->direction = Direction::UP;
			break;
		}
	}
	else
	{

	}
	
}

void Enemy_Slime_Blue::Attack()
{
	switch (_enemyInfo->direction)
	{
	case Direction::UP:
		//위로 절반 이동 후 다시 제자리로 + 해당 방향으로 공격 모션
		_enemyInfo->state = enemyState::STATE_MOVE;
		break;
	case Direction::DOWN:
		//아래로 절반 이동 후 다시 제자리로 + 해당 방향으로 공격 모션
		_enemyInfo->state = enemyState::STATE_MOVE;
		break;
	}
}

void Enemy_Slime_Blue::AniChange()
{
	//콜백 함수를 사용해 이미지가 바뀔대마다 정보를 받아올 수 있도록
	if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_IDLE_Ani");
	else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_Shadow_IDLE_Ani");
}
