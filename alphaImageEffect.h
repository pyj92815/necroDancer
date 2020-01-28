#pragma once
#include "effect.h"

class alphaImageEffect : public effect
{
	EFFECTTYPE _type;
	int _alphaValue = 0;
	int _speed;
	float _time;
	bool _isStop;
	
	// «¡∑π¿” 
	int _count,_currentFrameX,_currentFrameY;

public:
	alphaImageEffect();
	~alphaImageEffect();
	virtual HRESULT init(const char* imageName, float x, float y, int speed, EFFECTTYPE type);
	virtual HRESULT init(const char* imageName, float x, float y, int currentFrameX, int currentFrameY, EFFECTTYPE type);
	void release();
	void update();
	void render();
	void render(HDC hdc);
};

