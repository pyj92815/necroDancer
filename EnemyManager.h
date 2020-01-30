#pragma once
#include"gameNode.h"
#include"Enemy_Bat.h"
#include"Enemy_Dragon.h"
#include"Enemy_Ghost.h"
#include"Enemy_Minotaur.h"
#include"Enemy_Skeleton.h"
#include"Enemy_Skeleton_Yellow.h"
#include"Enemy_Slime_Blue.h"
#include"Enemy_Slime_Orange.h"
#include"Enemy_Warith.h"
#include"Enemy_Zombie.h"
#include<vector>

class player;

enum class EnemyType
{
	BAT,DRAGON,GHOST,MINOTAUR,SKELETON,SKELETON_YELLOW,SLIME_BLUE,SLIME_ORANGE,WRAITH,ZOMBIE
};

class EnemyManager :public gameNode
{
private:
	vector<Enemy*> _vEnemy;
	vector<Enemy*>::iterator _viEnemy;

	EnemyType _enemyType;

	player* _player;

public:
	EnemyManager() {};
	~EnemyManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void EnemyRemove();

	void EnemyInspection();
	void 임시enemy생성();
	
	void EnemyCreate(float x, float y, EnemyType enemyType);

	void Enemy_Bat_Create(float x, float y);
	void Enemy_Dragon_Create(float x, float y);
	void Enemy_Ghost_Create(float x, float y);
	void Enemy_Minotaur_Create(float x, float y);
	void Enemy_Skeleton_Create(float x, float y);
	void Enemy_Skeleton_Yellow_Create(float x, float y);
	void Enemy_Slime_Blue_Create(float x, float y);
	void Enemy_Slime_Orange_Create(float x, float y);
	void Enemy_Wraith_Create(float x, float y);
	void Enemy_Zombie_Create(float x, float y);

	//이미지 추가 함수
	void imageAdd();
	void AnimationAdd();

	void AddressLink(player* pl) { _player = pl; }

	virtual vector<Enemy*> getVEnemy() { return _vEnemy; }
	virtual vector<Enemy*>::iterator getViEnemy() { return _viEnemy; }
};