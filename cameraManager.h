#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	float _cameraWorldSizeX, _cameraWorldSizeY; // ī�޶� ����� 
	float _cameraSizeX, _cameraSizeY;			// ī�޶� ũ�� 
	float _cameraX, _cameraY;					// ī�޶� ��ǥ 

	
	HDC _worldDC;
	image* _worldImage;

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// ī�޶� ������ 
	void set_CameraSize(float x, float y);
	float get_CameraSize_X() { return _cameraSizeX; }
	float get_CameraSize_Y() { return _cameraSizeY; }

	// ī�޶��� ��ǥ 
	void set_CameraXY(int x, int y);
	void set_CameraXY(float x, float y);
	void set_CameraXY(POINT xy);
	void set_CameraXY(RECT rc);

	float get_CameraX() { return _cameraX; }
	float get_CameraY() { return _cameraY; }

	//ī�޶� �� ������ ������ ���ϰ� 
	void Camera_Correction();

	// ���� DC
	HDC getWorldDC() { return _worldDC; }
	image* getWorldImage() { return _worldImage; }

};

