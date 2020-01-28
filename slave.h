#pragma once
#include "gameNode.h"
#include "slaveLibrary.h"

class slave : public gameNode
{
protected:
	SLAVE_INFO		_slave;
	slaveLibrary	_library;

public:
	slave();
	~slave();

	virtual HRESULT init(SLAVE_TYPE type, int idx, int idy);
	virtual void release();
	virtual void update();
	virtual void render();

	SLAVE_INFO* get_Slave() { return &_slave; }					// 슬레이브의 정보 주소를 받아온다.
};

// 슬레이브 기본 클래스 