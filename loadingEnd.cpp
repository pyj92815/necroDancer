#include "stdafx.h"
#include "loadingEnd.h"

loadingEnd::loadingEnd()
{
}

loadingEnd::~loadingEnd()
{
}

HRESULT loadingEnd::init()
{
	return S_OK;
}

void loadingEnd::release()
{
}

void loadingEnd::update()
{
}

void loadingEnd::render()
{
	IMAGEMANAGER->findImage("intro_end")->render(getMemDC(), 0, 0);

}
