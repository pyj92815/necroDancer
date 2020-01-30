#include "stdafx.h"
#include "Enemy_Skeleton_Yellow.h"

void Enemy_Skeleton_Yellow::Action()
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

void Enemy_Skeleton_Yellow::Move()
{
	//�� ���ڸ��� �����δ�. ü���� 1�� �Ǹ� ���� ���ư��� �÷��̾ ������ �ݴ� �������� ��������.
}

void Enemy_Skeleton_Yellow::AniChange()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("skeleton_yellow_L_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("skeleton_yellow_L_Shadow_IDLE_Ani");
		break;
	case Direction::RIGHT:
		if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("skeleton_yellow_R_IDLE_Ani");
		else _enemyInfo->animation = KEYANIMANAGER->findAnimation("skeleton_yellow_R_Shadow_IDLE_Ani");
		break;
	}
	_enemyInfo->aniChange = true;
}
