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
	_slave.slave_Setting();			// 슬레이브의 변수를 Null 값으로 초기화 해준다.

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

