#pragma once
#include "gameNode.h"
#include "slaveLibrary.h"

class slave : public gameNode
{
protected:
	SLAVE_INFO	_slave;

public:
	slave();
	~slave();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

// 슬레이브 기본 클래스 