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
	_enemyInfo->Attack = false;

	//_enemyInfo->attackImage = IMAGEMANAGER->findImage("Enemy_Attack_LEFT");
	//_enemyInfo->attackAnimation = KEYANIMANAGER->findAnimation("Enemy_Attack_LEFT_Ani");

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
	Die();
	_enemyInfo->rc = RectMake(_enemyInfo->idx*52, _enemyInfo->idy*52, 52, 52);
}

void Enemy::render()
{
	_enemyInfo->Image->aniRender(CAMERAMANAGER->getWorldDC(), _enemyInfo->x, _enemyInfo->y - (_enemyInfo->Image->getFrameHeight() / 4), _enemyInfo->Animation);
	Rectangle(CAMERAMANAGER->getWorldDC(), _enemyInfo->rc);
	/*if(_enemyInfo->Attack)
	_enemyInfo->attackImage->aniRender(CAMERAMANAGER->getWorldDC(), _enemyInfo->x, _enemyInfo->y, _enemyInfo->attackAnimation);*/
}

void Enemy::AniStart()
{
	if (_enemyInfo->aniChange)
	{
		_enemyInfo->Animation->start();
		_enemyInfo->aniChange = false;
	}
}

void Enemy::Beat()
{
	if (BEATMANAGER->getBeating()&&_enemyInfo->Beat)
	{
		_enemyInfo->beatCount++;
		_enemyInfo->Beat = false;
	}
	if (!BEATMANAGER->getBeating())_enemyInfo->Beat = true;
}

void Enemy::Action()
{
}

void Enemy::Idle()
{
}

void Enemy::Move()
{
	if (_enemyInfo->idx + 1 == _playerInfo->idx && _enemyInfo->idy == _playerInfo->idy)
	{
		//오른쪽 공격
		_enemyInfo->state = enemyState::STATE_ATTACK;
		_enemyInfo->AttackDirection = Direction::RIGHT;
	}
	else if (_enemyInfo->idx - 1 == _playerInfo->idx && _enemyInfo->idy == _playerInfo->idy)
	{
		//왼쪽 공격
		_enemyInfo->state = enemyState::STATE_ATTACK;
		_enemyInfo->AttackDirection = Direction::LEFT;
	}
	else if (_enemyInfo->idx == _playerInfo->idx && _enemyInfo->idy - 1 == _playerInfo->idy)
	{
		//위쪽 공격
		_enemyInfo->state == enemyState::STATE_ATTACK;
		_enemyInfo->AttackDirection = Direction::UP;
	}
	else if (_enemyInfo->idx == _playerInfo->idx && _enemyInfo->idy + 1 == _playerInfo->idy)
	{
		//아래쪽 공격
		_enemyInfo->state = enemyState::STATE_ATTACK;
		_enemyInfo->AttackDirection = Direction::DOWN;
	}
	
	else if (_enemyInfo->idx != _playerInfo->idx)
	{
		if (_enemyInfo->idx > _playerInfo->idx && !_enemyInfo->left)
		{
			_enemyInfo->idx -= 1;
			_enemyInfo->x -= 52;
		}
		else if (_enemyInfo->idx < _playerInfo->idx && !_enemyInfo->right)
		{
			_enemyInfo->idx += 1;
			_enemyInfo->x += 52;
		}
	}
	else if (_enemyInfo->idx == _playerInfo->idx)
	{
		if (_enemyInfo->idy > _playerInfo->idy && !_enemyInfo->up)
		{
			_enemyInfo->idy -= 1;
			_enemyInfo->y -= 52;
		}
		else if (_enemyInfo->idy < _playerInfo->idy && !_enemyInfo->down)
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
	/*switch (_enemyInfo->AttackDirection)
	{
	case Direction::LEFT:
		_enemyInfo->attackImage = IMAGEMANAGER->findImage("Enemy_Attack_LEFT");
		_enemyInfo->attackAnimation = KEYANIMANAGER->findAnimation("Enemy_Attack_LEFT_Ani");
		
		_enemyInfo->Attack = true;
		break;
	case Direction::RIGHT:
		_enemyInfo->attackImage = IMAGEMANAGER->findImage("Enemy_Attack_RIGHT");
		_enemyInfo->attackAnimation = KEYANIMANAGER->findAnimation("Enemy_Attack_RIGHT_Ani");
		_enemyInfo->Attack = true;
		break;
	case Direction::UP:
		_enemyInfo->attackImage = IMAGEMANAGER->findImage("Enemy_Attack_UP");
		_enemyInfo->attackAnimation = KEYANIMANAGER->findAnimation("Enemy_Attack_UP_Ani");
		_enemyInfo->Attack = true;
		break;
	case Direction::DOWN:
		_enemyInfo->attackImage = IMAGEMANAGER->findImage("Enemy_Attack_DOWN");
		_enemyInfo->attackAnimation = KEYANIMANAGER->findAnimation("Enemy_Attack_DOWN_Ani");
		_enemyInfo->Attack = true;
		break;
	}*/
	//_enemyInfo->attackAnimation->start();
	_enemyInfo->state = enemyState::STATE_MOVE;
	_enemyInfo->Attack = false;
}

void Enemy::Die()
{
	if (_enemyInfo->HP <= 0)
	{
		_enemyInfo->state = enemyState::STATE_DIE;
	}
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
	_enemyInfo->Image = IMAGEMANAGER->findImage(enemyName);
	_enemyInfo->Animation = KEYANIMANAGER->findAnimation(enemyAnimation);
	_enemyInfo->rc = RectMake(_enemyInfo->idx*52, _enemyInfo->idy*52, 52, 52);

	_enemyInfo->x = (_enemyInfo->rc.left + _enemyInfo->rc.right) / 2;
	_enemyInfo->y = (_enemyInfo->rc.top + _enemyInfo->rc.bottom) / 2;

	_enemyInfo->discoveryRc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, 52 * 7, 52 * 7);
	_enemyInfo->Animation->start();
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
	_enemyInfo->Image = IMAGEMANAGER->findImage(enemyName);
	_enemyInfo->Animation = KEYANIMANAGER->findAnimation(enemyAnimation);
	_enemyInfo->rc = RectMake(_enemyInfo->idx*52, _enemyInfo->idy*52, 52, 52);

	_enemyInfo->x = (_enemyInfo->rc.left + _enemyInfo->rc.right) / 2;
	_enemyInfo->y = (_enemyInfo->rc.top + _enemyInfo->rc.bottom) / 2;

	_enemyInfo->discoveryRc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, 52 * 7, 52 * 7);
	_enemyInfo->Animation->start();
}
