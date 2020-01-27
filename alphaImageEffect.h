#pragma once
#include "effect.h"

class alphaImageEffect : public effect
{
	int _alphaValue = 0;
	int _speed;
	bool _isStop;
public:
	alphaImageEffect();
	~alphaImageEffect();

	virtual HRESULT init(const char* imageName, float x, float y,int speed,bool value = false);
	void release();
	void update();
	void render();
	void render(HDC hdc);
};

