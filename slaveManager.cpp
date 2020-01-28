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

	// Ÿ�Կ� �´� ���� �Ҵ��� �޴´�.
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
	new_Slave->init(type, idx, idy);							// �ش� �����̺긦 �����.
	_vSlaveList.push_back(new_Slave);							// ���� ������� �����̺긦 �����Ѵ�.
}

