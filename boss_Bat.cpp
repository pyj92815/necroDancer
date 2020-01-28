#include "stdafx.h"
#include "boss_Bat.h"

boss_Bat::boss_Bat()
{
}

boss_Bat::~boss_Bat()
{
}

HRESULT boss_Bat::init()
{
	return S_OK;
}

void boss_Bat::release()
{
}

void boss_Bat::update()
{
}

void boss_Bat::render()
{
	Rectangle(CAMERAMANAGER->getWorldDC(), _slave.pos.rc);
}

