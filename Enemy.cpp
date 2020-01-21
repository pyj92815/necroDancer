#include "stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init()
{
	//ZeroMemory(&_enemyInfo, sizeof(_enemyInfo));
	
	//_enemyInfo = new EnemyInfo;
	/*int Bat_Idle[] = { 0,1,2,3};
	_enemyInfo->image = IMAGEMANAGER->findImage("Enemy_bat");
	KEYANIMANAGER->addArrayFrameAnimation("BatAnimaition", "Enemy_bat", Bat_Idle, 4, 10, true);
	_enemyInfo->animation = KEYANIMANAGER->findAnimation("BatAnimaition");*/

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
	_enemyInfo->image->aniRender(getMemDC(),WINSIZEX/2,WINSIZEY/2,_enemyInfo->animation);
}

void Enemy::EnemyCreate(float x, float y, float HP, float damage, const char* enemyName)
{
	ZeroMemory(&_enemyInfo, sizeof(_enemyInfo));
	_enemyInfo = new EnemyInfo;
	_enemyInfo->x = x;
	_enemyInfo->y = y;
	_enemyInfo->HP = HP;
	_enemyInfo->damage = damage;
	_enemyInfo->image = IMAGEMANAGER->findImage(enemyName);
}