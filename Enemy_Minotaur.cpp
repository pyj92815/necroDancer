#include "stdafx.h"
#include "Enemy_Minotaur.h"

void Enemy_Minotaur::Action()
{
	switch (_enemyInfo->state)
	{
	case enemyState::STATE_IDLE:
		break;
	case enemyState::STATE_MOVE:
		if (_enemyInfo->beatCount > 1)
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

void Enemy_Minotaur::Move()
{
	//�� ���ڸ��� �����̸� 2�ܰ� ������ �μ� �� �ִ�. ���� �߿��� 3�ܰ� ���� �μ� �� �ִ�.
	//�÷��̾�� x,y��ǥ�� �ϳ��� ���̶� �������� ������ �Ѵ�.
	//���� �߿� �ٸ� ���ͳ� ���� �ε����� 2���ڰ� ���� �� ���� ���ڿ� �Ͼ �� ���� ���ں��� �����δ�.

	//if(�÷��̾��� x = enemy�� x || �÷��̾��� y = enemy�� y) _enemyInfo->state=Direction::State_ATTACK;
	if (_enemyInfo->idx != _playerInfo->idx)
	{
	if (_enemyInfo->idx > _playerInfo->idx)
	{
		_enemyInfo->idx -= 1;
		_enemyInfo->x -= 52;
	}
	else if (_enemyInfo->idx < _playerInfo->idx)
	{
		_enemyInfo->idx += 1;
		_enemyInfo->x += 52;
	}
	}
	else if (_enemyInfo->idx == _playerInfo->idx || _enemyInfo->idy == _playerInfo->idy)
	{
		_enemyInfo->state = enemyState::STATE_ATTACK;
	}
}

void Enemy_Minotaur::AniChange()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Minotaur_L_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Minotaur_L_Shadow_IDLE_Ani");
		break;
	case Direction::RIGHT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Minotaur_R_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Minotaur_R_Shadow_IDLE_Ani");
		break;
	}
	_enemyInfo->aniChange = true;
}
