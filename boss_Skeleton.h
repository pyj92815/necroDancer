#pragma once
#include "slave.h"

class boss_Skeleton : public slave
{
protected:

public:
	boss_Skeleton();
	~boss_Skeleton();

	HRESULT init();
	void release();
	void update();
	void render();
};

