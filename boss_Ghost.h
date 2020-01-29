#pragma once
#include "slave.h"

class boss_Ghost : public slave
{
protected:

public:
	boss_Ghost();
	~boss_Ghost();

	HRESULT init();
	void update();

	void boss_Ghost_ChangeAnimation();		// 슬레이브 고스트의 애니메이션 체인지 함수
};

