#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
	_cameraSizeX = WINSIZEX;
	_cameraSizeY = WINSIZEY;

	//초기값 플레이어 위치로 할 예정 
	_cameraX = 75;
	_cameraY = 220;

	_worldImage = new image;
	_worldImage = IMAGEMANAGER->addImage("worldMap",4000, 2000);
	_worldDC = _worldImage->getMemDC();

	_cameraWorldSizeX = 5200;
	_cameraWorldSizeY = 5200;

	isCameraMoveX = false;
	isCameraMoveY = false;
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::update()
{
}

void cameraManager::render()
{
}

void cameraManager::set_CameraSize(float x, float y)
{
	_cameraSizeX = x;
	_cameraSizeY = y;
	Camera_Correction();
}

void cameraManager::set_CameraXY(int x, int y)
{
	_cameraX = x - _cameraSizeX / 2.0f;
	_cameraY = y - _cameraSizeY / 2.0f;
	Camera_Correction();
}

void cameraManager::set_CameraXY(float x, float y)
{
	// 카메라의 위치를 판단한다.
	float winX = (x - _cameraSizeX / 2.0f); // 카메라의 시작위치 X
	float winY = (y - _cameraSizeY / 2.0f); // 카메라의 시작위치 Y

	_cameraX > winX ? isCameraMoveX = true : isCameraMoveX = false;
	_cameraY > winY ? isCameraMoveY = true : isCameraMoveY = false;

	//카메라의 Y 
	if (isCameraMoveY)
	{
		_cameraY -= 2.5f;
		if (_cameraY < winY) _cameraY = winY;	
	}
	else
	{
		_cameraY += 2.5f;
		if (_cameraY > winY) _cameraY = winY;
	}

	//카메라의 X 
	if (isCameraMoveX)
	{
		_cameraX -= 2.5f;
		if (_cameraX < winX) _cameraX = winX;
	}
	else
	{
		_cameraX += 2.5f;
		if (_cameraX > winX) _cameraX = winX;
	}

	//_cameraX = x - _cameraSizeX / 2.0f;
	//_cameraY = y - _cameraSizeY / 2.0f;
	Camera_Correction();
}

void cameraManager::set_CameraXY(POINT xy)
{
	_cameraX = xy.x - _cameraSizeX / 2.0f;
	_cameraY = xy.y - _cameraSizeY / 2.0f;
	Camera_Correction();
}

void cameraManager::set_CameraXY(RECT rc)
{
	_cameraX = rc.left - _cameraSizeX / 2.0f;
	_cameraY = rc.top - _cameraSizeY / 2.0f;
	Camera_Correction();
}

void cameraManager::Camera_Correction()
{
	if (_cameraX < 0) _cameraX = 0;
	if (_cameraY < 0) _cameraY = 0;
	if (_cameraX + _cameraSizeX > _cameraWorldSizeX)
	{
		_cameraX = _cameraWorldSizeX - _cameraSizeX;
	}
	if (_cameraY + _cameraSizeY > _cameraWorldSizeY)
	{
		_cameraY = _cameraWorldSizeY - _cameraSizeY;
	}
}

void cameraManager::Camera_Move()
{


}


