#pragma once
#include "gameNode.h"
#include "tileNode.h"

class mapTool: public gameNode
{

private:
	HWND _btnPlay;				//플레이 버튼
	HWND _btnSave;				//저장 버튼
	HWND _btnLoad;				//불러오기 버튼
	HWND _btnTerrainDraw;		//지형 그리기 버튼
	HWND _btnWallDraw;			//벽 그리기 버튼
	HWND _btnObjectDraw;		//오브젝트 그리기 버튼
	HWND _btnTrap;				//함정 버튼
	HWND _btnEraser;			//지우개 버튼

	tagCurrentTile _currentTile;
	tagSampleTile _terrainTile[TERRAINTILEX * TERRAINTILEY];
	tagSampleTile _wallTile[WALLTILEX * WALLTILEY];
	tagSampleTile _trapTile[TRAPTILEX * TRAPTILEY];
	tagTile		 _tiles[TILEX * TILEY];

public:
	mapTool();
	~mapTool();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setup();

	virtual void setMap();
	virtual void save();
	virtual void load();

	//virtual void clickLeft();

	//어떤 지형을 선택했는가?
	TERRAIN terrainSelect(int frameX, int frameY);
	//어떤 벽을 선택했는가?
	WALL wallSelect(int frameX, int frameY);
	//어떤 함정를 선택했는가?
	TRAP trapSelect(int frameX, int frameY);

	void setS(int num) { _crtSelect = num; }

};

