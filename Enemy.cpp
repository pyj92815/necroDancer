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

}

void Enemy::Action()
{
}

void Enemy::Move()
{
}

void Enemy::EnemyCreate(float x, float y, float HP, float damage,const char* enemyName1, const char* enemyName2)
{
	ZeroMemory(&_enemyInfo, sizeof(_enemyInfo));
	_enemyInfo = new EnemyInfo;
	_enemyInfo->x = x;
	_enemyInfo->y = y;
	_enemyInfo->HP = HP;
	_enemyInfo->damage = damage;
	_enemyInfo->image1 = IMAGEMANAGER->findImage(enemyName1);
	_enemyInfo->image2 = IMAGEMANAGER->findImage(enemyName2);
}