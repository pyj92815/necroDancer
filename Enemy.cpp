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
	Beat();
	AniChange();
	Action();
}

void Enemy::render()
{
	_enemyInfo->image->aniRender(CAMERAMANAGER->getWorldDC(), _enemyInfo->x, _enemyInfo->y-(_enemyInfo->image->getFrameHeight()/4), _enemyInfo->animation);
}

void Enemy::Beat()
{
	if (BEATMANAGER->getInterval())
	{
		_enemyInfo->beat++;
	}
}

void Enemy::Action()
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

	//x,y 중점에서 + 이미지 크기 x-이미지 절반 크기
}

void Enemy::EnemyCreate(float x, float y, float HP, float damage, const char* enemyName, const char* enemyAnimation)
{
	ZeroMemory(&_enemyInfo, sizeof(_enemyInfo));
	_enemyInfo = new EnemyInfo;
	_enemyInfo->direction = Direction::LEFT;
	_enemyInfo->state = enemyState::STATE_IDLE;
	_enemyInfo->idx = x*52;
	_enemyInfo->idy = y*52;
	_enemyInfo->HP = HP;
	_enemyInfo->damage = damage;
	_enemyInfo->image = IMAGEMANAGER->findImage(enemyName);
	_enemyInfo->animation = KEYANIMANAGER->findAnimation(enemyAnimation);
	_enemyInfo->rc = RectMake(_enemyInfo->idx, _enemyInfo->idy, 52, 52);

	_enemyInfo->x = (_enemyInfo->rc.left + _enemyInfo->rc.right) / 2;
	_enemyInfo->y = (_enemyInfo->rc.top + _enemyInfo->rc.bottom) / 2;

	_enemyInfo->discoveryRc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, 52 * 7, 52 * 7);
	_enemyInfo->animation->start();
}

void Enemy::EnemyCreate(float x, float y, float HP, float damage, const char* enemyName, const char* enemyAnimation, Direction direction)
{
	ZeroMemory(&_enemyInfo, sizeof(_enemyInfo));
	_enemyInfo = new EnemyInfo;
	_enemyInfo->direction = direction;
	_enemyInfo->state = enemyState::STATE_IDLE;
	_enemyInfo->x = x;
	_enemyInfo->y = y;
	_enemyInfo->HP = HP;
	_enemyInfo->damage = damage;
	_enemyInfo->image = IMAGEMANAGER->findImage(enemyName);
	_enemyInfo->animation = KEYANIMANAGER->findAnimation(enemyAnimation);
	_enemyInfo->rc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, 52, 52);
	_enemyInfo->discoveryRc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, 52 * 7, 52 * 7);
	_enemyInfo->animation->start();
}

float Enemy::LinearInterpolation(float value1, float value2, float amount)
{
	return float(value1 + ((float)(value2 - value1) * amount));
}
