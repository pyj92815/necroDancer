#include "stdafx.h"
#include "boss_Skeleton.h"

boss_Skeleton::boss_Skeleton()
{
}

boss_Skeleton::~boss_Skeleton()
{
}

HRESULT boss_Skeleton::init()
{
	return S_OK;
}

void boss_Skeleton::release()
{
}

void boss_Skeleton::update()
{
}

void boss_Skeleton::render()
{
	Rectangle(CAMERAMANAGER->getWorldDC(), _slave.pos.rc);
}
