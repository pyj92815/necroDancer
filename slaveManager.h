#pragma once
#include "gameNode.h"
#include "slave.h"
#include "slaveManager_Library.h"

class slaveManager : public gameNode
{
private:
	vector<slave*>					_vSlaveList;		// 슬레이브를 담는 벡터
	vector<slave*>::iterator		_viSlaveList;		// 슬레이브 이터에이터

	slaveManager_Library*			_library;			// 슬레이브 매니저 함수

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// 겟터
	vector<slave*> get_SlaveList() { return _vSlaveList; }			// 슬레이브 겟터
	slaveManager_Library* get_SlaveLibrary() { return _library; }	// 슬레이브 함수

	// 슬레이브 소환 
	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// SLAVE_BAT,				 박쥐				// SLAVE_GHOST,				 고스트
	// SLAVE_SKELETON,			 스켈레톤			// SLAVE_SKELETON_YELLOW,	 옐로우 스켈레톤
	// SLAVE_NONE				 없음
	void create_Slave(SLAVE_TYPE type, int idx, int idy);
	//void create_Slave(SLAVE_TYPE type, int idx, int idy) { _library->create_Slave(&_vSlaveList, type, idx, idy); }
};

