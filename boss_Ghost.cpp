#include "stdafx.h"
#include "boss_Ghost.h"

boss_Ghost::boss_Ghost()
{
}

boss_Ghost::~boss_Ghost()
{
}

HRESULT boss_Ghost::init()
{
	return S_OK;
}

void boss_Ghost::release()
{
}

void boss_Ghost::update()
{
}

void boss_Ghost::render()
{
	Rectangle(CAMERAMANAGER->getWorldDC(), _slave.pos.rc);
}
