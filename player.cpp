#include "stdafx.h"
#include "player.h"

player::player()
{
}

player::~player()
{
}

HRESULT player::init()
{
	// 이미지 
	_head.image = IMAGEMANAGER->addFrameImage("player1_heads", "./image/player/player1_heads.bmp", 192, 48, 8, 2, true, RGB(255, 0, 255));
	_body.image = IMAGEMANAGER->addFrameImage("player1_armor_body_xmas", "./image/player/player1_armor_body_xmas.bmp", 192, 120, 8, 5, true, RGB(255, 0, 255));

	// 플레이어 상태
	_head.state = PLAYERSTATE_RIGHT;
	_body.state = _head.state;

	//오른쪽 
	int headRight[] = {0,1,2,3,4,5,6,7};
	KEYANIMANAGER->addArrayFrameAnimation("headRight", "player1_heads", headRight, 8, 10,true);

	int bodyRight[] = {0,1,2,3};
	KEYANIMANAGER->addArrayFrameAnimation("bodyRight", "player1_armor_body_xmas", bodyRight, 4, 10, true);
	// 왼쪽 
	int headLeft[] = {15,14,13,12,11,10,9,8};
	KEYANIMANAGER->addArrayFrameAnimation("headLeft", "player1_heads", headLeft, 8, 10, true);

	int bodyLeft[] = {7,6,5,4};
	KEYANIMANAGER->addArrayFrameAnimation("bodyLeft", "player1_armor_body_xmas", bodyLeft, 4, 10, true);


	_head.ani = KEYANIMANAGER->findAnimation("headRight");
	_body.ani = KEYANIMANAGER->findAnimation("bodyRight");

	_body.x = WINSIZEX / 2;
	_body.y = WINSIZEY / 2;

	_head.x = _body.x;
	_head.y = _body.y;		// 이미지 크기 변경시 수정 해야함 

	_head.rc = RectMakeCenter(_head.x, _head.y, _head.image->getFrameWidth(), _head.image->getFrameHeight());
	_body.rc = RectMakeCenter(_body.x, _body.y, _body.image->getFrameWidth(), _body.image->getFrameHeight());

	_head.ani->start();
	_body.ani->start();
	return S_OK;
}

void player::release()
{
}

void player::update()
{
	KEYANIMANAGER->update();
	keyControl();

}

void player::render()
{
	//Rectangle(getMemDC(), _body.rc);
	//Rectangle(getMemDC(), _head.rc);
	_body.image->aniRender(getMemDC(), _body.x, _body.y, _body.ani);
	_head.image->aniRender(getMemDC(), _head.x, _head.y, _head.ani);
}

void player::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{

	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{

	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_head.ani = KEYANIMANAGER->findAnimation("headLeft");
		_body.ani = KEYANIMANAGER->findAnimation("bodyLeft");
		_head.ani->start();
		_body.ani->start();

	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_head.ani = KEYANIMANAGER->findAnimation("headRight");
		_body.ani = KEYANIMANAGER->findAnimation("bodyRight");
		_head.ani->start();
		_body.ani->start();
	}

}

void player::setAnimation()
{
	switch (_body.state)
	{
	case PLAYERSTATE_LEFTSTOP:
		break;
	case PLAYERSTATE_RIGHTSTOP:
		break;
	case PLAYERSTATE_UP:
		break;
	case PLAYERSTATE_DOWN:
		break;
	case PLAYERSTATE_RIGHT:
		break;
	case PLAYERSTATE_LEFT:
		break;
	}
}
