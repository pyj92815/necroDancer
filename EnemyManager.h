#pragma once
#include"gameNode.h"
#include"Enemy_Dragon.h"
#include"Enemy_Ghost.h"
#include"Enemy_Skeleton.h"
#include"Enemy_Skeleton_Yellow.h"
#include"Enemy_Slime_Blue.h"
#include"Enemy_Slime_Orange.h"
#include"Enemy_Warith.h"
#include<vector>

class player;

enum class EnemyType
{
	BAT,DRAGON,GHOST,MINOTAUR,SKELETON,SKELETON_YELLOW,SLIME_BLUE,SLIME_ORANGE,WRAITH,ZOMBIE

	//
	/*CHAR_BAT,
	CHAR_SLIME_BLUE, CHAR_SLIME_ORANGE,
	CHAR_GHOST, CHAR_WRAITH,
	CHAR_SKELETON, CHAR_SKELETON_YELLOW, CHAR_ZOMBIE,
	CHAR_MINO, CHAR_DRAGON, CHAR_BOSS,
	CHAR_NONE,*/
};

class EnemyManager :public gameNode
{
private:
	vector<Enemy*> _vEnemy;
	vector<Enemy*>::iterator _viEnemy;
	vector<tagTile*> _vTile;
	vector<tagTile*>::iterator _viTile;

	EnemyType _enemyType;

	player* _player;

	// 몬스터 위치 생성 
	map<CHARACTER, POINT>		   	_mEnemyPoint;
	map<CHARACTER, POINT>::iterator _miEnemyPoint;


public:
	EnemyManager() {};
	~EnemyManager() {};

	HRESULT init(map<CHARACTER, POINT> mEnemyPount);
	void release();
	void update();
	void render();
	
	void WallInspection();
	void Attack();
	void EnemyRemove();

	void EnemyInspection();	
	void EnemyCreate();

	void Enemy_Dragon_Create(float x, float y);
	void Enemy_Ghost_Create(float x, float y);
	void Enemy_Skeleton_Create(float x, float y);
	void Enemy_Skeleton_Yellow_Create(float x, float y);
	void Enemy_Slime_Blue_Create(float x, float y);
	void Enemy_Slime_Orange_Create(float x, float y);
	void Enemy_Wraith_Create(float x, float y);


	//이미지 추가 함수
	void imageAdd();
	void AnimationAdd();

	void AddressLink(player* pl) { _player = pl; }


	vector<Enemy*> getVEnemy() { return _vEnemy; }
	vector<Enemy*>::iterator getViEnemy() { return _viEnemy; }

	void setVtile(vector<tagTile*> tile);

	virtual vector<Enemy*> getVEnemy() { return _vEnemy; }
	virtual vector<Enemy*>::iterator getViEnemy() { return _viEnemy; }

};