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
	//	_deathMetal->setBoss_Beat(true);		// ��Ʈ�� �޾Ҵٸ� true�� �ٲ��ش�. (������ �����°��� ����)
	//	_deathMetal->setBoss_Move_Count();		// ���� ī��Ʈ�� 1 �����Ѵ�.
	//}

	//// ��Ʈ�� ���� 0�� ������ false�� ������ �ٲ��ش�.
	//if (!BEATMANAGER->getInterval()) _deathMetal->setBoss_Beat(false);

	//// ������Ż�� ���� ī��Ʈ�� 0�� �ȴٸ� �̵��� ���� �Ѵ�.
	//if (_deathMetal->getBoss_Move_Count() == 0)
	//{
	//	// �÷��̾�� ������Ż�� ������ �̿��Ͽ� �̵� �� ������ ���Ѵ�.
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
	//	//���� ���� �̵� �� �ٽ� ���ڸ��� + �ش� �������� ���� ���
	//	_enemyInfo->state = enemyState::STATE_MOVE;
	//	break;
	//case Direction::DOWN:
	//	//�Ʒ��� ���� �̵� �� �ٽ� ���ڸ��� + �ش� �������� ���� ���
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

	//x,y �������� + �̹��� ũ�� x-�̹��� ���� ũ��
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
