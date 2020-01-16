#include "stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init()
{
	//_animation->start();
	//_image = IMAGEMANAGER->findImage("Enemy_bat");
	_image= IMAGEMANAGER->addFrameImage("Enemy_bat", "./image./Enemy/bat.bmp", 96, 48, 4, 2, true, RGB(255, 0, 255));
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
	//IMAGEMANAGER->frameRender("Enemy_bat",hdc , WINSIZEX / 2, WINSIZEY / 2, 1, 0);
	_image->frameRender(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, 1, 0);
	//_image->aniRender(getMemDC(), WINSIZEX / 2+10, WINSIZEY / 2, _animation);
}

