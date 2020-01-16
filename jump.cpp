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


	// 만약 UP 키를 누르면 
	if (_isUpJumping) 
	{
		*_y -= _jumpPower;

		if (_startY > * _y)
		{
			_isJumping = false;
			_isUpJumping = false;
		}
	}
	else // 이외의 키를 누르면 
	{
		*_y -= _jumpPower;
		_jumpPower -= _gravity;
		if (_startY < *_y)
		{
			_isJumping = false;
			*_y = _startY;
		}
	}

}

void jump::render()
{
}

void jump::jumping(float* x, float* y, float jumpPower, float gravity,bool upJump)
{
	//점프중이면 리턴 이말은 점프중이면 실행하지마렁
	if (_isJumping) return;
	_isUpJumping = upJump;
	_isJumping = true;

	_x = x;
	_y = y;

	_startX = *x;

	// UP키를 누르면 
	if (_isUpJumping)
	{
		_startY = *y-52; // 위 타일의 중점 y 좌표 
	}
	else // 이외의 키를 누르면 
	{
		_startY = *y;
	}

	//call by value
	//call by reference

	_gravity = gravity;
	_jumpPower = jumpPower;

}
