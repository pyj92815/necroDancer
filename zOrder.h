#pragma once
#include "gameNode.h"

class tagTile;
class playerManager;
class Enemy;
class EnemyManager;
class player;
class slaveManager;
class SLAVE_INFO;
class slave;
class boss;
class deathMetal;

struct tagClass : public gameNode
{
	tagTile* tile;
	playerManager* pm;
	Enemy* enemy;
	player* player;
	slaveManager* slaveMoster;
	slave* slaveEnemy;
	deathMetal* deathMetalboss;
};

struct tagzOrder
{
	float* y;
	tagClass* Object;

	tagzOrder(float* y, tagClass* Object)
	{
		this->y = y;
		this->Object = Object;
	};
	tagzOrder() { ; }
};


class zOrder
{
private:

	vector<tagzOrder*> _zOrderVector;

	vector<pair<float, tagClass*>> 				    _vZorder;
	vector<pair<float, tagClass*>>::iterator	   _viZorder;

public:
	zOrder();
	~zOrder();

	HRESULT init();
	void release();
	void update();
	void render();

	vector<tagzOrder*>ZorderUpdate(vector<tagzOrder*>  num);
	void zOrderSetup(int idx, int idy, vector<tagTile*>* tagTile, playerManager* pm, EnemyManager* em);
	void zOrderSetup(int idx, int idy, tagTile* tagTile, playerManager* pm, EnemyManager* em);
	void zOrderSetup(int idx, int idy, tagTile* tagTile, player* player, slaveManager* slave,deathMetal* metal);
};

