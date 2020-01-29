#include "stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init()
{
	ZeroMemory(&_playerInfo, sizeof(_playerInfo));
	_playerInfo = new playerInfo;

	_enemyInfo->Beat = true;
	_enemyInfo->aniChange = true;
	_enemyInfo->Light = true;
	_enemyInfo->beatCount = 0;
	return S_OK;
}

void Enemy::relase()
{
}

void Enemy::update()
{
	Beat();
	AniStart();
	Action();
}

void Enemy::render()
{
	_enemyInfo->image->aniRender(CAMERAMANAGER->getWorldDC(), _enemyInfo->x, _enemyInfo->y - (_enemyInfo->image->getFrameHeight() / 4), _enemyInfo->animation);
}

void Enemy::AniStart()
{
	if (_enemyInfo->aniChange)
	{
		_enemyInfo->animation->start();
		_enemyInfo->aniChange = false;
	}
}

void Enemy::Beat()
{
	//if (BEATMANAGER->getInterval() && !_deathMetal->getBoss_Beat())
	//{
	//	_deathMetal->setBoss_Beat(true);		// 비트를 받았다면 true로 바꿔준다. (여러번 들어오는것을 방지)
	//	_deathMetal->setBoss_Move_Count();		// 무브 카운트를 1 감소한다.
	//}

	//// 비트의 값이 0이 됐을때 false의 값으로 바꿔준다.
	//if (!BEATMANAGER->getInterval()) _deathMetal->setBoss_Beat(false);

	//// 데스메탈의 무브 카운트가 0이 된다면 이동을 시작 한다.
	//if (_deathMetal->getBoss_Move_Count() == 0)
	//{
	//	// 플레이어와 데스메탈의 정보를 이용하여 이동 할 방향을 정한다.
	//	findPlayer(_player, _deathMetal, _ui);
	//}
	if (BEATMANAGER->getBeating()&&_enemyInfo->Beat)
	{
		_enemyInfo->beatCount++;
		_enemyInfo->Beat = false;
	}
	if (!BEATMANAGER->getBeating())_enemyInfo->Beat = true;
	/*if (BEATMANAGER->getInterval()&&_enemyInfo->Beat)
	{
		_enemyInfo->beatCount++;
		_enemyInfo->Beat = false;
	}
	if (!BEATMANAGER->getInterval())_enemyInfo->Beat = true;*/
	//cout << _enemyInfo->beatCount << endl;
}

void Enemy::Action()
{
}

void Enemy::Move()
{
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
	else if (_enemyInfo->idx == _playerInfo->idx)
	{
		if (_enemyInfo->idy > _playerInfo->idy)
		{
			_enemyInfo->idy -= 1;
			_enemyInfo->y -= 52;
		}
		else if (_enemyInfo->idy < _playerInfo->idy)
		{
			_enemyInfo->idy += 1;
			_enemyInfo->y += 52;
		}
	}
}

void Enemy::HalfMove()
{
}

void Enemy::AniChange()
{
}

void Enemy::Attack()
{
	//switch (_enemyInfo->direction)
	//{
	//case Direction::UP:
	//	//위로 절반 이동 후 다시 제자리로 + 해당 방향으로 공격 모션
	//	_enemyInfo->state = enemyState::STATE_MOVE;
	//	break;
	//case Direction::DOWN:
	//	//아래로 절반 이동 후 다시 제자리로 + 해당 방향으로 공격 모션
	//	_enemyInfo->state = enemyState::STATE_MOVE;
	//	break;
	//}
}


void Enemy::EnemyCreate(float x, float y, float HP, float damage)
{
	ZeroMemory(&_enemyInfo, sizeof(_enemyInfo));
	_enemyInfo = new EnemyInfo;
	_enemyInfo->direction = Direction::LEFT;
	_enemyInfo->state = enemyState::STATE_MOVE;
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
	_enemyInfo->state = enemyState::STATE_MOVE;
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
	_enemyInfo->state = enemyState::STATE_MOVE;
	_enemyInfo->idx = x;
	_enemyInfo->idy = y;
	_enemyInfo->HP = HP;
	_enemyInfo->damage = damage;
	_enemyInfo->image = IMAGEMANAGER->findImage(enemyName);
	_enemyInfo->animation = KEYANIMANAGER->findAnimation(enemyAnimation);
	_enemyInfo->rc = RectMake(_enemyInfo->idx*52, _enemyInfo->idy*52, 52, 52);

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
	_enemyInfo->state = enemyState::STATE_MOVE;
	_enemyInfo->idx = x;
	_enemyInfo->idy = y;
	_enemyInfo->HP = HP;
	_enemyInfo->damage = damage;
	_enemyInfo->image = IMAGEMANAGER->findImage(enemyName);
	_enemyInfo->animation = KEYANIMANAGER->findAnimation(enemyAnimation);
	_enemyInfo->rc = RectMake(_enemyInfo->idx*52, _enemyInfo->idy*52, 52, 52);

	_enemyInfo->x = (_enemyInfo->rc.left + _enemyInfo->rc.right) / 2;
	_enemyInfo->y = (_enemyInfo->rc.top + _enemyInfo->rc.bottom) / 2;

	_enemyInfo->discoveryRc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, 52 * 7, 52 * 7);
	_enemyInfo->animation->start();
}
