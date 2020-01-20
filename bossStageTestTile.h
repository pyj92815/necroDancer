#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "tile.h"

class bossStageTestTile : public gameNode
{
private:
	vector<tile*>				_vTotalList;		// ��ü Ÿ�� ����	(�׽�Ʈ��)
	vector<tile*>::iterator		_viTotalList;		// ��ü Ÿ�� ����	(�׽�Ʈ��)

	tile*						_boss;				// ���� ��ġ Ÿ��(�׽�Ʈ��)
	int							_tileCnt;			// Ÿ�� ���͹���

public:
	bossStageTestTile();
	~bossStageTestTile();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// ����
	void setTile();	// Ÿ�� ����
	void setTotalTile(vector<tile*> total) { _vTotalList = total; }	// Ÿ�� ����
	
	// ����
	vector<tile*> getTotalTile() { return _vTotalList; } // Ÿ�� ����
};

