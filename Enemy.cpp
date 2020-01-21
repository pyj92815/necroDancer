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
	_enemyInfo->discoveryRc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, 52 * 7, 52 * 7);

}

void Enemy::render()
{

}

void Enemy::Action()
{
	switch (_enemyInfo->state)
	{
	case enemyState::STATE_IDLE:
		//if(IntersectRect())
		break;
	case enemyState::STATE_DISCOVERY:
		break;
	case enemyState::STATE_MOVE:
		break;
	case enemyState::STATE_ATTACK:
		break;
	case enemyState::STATE_DIE:
		break;
	default:
		break;
	}
}

void Enemy::Move()
{
}

void Enemy::EnemyCreate(float x, float y, float HP, float damage,const char* enemyName1, const char* enemyName2)
{
	ZeroMemory(&_enemyInfo, sizeof(_enemyInfo));
	_enemyInfo = new EnemyInfo;
	_enemyInfo->state = enemyState::STATE_IDLE;
	_enemyInfo->x = x;
	_enemyInfo->y = y;
	_enemyInfo->HP = HP;
	_enemyInfo->damage = damage;
	_enemyInfo->image1 = IMAGEMANAGER->findImage(enemyName1);
	_enemyInfo->image2 = IMAGEMANAGER->findImage(enemyName2);
	_enemyInfo->rc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, _enemyInfo->image1->getFrameWidth(), _enemyInfo->image1->getFrameHeight());
}