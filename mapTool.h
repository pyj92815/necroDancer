#pragma once
#include "gameNode.h"
#include <string>

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

	float _WINSIZEX, _WINSIZEY;
	int _pos[2];

private:
	tagButton _saveButton;		//����
	tagButton _loadButton;		//�ε�
	tagButton _terrainButton;	//����
	tagButton _wallButton;		//��
	tagButton _trapButton;		//����
	tagButton _itemButton;		//������
	tagButton _exitButton;		//������
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

	//� ������ �����ߴ°�?
	TERRAIN terrainSelect(int frameX, int frameY);
	//� ���� �����ߴ°�?
	WALL wallSelect(int frameX, int frameY);
	//� ������ �����ߴ°�?
	TRAP trapSelect(int frameX, int frameY);

	void setS(int num) { _crtSelect = num; }

};

