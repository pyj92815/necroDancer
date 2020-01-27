#pragma once
#include"animation.h"
#include"gameNode.h"
#include<vector>
enum class enemyState
{
	STATE_IDLE,STATE_MOVE,STATE_ATTACK,STATE_DIE
};
enum class Direction
{
	LEFT, RIGHT, UP, DOWN
};
struct EnemyInfo
{
	enemyState state;
	Direction direction;
	animation* animation;
	image* image;
	float x, y;
	RECT rc;
	RECT discoveryRc;
	float HP;
	float damage;
	bool Light;
};

class Enemy:public gameNode
{
protected:
	EnemyInfo* _enemyInfo;				//에너미 정보(구조체)
	
public:
	Enemy() {};
	~Enemy() {};

	virtual HRESULT init();
	//virtual HRESULT init(int idx, int idy, string enemyName);
	virtual void relase();
	virtual void update();
	virtual void render();
	
	virtual void Action();
	virtual void Move();
	virtual void AniChange();
	virtual void Attack();

	//Enemy생성 함수 (float x, float y, float HP, float damage, const char* enemyName)
	virtual void EnemyCreate(float x, float y, float HP,float damage);
	virtual void EnemyCreate(float x, float y, float HP, float damage,Direction direction);

	//Enemy정보 접근자
	virtual EnemyInfo* getEnemyInfo() { return _enemyInfo; }

};

