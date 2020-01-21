#pragma once
#include "gameNode.h"
#include <string>

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

	float _WINSIZEX, _WINSIZEY;
	int _pos[2];

private:
	tagButton _saveButton;		//저장
	tagButton _loadButton;		//로드
	tagButton _terrainButton;	//지형
	tagButton _wallButton;		//벽
	tagButton _trapButton;		//함정
	tagButton _itemButton;		//아이템
	tagButton _exitButton;		//나가기
private:
	tagMouse _RectCreate;
	bool _isClick;
	
	int _startL, _startT, _endR, _endB;

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

