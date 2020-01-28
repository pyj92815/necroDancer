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
	_library.slave_Reset(&_slave);				// 슬레이브의 변수를 Null 값으로 초기화 해준다.
	_library.slave_Setting(&_slave, type);		// 슬레이브의 타입에 맞게 스테이터스를 만들어준다.
	_library.pos_Setting(&_slave, idx, idy);	// 슬레이브의 좌표 변수들을 갱신 해준다.
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


