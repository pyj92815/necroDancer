#include "stdafx.h"
#include "slaveManager.h"

HRESULT slaveManager::init()
{

	return S_OK;
}

void slaveManager::release()
{
}

void slaveManager::update()
{
	for (_viSlaveList = _vSlaveList.begin(); _viSlaveList != _vSlaveList.end(); ++_viSlaveList)
	{
		(*_viSlaveList)->update();
	}

	delete_Slave();
}

void slaveManager::render()
{
	for (_viSlaveList = _vSlaveList.begin(); _viSlaveList != _vSlaveList.end(); ++_viSlaveList)
	{
		(*_viSlaveList)->render();
	}
}

void slaveManager::create_Slave(SLAVE_TYPE type, int idx, int idy)
{
	slave* new_Slave;

	// 타입에 맞는 공간 할당을 받는다.
	switch (type)
	{
		case SLAVE_TYPE::SLAVE_BAT:
			new_Slave = new boss_Bat;
			break;

		case SLAVE_TYPE::SLAVE_GHOST:
			new_Slave = new boss_Ghost;
			break;

		case SLAVE_TYPE::SLAVE_SKELETON:
			new_Slave = new boss_Skeleton;
			break;

		case SLAVE_TYPE::SLAVE_SKELETON_YELLOW:
			new_Slave = new boss_Skeleton_Yellow;
			break;
	}		
	new_Slave->init(type, idx, idy);							// 해당 슬레이브를 만든다.
	_vSlaveList.push_back(new_Slave);							// 새로 만들어진 슬레이브를 저장한다.
}

void slaveManager::delete_Slave()
{
	for (int i = 0; i < _vSlaveList.size(); ++i)
	{
		// 에너미의 체력이 모두 떨어지면 삭제
		if (_vSlaveList[i]->get_Slave()->status.hp <= 0 && !_vSlaveList[i]->get_Slave()->b_Value.ghostJonYha)
		{
			_vSlaveList.erase(_vSlaveList.begin() + i);
			break;
		}

		// 고스트는 무적 상태일때 죽지 않아야 한다.
		if (_vSlaveList[i]->get_Slave()->b_Value.ghostJonYha)
		{
			_vSlaveList[i]->get_Slave()->status.hp = 1;
		}
	}
}

