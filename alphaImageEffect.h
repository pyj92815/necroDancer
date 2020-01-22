#pragma once
#include "effect.h"

class alphaImageEffect : public effect
{
	int _alphaValue = 0;
	bool _moveStart;
public:
	alphaImageEffect();
	~alphaImageEffect();

	virtual HRESULT init();
	void alphaEffectStart(const char* imageName,float x, float y);
	void release();
	void update();
	void render();
	void render(HDC hdc);
};

