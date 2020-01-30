#pragma once
#include "slave.h"

class boss_Skeleton : public slave
{
protected:

public:
	boss_Skeleton();
	~boss_Skeleton();

	HRESULT init();
	void update();

	void move();								// 슬레이브의 움직임 연산

	void boss_Skeleton_ChangeAnimation();		// 슬레이브 박쥐의 애니메이션 체인지 함수
};

