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
	new_Slave = new slave;								// ���� �Ҵ��� �޴´�.
	new_Slave->init(type, idx, idy);					// �ش� �����̺긦 �����.

	_vSlaveList.push_back(new_Slave);					// ���� ������� �����̺긦 �����Ѵ�.
}

