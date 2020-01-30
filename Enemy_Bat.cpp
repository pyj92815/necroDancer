#include "stdafx.h"
#include "Enemy_Bat.h"

void Enemy_Bat::Action()
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

void Enemy_Bat::Move()
{
	//����� �� ���ڸ��� ������������ ��ĭ�� �̵��Ѵ�.
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		//�̵� ��ο� �÷��̾ ������
		_enemyInfo->state = enemyState::STATE_ATTACK;
		//�·� �̵�
		break;
	case Direction::RIGHT:
		//�̵� ��ο� �÷��̾ ������
		_enemyInfo->state = enemyState::STATE_ATTACK;
		//��� �̵�
		break;
	case Direction::UP:
		//�̵� ��ο� �÷��̾ ������
		_enemyInfo->state = enemyState::STATE_ATTACK;
		//���� �̵�
		break;
	case Direction::DOWN:
		//�̵� ��ο� �÷��̾ ������
		_enemyInfo->state = enemyState::STATE_ATTACK;
		//�Ʒ��� �̵�
		break;
	}
}

void Enemy_Bat::RandDirection()
{
	int rand_Num = RND->getInt(4);

	if (rand_Num == 0)
	{
		_enemyInfo->direction = Direction::LEFT;
	}
	else if (rand_Num == 1)
	{
		_enemyInfo->direction = Direction::RIGHT;
	}
	else if (rand_Num == 2)
	{
		_enemyInfo->direction = Direction::UP;
	}
	else if (rand_Num == 3)
	{
		_enemyInfo->direction = Direction::DOWN;
	}
}

void Enemy_Bat::AniChange()
{

	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Bat_L_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Bat_L_Shadow_IDLE_Ani");
		break;

	case Direction::RIGHT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Bat_R_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Bat_R_Shadow_IDLE_Ani");
		break;
	}
	_enemyInfo->aniChange = true;
}
