#include "stdafx.h"
#include "slave.h"

slave::slave()
{
}

slave::~slave()
{
}

HRESULT slave::init(SLAVE_TYPE type, int idx, int idy)
{
	_library.slave_Reset(&_slave);				// �����̺��� ������ Null ������ �ʱ�ȭ ���ش�.
	_library.slave_Setting(&_slave, type);		// �����̺��� Ÿ�Կ� �°� �������ͽ��� ������ش�.
	_library.pos_Setting(&_slave, idx, idy);	// �����̺��� ��ǥ �������� ���� ���ش�.
	_slave.image.animation->start();
	return S_OK;
}

void slave::release()
{
}

void slave::update()
{
}

void slave::render()
{
	_slave.image.img->aniRender(CAMERAMANAGER->getWorldDC(), _slave.pos.center.x, _slave.pos.center.y -
		(_slave.image.img->getFrameHeight() / 4), _slave.image.animation);

}


