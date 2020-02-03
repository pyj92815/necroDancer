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
	playerManager* _pm;					// 플레이어 매니져
	EnemyManager* _em;					// 애너미
	UImanager* _ui;						// UI
	miniMap* _minimap;					// 미니맵
	zOrder* _zOrder;					// Z-order
	bossStageScene* _bossStageScene;	// 보스씬
	visionFloodFill* _floodFill;		// 바닥 

	int _playerIdx, _playerIdy;			// 플레이어 id
	int _bossIdx, _bossIdy;				// 보스 계단 위치 
	int _stageIdx, _stageIdy;			// 스테이지 계단 위치 
	const char* fileName;				// 로드 파일 이름 


	int _tileFirstX, _tileSecondX; // 타일 깜박이는 숫자 
	int _tileFirstY, _tileSecondY; // 타일 깜박이는 숫자 

public:
	stageScene() { fileName = "Loby_SaveFile.map"; }
	~stageScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	player* getPlayerAddress()			{ return _pm->getPlayerInfo(); }		// Player
	vector<tagTile*> getStageTile()		{ return _vTotalList; }					// 타일 맵 
	UImanager* getUiAddress()			{ return _ui; }							// UI
	playerManager* getPlayerManager()	{ return _pm; }							//Player Manager

	void stageMapLoad(const char* fileName);
	void stageCollision();														// 바닥 충돌 
	void bossStageSceneAddressLink(bossStageScene* bossStageScene) { _bossStageScene = bossStageScene; }

	void nextPage();					// 다음 맵으로 넘어가기 위한 함수 
	void tileOnOff();					// 바닥 색깔 변화 
		
};