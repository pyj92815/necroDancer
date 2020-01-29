#include "stdafx.h"
#include "alphaImageEffect.h"
#include "effect.h"

alphaImageEffect::alphaImageEffect()
{
}

alphaImageEffect::~alphaImageEffect()
{
}

HRESULT alphaImageEffect::init(const char* imageName, float x, float y, int speed, EFFECTTYPE type)
{
	_effectImage = IMAGEMANAGER->findImage(imageName);	// 이미지
	_isRunning = true;	// 렌더링 BOOL값 

	_x = x;
	_y = y;

	_type = type;			//EFFECT의 타입 

	_alphaValue = 255;
	_speed = speed;			// alpha 

	_time = TIMEMANAGER->getWorldTime();

	_count = 0;

	return S_OK;
}

HRESULT alphaImageEffect::init(const char* imageName, float x, float y, int currentFrameX, int currentFrameY, EFFECTTYPE type)
{
	_effectImage = IMAGEMANAGER->findImage(imageName);	// 이미지
	_isRunning = true;	// 렌더링 BOOL값 

	_x = x;
	_y = y;

	_type = type;			//EFFECT의 타입 

	_time = TIMEMANAGER->getWorldTime();

	_count = 0;
	_currentFrameX = currentFrameX;
	_currentFrameY = currentFrameY;
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
		switch (_type)
		{
		case TIMESLOW:
			if (_time + 0.25f <= TIMEMANAGER->getWorldTime())
			{
				_isRunning = false;
				this->release();
			}
			break;
		case SLOW:
			_y -= 20 * TIMEMANAGER->getElapsedTime();

			_alphaValue -= _speed;
			if (_alphaValue < 10)
			{
				_isRunning = false;
				this->release();
			}
			break;
		case STOP:
			_alphaValue -= _speed;
			if (_alphaValue < 10)
			{
				_isRunning = false;
				this->release();
			}
			break;
		case FRAMEIMAGE:
			_count++;
			if (_count > 2)
			{
				_currentFrameX++;
				_effectImage->setFrameX(_currentFrameX);
				if (_currentFrameX > _effectImage->getMaxFrameX())
				{
					_isRunning = false;
					this->release();
				}
				_count = 0;
			}
			break;
		default:
			break;
		}

	}
}

void alphaImageEffect::render()
{
	_effectImage->frameRender(CAMERAMANAGER->getWorldDC(), _x, _y);
}

void alphaImageEffect::render(HDC hdc)
{
	if (_isRunning)
	{
		switch (_type)
		{
		case FRAMEIMAGE:
			_effectImage->frameRender(hdc, _x, _y,_currentFrameX,_currentFrameY);
		break;
		default:
			_effectImage->alphaRender(hdc, _x, _y, _alphaValue);
		break;
		}
	}
}
