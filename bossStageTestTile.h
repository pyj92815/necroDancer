#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "tile.h"

class bossStageTestTile : public gameNode
{
private:
	vector<tile*>				_vTotalList;		// 전체 타일 벡터	(테스트용)
	vector<tile*>::iterator		_viTotalList;		// 전체 타일 벡터	(테스트용)

	tile*						_boss;				// 보스 위치 타일(테스트용)
	int							_tileCnt;			// 타일 인터벌용

public:
	bossStageTestTile();
	~bossStageTestTile();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// 셋터
	void setTile();	// 타일 셋팅
	void setTotalTile(vector<tile*> total) { _vTotalList = total; }	// 타일 갱신
	
	// 겟터
	vector<tile*> getTotalTile() { return _vTotalList; } // 타일 겟터
};

