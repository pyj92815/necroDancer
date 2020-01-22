#include "stdafx.h"
#include "alphaImageEffect.h"

alphaImageEffect::alphaImageEffect()
{
}

alphaImageEffect::~alphaImageEffect()
{
}

HRESULT alphaImageEffect::init()
{
	_alphaValue = 255;
	_moveStart = false;
	return S_OK;
}

void alphaImageEffect::alphaEffectStart(const char* imageName,float x,float y)
{
	_effectImage = IMAGEMANAGER->findImage(imageName);
	_x = x;
	_y = y;
	_isRunning = true;
	_alphaValue = 255;
}


void alphaImageEffect::release()
{
	_effectImage = NULL;
	SAFE_DELETE(_effectAnimation);
}

void alphaImageEffect::update()
{
	if (_isRunning)
	{
		_y -= 10 * TIMEMANAGER->getElapsedTime();
		_alphaValue -= 10;
		if (_alphaValue < 10)
		{
			_isRunning = false;
			this->release();
		}
	}
}

void alphaImageEffect::render()
{
	_effectImage->render(getMemDC(), _x, _y);
}
void alphaImageEffect::render(HDC hdc)
{
	if(_isRunning)	_effectImage->alphaRender(hdc, _x, _y, _alphaValue);
}
