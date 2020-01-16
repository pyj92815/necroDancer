#include "stdafx.h"
#include "jump.h"


jump::jump()
{
}


jump::~jump()
{
}

HRESULT jump::init()
{
	_isJumping = _jumpPower = _gravity = 0;

	return S_OK;
}

void jump::release()
{
}

void jump::update()
{
	if (!_isJumping) return;

	*_y -= _jumpPower;
	_jumpPower -= _gravity;

	if (_startY < *_y)
	{
		_isJumping = false;
		*_y = _startY;
	}
}

void jump::render()
{
}

void jump::jumping(float* x, float* y, float jumpPower, float gravity)
{
	//점프중이면 리턴 이말은 점프중이면 실행하지마렁
	if (_isJumping) return;

	_isJumping = true;

	_x = x;
	_y = y;

	_startX = *x;
	_startY = *y;

	//call by value
	//call by reference

	_gravity = gravity;
	_jumpPower = jumpPower;

}
