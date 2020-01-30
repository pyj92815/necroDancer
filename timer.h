#pragma once

class timer
{
private:
	float _timeScale;
	float _timeElapsed;	//TickCount

	__int64 _curTime;
	__int64 _lastTime;
	__int64 _periodFrequency;

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;

	float _FPSTimeElapsed;
	float _worldTime;
	float _countTime; // 원하는 지점에서 시간을 재기 위해 만든 변수

	bool _countTimeResetSwitch; // _countTime 리셋(0으로 초기화) 판단하는 bool
	bool _countTimeSwitch; // _countTime을 셀 수 있는지 판단하는 bool

public:
	timer();
	~timer();

	HRESULT init();
	void tick(float lockFPS = 0.0f);
	unsigned long getFrameRate(char* str = NULL) const;

	inline float getElapsedTime() const { return _timeElapsed; }
	inline float getWorldTime() const { return _worldTime; }

	inline float getCountTime() { return _countTime; }
	inline void setCountTime(float countTime) { _countTime = countTime; }

	void setCountTimeResetSwitch(bool resetSwitch) { _countTimeResetSwitch = resetSwitch; }
	void countTimeSwitch(bool ONOff_Switch) { _countTimeSwitch = ONOff_Switch; }

	float* getCountTimePt() { return &_countTime; }
	bool* getCountTimeResetSwitchPt() { return &_countTimeResetSwitch; }
	bool* getCountTimeSwitchPt() { return &_countTimeSwitch; }
};
