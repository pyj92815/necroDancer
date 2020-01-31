#pragma once
#include "singletonBase.h"
#include "timer.h"

class timeManager : public singletonBase <timeManager>
{
private:
	timer* _timer;

public:
	timeManager();
	~timeManager();

	HRESULT init();
	void release();
	void update(float lockFPS = 0.0f);
	void render(HDC hdc);

	//Delta타임
	inline float getElapsedTime() const { return _timer->getElapsedTime(); }

	//World타임
	inline float getWorldTime() const { return _timer->getWorldTime(); }

	//원하는 지점에서부터 세기
	inline float getCountTime() { return _timer->getCountTime(); }
	inline void setCountTime(float countTime) { *(_timer->getCountTimePt()) = countTime; }
	
	inline void setCountTimeResetSwitch(bool resetSwitch) { *(_timer->getCountTimeResetSwitchPt()) = resetSwitch; }
	inline void setCountTimeSwitch(bool ONOff_Switch) { *(_timer->getCountTimeSwitchPt()) = ONOff_Switch; }

	inline float getDaeHunWorldTime() const { return _timer->getDaeHunWorldTime();}
};

