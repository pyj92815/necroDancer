#include "stdafx.h"
#include "slave.h"

slave::slave()
{
}

slave::~slave()
{
}

HRESULT slave::init()
{
	_slave.slave_Setting();			// �����̺��� ������ Null ������ �ʱ�ȭ ���ش�.

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
}

