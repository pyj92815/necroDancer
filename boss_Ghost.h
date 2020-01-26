#pragma once
#include "slave.h"

class boss_Ghost : public slave
{
protected:

public:
	boss_Ghost();
	~boss_Ghost();

	virtual HRESULT init();
	void release();
	void update();
	void render();
};

