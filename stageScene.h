#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "EnemyManager.h"
#include "UImanager.h"
#include "Collision.h"

class bossStageScene;

struct tagClass
{
	tagTile* tile;
	playerManager* player;
	Enemy* enemy;
};

struct zOrder
{
	float* y;
	tagClass* Object;

	zOrder(float* y, tagClass* Object)
	{
		this->y = y;
		this->Object = Object;
	};
	zOrder() { ; }
};

class stageScene: public gameNode
{
private: // �� �浹  
	tagTile							_tiles[TILEX * TILEY];   // �������� ��
	vector<tagTile*>						  _vTotalList;	 // �������� �� ������ ����
	vector<tagTile*>::iterator			     _viTotalList;

	Collision _collision;			// �浹ó�� 
private: // ��Ʈ����
	vector<zOrder*> _zOrderVector;

	vector<pair<float, tagClass*>> 				    _vZorder;
	vector<pair<float, tagClass*>>::iterator	   _viZorder;
private: // ���� ���� 	
	playerManager* _pm;
	EnemyManager* _em;
	UImanager* _ui;
	
	bossStageScene* _bossStageScene;
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
	
	// �� 
	void stageMapLoad();
	void stageCollision();
	void bossStageSceneAddressLink(bossStageScene* bossStageScene) { _bossStageScene = bossStageScene; }

	void setVision(POINT index, int sight);
};

