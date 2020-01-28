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
	//�� ���ڸ��� �����̸� �� �Ʒ� 2���� Ÿ�ϸ��� �պ��ϸ� �����δ�. �̵� ��ο� ���� �ִٸ� ���ڸ� ������ �Ѵ�.
	if (BEATMANAGER->getInterval())
	{
		switch (_enemyInfo->direction)
		{
		case Direction::UP:
			//�̵� ��ο� �÷��̾ ������
			//_enemyInfo->state = enemyState::STATE_ATTACK;
			//���� �̵�
			_enemyInfo->y -= 10;
			_enemyInfo->direction = Direction::DOWN;
			break;
		case Direction::DOWN:
			//�̵� ��ο� �÷��̾ ������
			//_enemyInfo->state = enemyState::STATE_ATTACK;
			//�Ʒ��� �̵�
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
		//���� ���� �̵� �� �ٽ� ���ڸ��� + �ش� �������� ���� ���
		_enemyInfo->state = enemyState::STATE_MOVE;
		break;
	case Direction::DOWN:
		//�Ʒ��� ���� �̵� �� �ٽ� ���ڸ��� + �ش� �������� ���� ���
		_enemyInfo->state = enemyState::STATE_MOVE;
		break;
	}
}

void Enemy_Slime_Blue::AniChange()
{
	//�ݹ� �Լ��� ����� �̹����� �ٲ�븶�� ������ �޾ƿ� �� �ֵ���
	if (_enemyInfo->Light)_enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_IDLE_Ani");
	else _enemyInfo->animation = KEYANIMANAGER->findAnimation("Enemy_slime_blue_Shadow_IDLE_Ani");
}
