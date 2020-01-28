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

	void boss_Skeleton_ChangeAnimation();		// 슬레이브 박쥐의 애니메이션 체인지 함수
};

