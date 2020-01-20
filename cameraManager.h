#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	float _cameraWorldSizeX, _cameraWorldSizeY; // 카메라 배경으 
	float _cameraSizeX, _cameraSizeY;			// 카메라 크기 
	float _cameraX, _cameraY;					// 카메라 좌표 

	
	HDC _worldDC;
	image* _worldImage;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// 카메라 사이즈 
	void set_CameraSize(float x, float y);
	float get_CameraSize_X() { return _cameraSizeX; }
	float get_CameraSize_Y() { return _cameraSizeY; }

	// 카메라의 좌표 
	void set_CameraXY(int x, int y);
	void set_CameraXY(float x, float y);
	void set_CameraXY(POINT xy);
	void set_CameraXY(RECT rc);

	float get_CameraX() { return _cameraX; }
	float get_CameraY() { return _cameraY; }

	//카메라가 맵 밖으로 나가지 못하게 
	void Camera_Correction();

	// 월드 DC
	HDC getWorldDC() { return _worldDC; }
	image* getWorldImage() { return _worldImage; }

};

