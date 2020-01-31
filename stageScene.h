#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "EnemyManager.h"
#include "UImanager.h"
#include "Collision.h"
#include "miniMap.h"
#include "zOrder.h"
#include "visionFloodFill.h"

class bossStageScene;

class stageScene: public gameNode
{
private: // �� �浹  
	tagTile							_tiles[TILEX * TILEY];   // �������� ��
	vector<tagTile*>						  _vTotalList;	 // �������� �� ������ ����
	vector<tagTile*>::iterator			     _viTotalList;

	Collision _collision;			// �浹ó�� 
private: // ��Ʈ����
	//vector<zOrder*> _zOrderVector;

	//vector<pair<float, tagClass*>> 				    _vZorder;
	//vector<pair<float, tagClass*>>::iterator	   _viZorder;

private: // ���� ���� 	
	playerManager* _pm;
	EnemyManager* _em;
	UImanager* _ui;
	bossStageScene* _bossStageScene;
	miniMap* _minimap;
	zOrder* _zOrder;
	visionFloodFill* _floodFill;

public:
	stageScene() {}
	~stageScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	player* getPlayerAddress() { return _pm->getPlayerInfo(); }

	// ��Ʈ���� ����
	void ZorderSetup();
	vector<zOrder*>ZorderUpdate(vector<zOrder*>  num);
	vector<tagTile*> getStageTile() { return _vTotalList; }
	UImanager* getUiAddress() { return _ui; }
	playerManager* getPlayerManager() { return _pm; }
	// �� 
	void stageMapLoad();
	void stageCollision();
	void bossStageSceneAddressLink(bossStageScene* bossStageScene) { _bossStageScene = bossStageScene; }

	void setVision(POINT index, int sight);
};