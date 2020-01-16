#include "stdafx.h"
#include "player.h"

player::player()
{
}

player::~player()
{
}

HRESULT player::init(int idx, int idy, int tileSizeX, int tileSizeY)
{
	// �̹��� 
	_head.image = IMAGEMANAGER->addFrameImage("player1_heads", "./image/player/player1_heads.bmp", 192, 48, 8, 2, true, RGB(255, 0, 255));
	_body.image = IMAGEMANAGER->addFrameImage("player1_armor_body_xmas", "./image/player/player1_armor_body_xmas.bmp", 192, 120, 8, 5, true, RGB(255, 0, 255));

	// �÷��̾� ����
	_head.state = PLAYERSTATE_RIGHT;
	_body.state = _head.state;

	//������ 
	int headRight[] = {0,1,2,3,4,5,6,7};
	KEYANIMANAGER->addArrayFrameAnimation("headRight", "player1_heads", headRight, 8, 10,true);

	int bodyRight[] = {0,1,2,3};
	KEYANIMANAGER->addArrayFrameAnimation("bodyRight", "player1_armor_body_xmas", bodyRight, 4, 10, true);
	// ���� 
	int headLeft[] = {15,14,13,12,11,10,9,8};
	KEYANIMANAGER->addArrayFrameAnimation("headLeft", "player1_heads", headLeft, 8, 10, true);

	int bodyLeft[] = {7,6,5,4};
	KEYANIMANAGER->addArrayFrameAnimation("bodyLeft", "player1_armor_body_xmas", bodyLeft, 4, 10, true);
	
	//�ִϸ��̼� �ʱ�ȭ 
	_head.ani = KEYANIMANAGER->findAnimation("headRight");
	_body.ani = KEYANIMANAGER->findAnimation("bodyRight");

	//�÷��̾��� ��ġ index��
	_body.idx = _head.idx = idx;
	_body.idy = _head.idy = idy;

	//�÷��̾��� �ʱⰪ 
	_body.x = _body.idx * tileSizeX + (tileSizeX/2);
	_body.y = _body.idy * tileSizeY + (tileSizeY/2);

	_distance = tileSizeY;			// Ÿ���� distance 

	_head.x = _body.x;
	_head.y = _body.y;		// �̹��� ũ�� ����� ���� �ؾ��� 

	_head.rc = RectMakeCenter(_head.x, _head.y, _head.image->getFrameWidth(), _head.image->getFrameHeight());
	_body.rc = RectMakeCenter(_body.x, _body.y, _body.image->getFrameWidth(), _body.image->getFrameHeight());

	//�ִϸ��̼� ���� 
	_head.ani->start();
	_body.ani->start();

	//���� ���� 
	_action = new action;
	_action->init();
	_isMoving = false;
	_time = 0.1;			 // �����̴� �ð� 
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	KEYANIMANAGER->update();
	
	keyControl();
	playerMove();
}

void player::render()
{
	//Rectangle(getMemDC(), _body.rc);
	//Rectangle(getMemDC(), _head.rc);
	_body.image->aniRender(getMemDC(), _body.x, _body.y, _body.ani);
	_head.image->aniRender(getMemDC(), _head.x, _head.y, _head.ani);
}

void player::playerMove()
{
	if (!_isMoving) return;

	float elapsedTime = TIMEMANAGER->getElapsedTime();

	//200������ �Ÿ��� 2�ʿ� ���ļ� �����ؾ��Ѵٸ� �ӵ����� ������
	float moveSpeed = (elapsedTime / _time) * 26;

	//�̹����� ������������ ������ �ӵ��� ���缭 ���ϴ� �ð��� ������ �Ѵ�
	_head.x = _head.x + cosf(_angle) * moveSpeed;
	_body.x = _body.x + cosf(_angle) * moveSpeed;
	_head.y = _head.y + (-sinf(_angle) * moveSpeed);
	_body.y = _body.y + (-sinf(_angle) * moveSpeed);


	float time = TIMEMANAGER->getElapsedTime();

	if (_time + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();

		_head.x = _head.idx * _distance + (_distance / 2);
		_head.y = _head.idy * _distance + (_distance / 2);
		_body.x = _body.idx * _distance + (_distance / 2);
		_body.y = _body.idy * _distance + (_distance / 2);
		_isMoving = false;
	}
}

void player::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_head.idy--;
		_body.idy--;

		_angle = getAngle(_head.x, _head.y, _head.x, _head.y - _distance);
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_isMoving = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_head.idy++;
		_body.idy++;

		_angle = getAngle(_head.x, _head.y, _head.x, _head.y + _distance);
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_isMoving = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_head.ani = KEYANIMANAGER->findAnimation("headLeft");
		_body.ani = KEYANIMANAGER->findAnimation("bodyLeft");
		_head.ani->start();
		_body.ani->start();
		_head.idx--;
		_body.idx--;

		_angle = getAngle(_head.x, _head.y, _head.x-_distance, _head.y);
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_isMoving = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_head.ani = KEYANIMANAGER->findAnimation("headRight");
		_body.ani = KEYANIMANAGER->findAnimation("bodyRight");
		_head.ani->start();
		_body.ani->start();
		_head.idx++;
		_body.idx++;

		_angle = getAngle(_head.x, _head.y, _head.x + _distance, _head.y);
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_isMoving = true;
	}

}
