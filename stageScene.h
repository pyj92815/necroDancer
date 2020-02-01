#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "UImanager.h"
#include "Collision.h"
#include "miniMap.h"
#include "zOrder.h"
#include "visionFloodFill.h"
#include"EnemyManager.h"
class bossStageScene;
class stageScene: public gameNode
{
private: // 맵 충돌  
	tagTile							_tiles[TILEX * TILEY];   // 스테이지 맵
	vector<tagTile*>						  _vTotalList;	 // 스테이지 맵 포인터 백터
	vector<tagTile*>::iterator			     _viTotalList;

	Collision _collision;			// 충돌처리 
private: // Enemy 포인터 
	map<CHARACTER, POINT>		   	_mEnemyPoint;
	map<CHARACTER, POINT>::iterator _miEnemyPoint;

private: // 하위 계층 	
	playerManager* _pm;
	EnemyManager* _em;
	UImanager* _ui;
	bossStageScene* _bossStageScene;
	miniMap* _minimap;
	zOrder* _zOrder;
	visionFloodFill* _floodFill;

	int _playerIdx, _playerIdy;
	int _bossIdx, _bossIdy;
	int _stageIdx, _stageIdy;
	const char* fileName;
public:
	stageScene() { fileName = "Loby_SaveFile.map"; }
	~stageScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	player* getPlayerAddress() { return _pm->getPlayerInfo(); }

	// 제트오더 관련
	//void ZorderSetup();
	//vector<zOrder*>ZorderUpdate(vector<zOrder*>  num);
	vector<tagTile*> getStageTile() { return _vTotalList; }
	UImanager* getUiAddress() { return _ui; }
	playerManager* getPlayerManager() { return _pm; }
	// 맵 
	void stageMapLoad(const char* fileName);
	void stageCollision();
	void bossStageSceneAddressLink(bossStageScene* bossStageScene) { _bossStageScene = bossStageScene; }

	void setVision(POINT index, int sight);
	void nextPage();
	
};