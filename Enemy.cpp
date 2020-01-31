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
	_enemyInfo->Move = false;
	_enemyInfo->MoveSpeed = 10.4;
	_enemyInfo->parentDirection = _enemyInfo->direction;
	_enemyInfo->parentLight = _enemyInfo->Light;
	_enemyInfo->routeX = 0;
	_enemyInfo->routeY = 0;
	_enemyInfo->left = false;
	_enemyInfo->right = false;
	_enemyInfo->up = false;
	_enemyInfo->down = false;
	_enemyInfo->correction = false;
	//_collision = new Collision;

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
	if (_enemyInfo->parentDirection != _enemyInfo->direction)
	{
		AniChange();
		_enemyInfo->parentDirection = _enemyInfo->direction;
	}
	if (_enemyInfo->parentLight != _enemyInfo->Light)
	{
		AniChange();
		_enemyInfo->parentLight = _enemyInfo->Light;
	}
	
	if(!_enemyInfo->Attack)
		switch (_enemyInfo->direction)
		{
		case Direction::LEFT:
			if (!_enemyInfo->left)
			{
				moveAction();
				_enemyInfo->correction = false;
			}
			else
			{
				_enemyInfo->x = _enemyInfo->idx * 52+26;
				_enemyInfo->y = _enemyInfo->idy * 52+26;
			}
			break;
		case Direction::RIGHT:
			if (!_enemyInfo->right)
			{
				moveAction();
				_enemyInfo->correction = false;
			}
			else
			{
				_enemyInfo->x = _enemyInfo->idx * 52+26;
				_enemyInfo->y = _enemyInfo->idy * 52+26;
			}
			break;
		case Direction::UP:
			if (!_enemyInfo->up)
			{
				moveAction();
				_enemyInfo->correction = false;
			}
			else
			{
				_enemyInfo->x = _enemyInfo->idx * 52+26;
				_enemyInfo->y = _enemyInfo->idy * 52+26;
			}
			break;
		case Direction::DOWN:
			if (!_enemyInfo->down)
			{
				moveAction();
				_enemyInfo->correction = false;
			}
			else
			{
				_enemyInfo->x = _enemyInfo->idx * 52+26;
				_enemyInfo->y = _enemyInfo->idy * 52+26;
			}
			
			break;
		}
	
	//enemyMove();
	_enemyInfo->rc = RectMake(_enemyInfo->idx * 52, _enemyInfo->idy * 52, 52, 52);
	
}

void Enemy::render()
{
	_enemyInfo->Image->aniRender(CAMERAMANAGER->getWorldDC(), _enemyInfo->x, _enemyInfo->y - (_enemyInfo->Image->getFrameHeight() / 4), _enemyInfo->Animation);
	//Rectangle(CAMERAMANAGER->getWorldDC(), _enemyInfo->rc);
	if(_enemyInfo->Attack)
	_enemyInfo->attackImage->aniRender(CAMERAMANAGER->getWorldDC(), _playerInfo->x, _playerInfo->y, _enemyInfo->attackAnimation);
}

void Enemy::AniStart()
{
	if (_enemyInfo->aniChange)
	{
		_enemyInfo->Animation->start();
		_enemyInfo->aniChange = false;
	}
}

float Enemy::LinearInterpolation(float value1, float value2, float amount)
{
	return float(value1 + ((float)(value2 - value1) * amount));
}

