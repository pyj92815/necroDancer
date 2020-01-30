#pragma once
#include "slave.h"

class boss_Bat : public slave
{

public:
	boss_Bat();
	~boss_Bat();

	HRESULT init();
	void update();

	void move();							// 슬레이브의 움직임 연산

	void boss_Bat_ChangeAnimation();		// 슬레이브 박쥐의 애니메이션 체인지 함수
};

