#pragma once
#include "stdafx.h"

class slaveManager_Library
{


public:

	
	void create_Slave(vector<slave*>* vSlaveList, SLAVE_TYPE type, int idx, int idy)	// 슬레이브를 만든다. 해당 이름을 가진 슬레이브를 인덱스 x, y 위치에 만든다.
	{
		slave* new_Slave;
		new_Slave = new slave;								// 공간 할당을 받는다.
		new_Slave->init(type, idx, idy);					// 해당 슬레이브를 만든다.

		vSlaveList->push_back(new_Slave);					// 새로 만들어진 슬레이브를 저장한다.
	}

};