void Enemy::Beat()
{
	if (BEATMANAGER->getBeating() && _enemyInfo->Beat)
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
	bool same;
	int x = _enemyInfo->idx + _playerInfo->idx;
	int y = _enemyInfo->idy + _playerInfo->idy;
	_enemyInfo->Attack = false;
	if(!_enemyInfo->Move)_enemyInfo->worldTimeCount = TIMEMANAGER->getWorldTime();

	if (_enemyInfo->idx - 1 == _playerInfo->idx && _enemyInfo->idy == _playerInfo->idy)
	{
		_enemyInfo->state = enemyState::STATE_ATTACK;
		_enemyInfo->AttackDirection = Direction::LEFT;
	}
	else if (_enemyInfo->idx + 1 == _playerInfo->idx && _enemyInfo->idy == _playerInfo->idy)
	{
		_enemyInfo->state = enemyState::STATE_ATTACK;
		_enemyInfo->AttackDirection = Direction::RIGHT;
	}
	else if (_enemyInfo->idx == _playerInfo->idx && _enemyInfo->idy - 1 == _playerInfo->idy)
	{
		_enemyInfo->state = enemyState::STATE_ATTACK;
		_enemyInfo->AttackDirection = Direction::UP;
	}
	else if (_enemyInfo->idx == _playerInfo->idx && _enemyInfo->idy + 1 == _playerInfo->idy)
	{
		_enemyInfo->state = enemyState::STATE_ATTACK;
		_enemyInfo->AttackDirection = Direction::DOWN;
	}
	//enemy와 플레어의 y축이 같다면(x축 이동)
	else if (_enemyInfo->idy == _playerInfo->idy)
	{
		//enemy가 플레이어의 오른쪽에 있다면 왼쪽으로 이동
		if (_enemyInfo->idx > _playerInfo->idx && !_enemyInfo->left)
		{
			_enemyInfo->direction = Direction::LEFT;
			_enemyInfo->idx -= 1;
			
			enemyAngle();
			}
		
		//enemy가 플레이어의 왼쪽에 있다면 오른쪽으로 이동
		else if (_enemyInfo->idx < _playerInfo->idx && !_enemyInfo->right)
		{
			_enemyInfo->direction = Direction::RIGHT;
			_enemyInfo->idx += 1;
			
			enemyAngle();
			
		}
	}
	//enemy와 플레이어의 x축이 같다면(y축 이동)
	else if (_enemyInfo->idx == _playerInfo->idx )
	{
		//enemy가 플레이어의 아래쪽에 있다면 위로 이동
		if (_enemyInfo->idy > _playerInfo->idy && !_enemyInfo->up)
		{
			_enemyInfo->direction = Direction::UP;
			_enemyInfo->idy -= 1;
			
			enemyAngle();
			
		}
		//enemy가 플레이어의 위쪽에 있다면 아래로 이동
		else if (_enemyInfo->idy < _playerInfo->idy && !_enemyInfo->down)
		{
			_enemyInfo->direction = Direction::DOWN;
			_enemyInfo->idy += 1;
			
			enemyAngle();
			
		}
	}
	//y축이 더 가까움(y축 이동)
	else if (x > y)
	{
		//enemy가 플레이어보다 밑에 있다면
		if (_enemyInfo->idy > _playerInfo->idy && !_enemyInfo->up)
		{
			_enemyInfo->direction = Direction::UP;
			_enemyInfo->idy -= 1;
			
			enemyAngle();
			
		}
		//enemy가 플레이어보다 위에 있다면
		else if (_enemyInfo->idy < _playerInfo->idy && !_enemyInfo->down)
		{
			_enemyInfo->direction = Direction::DOWN;
			_enemyInfo->idy += 1;
			
			enemyAngle();
			
			
		}

	}
	//x축이 더 가까움(x축 이동)
	else if (x < y)
	{
		if (_enemyInfo->idx > _playerInfo->idx && !_enemyInfo->left)
		{
			_enemyInfo->direction = Direction::LEFT;
			_enemyInfo->idx -= 1;
			
			enemyAngle();
			
		}
		else if (_enemyInfo->idx < _playerInfo->idx && !_enemyInfo->right)
		{
			_enemyInfo->direction = Direction::RIGHT;
			_enemyInfo->idx += 1;
			
			enemyAngle();
			
		}
	}
	//x y축의 거리가 같음(랜덤하게 x,y 둘중 하나 연산)
	else if (x == y)
	{
		//랜덤 숫자를 받아서 그 숫자가 1이면(x축 이동)
		if (RND->getInt(2) % 2 == 1)
		{
			if (_enemyInfo->idx > _playerInfo->idx)
			{
				_enemyInfo->direction = Direction::LEFT;
				_enemyInfo->idx -= 1;
				
				enemyAngle();
				
			}
			else if (_enemyInfo->idx < _playerInfo->idx)
			{
				_enemyInfo->direction = Direction::RIGHT;
				_enemyInfo->idx += 1;
				
				enemyAngle();
				
			}
		}
		//숫자가 0이면(y축 이동)
		else if (RND->getInt(2) % 2 == 0)
		{
			if (_enemyInfo->idy > _playerInfo->idy)
			{
				_enemyInfo->direction = Direction::UP;
				_enemyInfo->idy -= 1;
			
				enemyAngle();
				
			}
			else if (_enemyInfo->idy < _playerInfo->idy)
			{
				_enemyInfo->direction = Direction::DOWN;
				_enemyInfo->idy += 1;

				
				enemyAngle();
				
			}
		}
	}
	_enemyInfo->Move = true;
}

