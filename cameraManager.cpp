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
	_worldImage = IMAGEMANAGER->addImage("worldMap",2080, 2080);
	_worldDC = _worldImage->getMemDC();

	_isCameraMoveX = false;
	_isCameraMoveY = false;

	/*_mapToolImage = new image;
	_mapToolImage = IMAGEMANAGER->addImage("mapToolMap", 5200, 5200);
	_mapToolDC = _mapToolImage->getMemDC();*/

	_cameraWorldSizeX = 2080;
	_cameraWorldSizeY = 2080;

	_cameraMapTileSizeX = 1800;
	_cameraMapTileSizeY = 900;
	
	_cameraMapSizeX = NULL;
	_cameraMapSizeY = NULL;

	_cameraRect = RectMake(_cameraX, _cameraY, WINSIZEX, WINSIZEY);
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

void cameraManager::set_CameraXY(float x, float y , bool fast)
{
	if (fast)
	{
		_cameraX = x - _cameraSizeX / 2.0f;
		_cameraY = y - _cameraSizeY / 2.0f;
		Camera_Correction();
		_cameraRect = RectMake(_cameraX, _cameraY, WINSIZEX, WINSIZEY);  // RECT 업데이트 
		return;
	}
	// 카메라의 위치를 판단한다.
	float winX = (x - _cameraSizeX / 2.0f); // 카메라의 시작위치 X
	float winY = (y - _cameraSizeY / 2.0f); // 카메라의 시작위치 Y

	_cameraX > winX ? _isCameraMoveX = true : _isCameraMoveX = false;
	_cameraY > winY ? _isCameraMoveY = true : _isCameraMoveY = false;

	//카메라의 Y 
	if (_isCameraMoveY)
	{
		_cameraY -= 3.0f;
		if (_cameraY < winY) _cameraY = winY;	
	}
	else
	{
		_cameraY += 3.0f;
		if (_cameraY > winY) _cameraY = winY;
	}

	//카메라의 X 
	if (_isCameraMoveX)
	{
		_cameraX -= 3.0f;
		if (_cameraX < winX) _cameraX = winX;
	}
	else
	{
		_cameraX += 3.0f;
		if (_cameraX > winX) _cameraX = winX;
	}

	/*_cameraX = x - _cameraSizeX / 2.0f;
	_cameraY = y - _cameraSizeY / 2.0f;*/

	Camera_Correction();
	_cameraRect = RectMake(_cameraX, _cameraY, WINSIZEX, WINSIZEY);  // RECT 업데이트 
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
//■■■■■■■■■■■■■■■■■■■■■■■■■맵툴 사이즈■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
void cameraManager::set_CameraMapTielSize(float x, float y)
{
	_cameraSizeX = x;
	_cameraSizeY = y;
	CameraMapTool_Correction();
}

void cameraManager::set_CameraMapTool_XY(int x, int y)
{
	_cameraX = x - _cameraSizeX / 2.0f;
	_cameraY = y - _cameraSizeY / 2.0f;
	CameraMapTool_Correction();
}

void cameraManager::set_CameraMapTool_XY(float x, float y)
{
	_cameraX = x - _cameraSizeX / 2.0f;
	_cameraY = y - _cameraSizeY / 2.0f;
	CameraMapTool_Correction();
}

void cameraManager::set_CameraMapTool_XY(POINT xy)
{
	_cameraX = xy.x - _cameraSizeX / 2.0f;
	_cameraY = xy.y - _cameraSizeY / 2.0f;
	CameraMapTool_Correction();
}


void cameraManager::set_CameraMapTool_XY(RECT rc)
{
	_cameraX = rc.left - _cameraSizeX / 2.0f;
	_cameraY = rc.top - _cameraSizeY / 2.0f;
	CameraMapTool_Correction();
}

void cameraManager::CameraMapTool_Correction()
{
	if (_cameraX < 0) _cameraX = 0;
	if (_cameraY < 0) _cameraY = 0;
	if (_cameraX + 1800 > 2080)
	{
		_cameraX = 2080 - 1800;
	}
	if (_cameraY + 900 > 2080)
	{
		_cameraY = 2080 - 900;
	}
}
void cameraManager::CameraMapTool_Move()
{
}


void cameraManager::Camera_WorldDC_Shake()
{
	// 0.0 camerax,y 에서는 충돌처리가 안됨 
	set_CameraXY(_cameraX + RND->getFromFloatTo(-3, 3), _cameraY + RND->getFromFloatTo(-3, 3));
	set_CameraXY(_cameraX + RND->getFromFloatTo(-3, 3), _cameraY + RND->getFromFloatTo(-3, 3));
	set_CameraXY(_cameraX + RND->getFromFloatTo(-3, 3), _cameraY + RND->getFromFloatTo(-3, 3));
}

void cameraManager::set_CameraPos_Update(float x, float y)
{
	_cameraX = x;
	_cameraY = y; 

	if (_cameraX < 0) _cameraX = 0;
	if (_cameraY < 0) _cameraY = 0;
	if (_cameraX + _cameraMapTileSizeX > 2080)
	{
		_cameraX = 2080 - _cameraMapTileSizeX;
	}
	if (_cameraY + _cameraMapTileSizeY > 2080)
	{

		_cameraY = 2080 - _cameraMapTileSizeY;
	}
}


