#pragma once
#include "gameNode.h"

class animation;

class effect : public gameNode
{
protected:
	int			_x;
	int			_y;

	image*		  _effectImage;
	animation* _effectAnimation;
	BOOL		_isRunning;
	BOOL	    _last;
	float		_elapsedTime;

public:
	effect();
	~effect();

	virtual HRESULT init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime);
	virtual HRESULT init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime, bool last = false);
	virtual HRESULT init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime, float x, float y, bool last = false);

	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(HDC hdc);
	void startEffect(int x, int y);
	void startEffect(float x, float y);
	virtual void killEffect();

	BOOL getIsRunning() { return _isRunning; }
	BOOL getIsLast() { return _last; }
};

