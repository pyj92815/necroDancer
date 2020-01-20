#pragma once
#include "gameNode.h"
#include "tileNode.h"

class mapTool: public gameNode
{

private:
	HWND _btnPlay;				//�÷��� ��ư
	HWND _btnSave;				//���� ��ư
	HWND _btnLoad;				//�ҷ����� ��ư
	HWND _btnTerrainDraw;		//���� �׸��� ��ư
	HWND _btnWallDraw;			//�� �׸��� ��ư
	HWND _btnObjectDraw;		//������Ʈ �׸��� ��ư
	HWND _btnTrap;				//���� ��ư
	HWND _btnEraser;			//���찳 ��ư

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

	//� ������ �����ߴ°�?
	TERRAIN terrainSelect(int frameX, int frameY);
	//� ���� �����ߴ°�?
	WALL wallSelect(int frameX, int frameY);
	//� ������ �����ߴ°�?
	TRAP trapSelect(int frameX, int frameY);

	void setS(int num) { _crtSelect = num; }

};

