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
}

void Enemy::render()
{
	IMAGEMANAGER->findImage(_enemyInfo->enemyName1)->aniRender(CAMERAMANAGER->getWorldDC(), _enemyInfo->x, _enemyInfo->y, KEYANIMANAGER->findAnimation(_enemyInfo->animation));
}

void Enemy::Action()
{
	switch (_enemyInfo->state)
	{
	case enemyState::STATE_IDLE:
		break;
	case enemyState::STATE_DISCOVERY:
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

void Enemy::EnemyCreate(float x, float y, float HP, float damage,const char* enemyName1, const char* enemyName2)
{
	ZeroMemory(&_enemyInfo, sizeof(_enemyInfo));
	_enemyInfo = new EnemyInfo;
	_enemyInfo->state = enemyState::STATE_IDLE;
	_enemyInfo->x = x;
	_enemyInfo->y = y;
	_enemyInfo->HP = HP;
	_enemyInfo->damage = damage;
	_enemyInfo->enemyName1 = enemyName1;
	_enemyInfo->enemyName2 = enemyName2;
	//_enemyInfo->rc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y,IMAGEMANAGER->findImage(enemyName1)->getFrameWidth(), IMAGEMANAGER->findImage(enemyName1)->getFrameHeight());
	_enemyInfo->rc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, 52, 52);
	_enemyInfo->animation = "Enemy_zombie_UP_Ani";
	_enemyInfo->discoveryRc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, 52 * 7, 52 * 7);
	KEYANIMANAGER->findAnimation(_enemyInfo->animation)->start();
}