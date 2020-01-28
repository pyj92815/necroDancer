#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	RECT  _cameraRect;							// 렌더링 RECT   
	float _cameraWorldSizeX, _cameraWorldSizeY; // 카메라 배경으 
	float _cameraSizeX, _cameraSizeY;			// 카메라 크기 
	float _cameraX, _cameraY;					// 카메라 좌표 

	float _cameraMapFullTileSizeX, _cameraMapFullTileSizeY; //맵툴 최대 사이즈
	float _cameraMapTileSizeX, _cameraMapTileSizeY;			//맵툴 크기
	float _cameraMapSizeX, _cameraMapSizeY;					//맵툴 좌표			

	HDC _worldDC;
	image* _worldImage;

	//HDC _mapToolDC;
	//image* _mapToolImage;

	bool _isCameraMoveX;
	bool _isCameraMoveY;

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
	void Camera_Move();
	// 월드 DC
	HDC getWorldDC() { return _worldDC; }
	image* getWorldImage() { return _worldImage; }
	// 맵툴 DC
	/*HDC getmapToolDC() { return _mapToolDC; }
	image* getmapToolImage() { return _mapToolImage; }*/
	
	// 맵툴 사이즈
	void set_CameraMapTielSize(float x, float y);
	float get_CameraMapTileSize_X() { return _cameraMapTileSizeX; }
	float get_CameraMapTileSize_Y() { return _cameraMapTileSizeY; }

	// 맵툴 좌표
	void set_CameraMapTool_XY(int x, int y);
	void set_CameraMapTool_XY(float x, float y);
	void set_CameraMapTool_XY(POINT xy);
	void set_CameraMapTool_XY(RECT rc);

	float get_CameraMapSize_X() { return _cameraMapSizeX; }
	float get_CameraMapSize_Y() { return _cameraMapSizeY; }

	void CameraMapTool_Correction();
	void CameraMapTool_Move();

	//카메라 흔들리는보정 
	void Camera_WorldDC_Shake();
	RECT getCamera_Rect() { return _cameraRect; }
	void set_CameraPos_Update(float x, float y);

};

