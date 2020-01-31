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
	float _countTime; // ���ϴ� �������� �ð��� ��� ���� ���� 

	bool _countTimeResetSwitch; // _countTime ����(0���� �ʱ�ȭ) �Ǵ��ϴ� bool
	bool _countTimeSwitch; // _countTime�� �� �� �ִ��� �Ǵ��ϴ� bool

public:
	timer();
	~timer();

	HRESULT init();
	void tick(float lockFPS = 0.0f);
	unsigned long getFrameRate(char* str = NULL) const;

	bool daehunCustom();

	inline float getElapsedTime() const { return _timeElapsed; }
	inline float getWorldTime() const { return _worldTime; }
	//ms ����
	inline float getDaeHunWorldTime() const { return _daehunWorldTime; }

	inline float getCountTime() { return _countTime; }
	inline void setCountTime(float countTime) { _countTime = countTime; }

	void setCountTimeResetSwitch(bool resetSwitch) { _countTimeResetSwitch = resetSwitch; }
	void countTimeSwitch(bool ONOff_Switch) { _countTimeSwitch = ONOff_Switch; }

	float* getCountTimePt() { return &_countTime; }
	bool* getCountTimeResetSwitchPt() { return &_countTimeResetSwitch; }
	bool* getCountTimeSwitchPt() { return &_countTimeSwitch; }
};
