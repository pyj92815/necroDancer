#include "stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init()
{
	
	return S_OK;
}

void Enemy::relase()
{
}

void Enemy::update()
{
	AniChange();
	Move();
}

void Enemy::render()
{
	_enemyInfo->image->aniRender(CAMERAMANAGER->getWorldDC(), _enemyInfo->x, _enemyInfo->y, _enemyInfo->animation);
}

void Enemy::Action()
{
	switch (_enemyInfo->state)
	{
	case enemyState::STATE_IDLE:
		break;
	case enemyState::STATE_MOVE:
		break;
	case enemyState::STATE_ATTACK:
		break;
	case enemyState::STATE_DIE:
		break;
	}
}

void Enemy::Move()
{
}

void Enemy::AniChange()
{
}

void Enemy::Attack()
{
}

void Enemy::EnemyCreate(float x, float y, float HP, float damage)
{
	ZeroMemory(&_enemyInfo, sizeof(_enemyInfo));
	_enemyInfo = new EnemyInfo;
	_enemyInfo->direction = Direction::LEFT;
	_enemyInfo->state = enemyState::STATE_IDLE;
	_enemyInfo->x = x;
	_enemyInfo->y = y;
	_enemyInfo->HP = HP;
	_enemyInfo->damage = damage;
	_enemyInfo->rc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, 52, 52);
	_enemyInfo->discoveryRc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, 52 * 7, 52 * 7);
}

void Enemy::EnemyCreate(float x, float y, float HP, float damage, Direction direction)
{
	ZeroMemory(&_enemyInfo, sizeof(_enemyInfo));
	_enemyInfo = new EnemyInfo;
	_enemyInfo->direction = direction;
	_enemyInfo->state = enemyState::STATE_IDLE;
	_enemyInfo->x = x;
	_enemyInfo->y = y;
	_enemyInfo->HP = HP;
	_enemyInfo->damage = damage;
	_enemyInfo->rc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, 52, 52);
	_enemyInfo->discoveryRc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, 52 * 7, 52 * 7);
}
