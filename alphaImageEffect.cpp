#include "stdafx.h"
#include "alphaImageEffect.h"

alphaImageEffect::alphaImageEffect()
{
}

alphaImageEffect::~alphaImageEffect()
{
}

HRESULT alphaImageEffect::init(const char* imageName, float x, float y)
{
	_alphaValue = 255;
	_x = x;
	_y = y;
	_effectImage = IMAGEMANAGER->findImage(imageName);
	_isRunning = true;
	return S_OK;
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
