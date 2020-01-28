#pragma once
#include "slave.h"

class boss_Skeleton_Yellow : public slave
{
protected:

public:
	boss_Skeleton_Yellow();
	~boss_Skeleton_Yellow();

	HRESULT init();
	void release();
	void update();
	void render();

};

