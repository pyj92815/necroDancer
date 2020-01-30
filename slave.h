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

	// 슬레이브, 플레이어, UI
	virtual void move(SLAVE_DIRECTION direction);				// 슬레이브의 움직임 연산

	SLAVE_INFO* get_Slave() { return &_slave; }					// 슬레이브의 정보 주소를 받아온다.
	void slave_Pos_Setting();									// 슬레이브 좌표 변수 갱신
};

// 슬레이브 기본 클래스 