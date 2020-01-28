#pragma once
#include "slave.h"

class boss_Bat : public slave
{

public:
	boss_Bat();
	~boss_Bat();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

