#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "tile.h"

class bossStageTestTile : public gameNode
{
private:

	tile*						_boss;				// 보스 위치 타일(테스트용)
	int							_tileCnt;			// 타일 인터벌용

	tagTile* _tiles[TILEX * TILEY];						// 불러온 맵을 저장한다.
	vector<tagTile*>				_vTotalList;		// 전체 타일 벡터	(테스트용)
	vector<tagTile*>::iterator		_viTotalList;		// 전체 타일 벡터	(테스트용)


public:
	bossStageTestTile();
	~bossStageTestTile();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// 셋터
	void setTile();	// 타일 셋팅
	void setTotalTile(vector<tagTile*> total) { _vTotalList = total; }	// 타일 갱신
	
	// 맵 모든 정보를 겟터
	vector<tagTile*> getTotalTile() { return _vTotalList; } // 타일 겟터

	// 맵 불러오는 함수
	void BossStageLoad();

};