void Enemy::enemyAngle()
{
	switch (_enemyInfo->direction)
	{
	case Direction::LEFT:
		if (_enemyInfo->left)break;
		_enemyInfo->angle = getAngle(_enemyInfo->x, _enemyInfo->y, _enemyInfo->x - 52, _enemyInfo->y);
		break;
	case Direction::RIGHT:
		if (_enemyInfo->right)break;
		_enemyInfo->angle = getAngle(_enemyInfo->x, _enemyInfo->y, _enemyInfo->x + 52, _enemyInfo->y);
		
		break;
	case Direction::UP:
		if (_enemyInfo->up)break;
		_enemyInfo->angle = getAngle(_enemyInfo->x, _enemyInfo->y, _enemyInfo->x, _enemyInfo->y-52);
		
		break;
	case Direction::DOWN:
		if (_enemyInfo->down)break;
		_enemyInfo->angle = getAngle(_enemyInfo->x, _enemyInfo->y, _enemyInfo->x, _enemyInfo->y+52);
		
		break;
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
	switch (_enemyInfo->AttackDirection)
	{
	case Direction::LEFT:
		if (!(_enemyInfo->idx - 1 == _playerInfo->idx && _enemyInfo->idy == _playerInfo->idy))
		{
			_enemyInfo->Attack = false;
			break;
		}
		_enemyInfo->attackImage = IMAGEMANAGER->findImage("Enemy_Attack_Left");
		_enemyInfo->attackAnimation = KEYANIMANAGER->findAnimation("Enemy_Attack_LEFT_Ani");
		
		_enemyInfo->Attack = true;
		break;
	case Direction::RIGHT:
		if (!(_enemyInfo->idx + 1 == _playerInfo->idx && _enemyInfo->idy == _playerInfo->idy))
		{
			_enemyInfo->Attack = false;
			break;
		}
		_enemyInfo->attackImage = IMAGEMANAGER->findImage("Enemy_Attack_Right");
		_enemyInfo->attackAnimation = KEYANIMANAGER->findAnimation("Enemy_Attack_RIGHT_Ani");
		_enemyInfo->Attack = true;
		break;
	case Direction::UP:
		if (!(_enemyInfo->idx == _playerInfo->idx && _enemyInfo->idy - 1 == _playerInfo->idy))
		{
			_enemyInfo->Attack = false;
			break;
		}
		_enemyInfo->attackImage = IMAGEMANAGER->findImage("Enemy_Attack_Up");
		_enemyInfo->attackAnimation = KEYANIMANAGER->findAnimation("Enemy_Attack_UP_Ani");
		_enemyInfo->Attack = true;
		break;
	case Direction::DOWN:
		if (!(_enemyInfo->idx == _playerInfo->idx && _enemyInfo->idy + 1 == _playerInfo->idy))
		{
			_enemyInfo->Attack = false;
			break;
		}
		_enemyInfo->attackImage = IMAGEMANAGER->findImage("Enemy_Attack_Down");
		_enemyInfo->attackAnimation = KEYANIMANAGER->findAnimation("Enemy_Attack_DOWN_Ani");
		_enemyInfo->Attack = true;
		break;
	}
	if (_enemyInfo->Attack)
	{
		_enemyInfo->attackAnimation->start();
	}
	else { _enemyInfo->attackAnimation->stop(); }
	//_enemyInfo->attackAnimation->start();
	_enemyInfo->state = enemyState::STATE_MOVE;
	//_enemyInfo->Attack = false;
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
	_enemyInfo->attackImage = IMAGEMANAGER->findImage("Enemy_Attack_Left");
	_enemyInfo->attackAnimation = KEYANIMANAGER->findAnimation("Enemy_Attack_LEFT_Ani");
	_enemyInfo->rc = RectMake(_enemyInfo->idx * 52, _enemyInfo->idy * 52, 52, 52);

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
	_enemyInfo->attackImage = IMAGEMANAGER->findImage("Enemy_Attack_Left");
	_enemyInfo->attackAnimation = KEYANIMANAGER->findAnimation("Enemy_Attack_LEFT_Ani");
	_enemyInfo->rc = RectMake(_enemyInfo->idx * 52, _enemyInfo->idy * 52, 52, 52);

	_enemyInfo->x = (_enemyInfo->rc.left + _enemyInfo->rc.right) / 2;
	_enemyInfo->y = (_enemyInfo->rc.top + _enemyInfo->rc.bottom) / 2;

	_enemyInfo->discoveryRc = RectMakeCenter(_enemyInfo->x, _enemyInfo->y, 52 * 7, 52 * 7);
	_enemyInfo->Animation->start();
}

void Enemy::moveAction()
{
	if (!_enemyInfo->Move) return;

	float elapsedTime = TIMEMANAGER->getElapsedTime();

	//200정도의 거리를 2초에 걸쳐서 도달해야한다면 속도값을 구해줌
	float moveSpeed = (elapsedTime / _time) * 52;

	
		//이미지를 도착지점까지 각도와 속도를 맞춰서 원하는 시간에 도달케 한다
		_enemyInfo->x = _enemyInfo->x + cosf(_enemyInfo->angle) * moveSpeed;
		_enemyInfo->y = _enemyInfo->y+ (-sinf(_enemyInfo->angle) * moveSpeed);

		// 만약 월드 시간이 도달하면 
		if (_time + _enemyInfo->worldTimeCount <= TIMEMANAGER->getWorldTime())
		{
			_enemyInfo->worldTimeCount = TIMEMANAGER->getWorldTime();
			// 위치를 고정시키고 MOVE BOOL값을 false로
			_enemyInfo->x = _enemyInfo->idx * 52 + (52 / 2);
			_enemyInfo->y = _enemyInfo->idy * 52 + (52 / 2);

			_enemyInfo->Move = false;	    // 선형 보간 
			
			return;
		}
	
}
