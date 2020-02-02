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
	float _daehunWorldTime;
	float _countTime; // 원하는 지점에서 시간을 재기 위해 만듬 
	float _countLoadingTime; // 로딩 시간을 주기 위해 만듬

	bool _countTimeResetSwitch; // _countTime 리셋(0으로 초기화) 판단하는 bool
	bool _countTimeSwitch; // _countTime을 셀 수 있는지 판단하는 bool

	bool _countLoadingTimeSwitch; // 로딩 시간을 판별하는 함수

public:
	timer();
	~timer();

	HRESULT init();
	void tick(float lockFPS = 0.0f);
	unsigned long getFrameRate(char* str = NULL) const;

	bool daehunCustom();

	inline float getElapsedTime() const { return _timeElapsed; }
	inline float getWorldTime() const { return _worldTime; }
	//ms 단위
	inline float getDaeHunWorldTime() const { return _daehunWorldTime; }

	inline float getCountTime() { return _countTime; }

	// 로딩을 재기 위한 시간
	inline float getCountLoadingTime() { return _countLoadingTime; }

	float* getCountTimePt() { return &_countTime; }
	bool* getCountTimeResetSwitchPt() { return &_countTimeResetSwitch; }
	bool* getCountTimeSwitchPt() { return &_countTimeSwitch; }

	float* getCountLoadingTimePt() { return &_countLoadingTime; }
	bool* getCountLoadingTimeSwitchPt() { return &_countLoadingTimeSwitch; }
};
