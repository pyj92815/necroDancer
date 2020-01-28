#include "stdafx.h"
#include "boss_Skeleton_Yellow.h"

boss_Skeleton_Yellow::boss_Skeleton_Yellow()
{
}

boss_Skeleton_Yellow::~boss_Skeleton_Yellow()
{
}

HRESULT boss_Skeleton_Yellow::init()
{
	return S_OK;
}

void boss_Skeleton_Yellow::release()
{
}

void boss_Skeleton_Yellow::update()
{
}

void boss_Skeleton_Yellow::render()
{
	Rectangle(CAMERAMANAGER->getWorldDC(), _slave.pos.rc);
}
