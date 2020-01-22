#pragma once
#include"animation.h"
#include"gameNode.h"
#include<vector>
enum class enemyState
{
	STATE_IDLE,STATE_DISCOVERY,STATE_MOVE,STATE_ATTACK,STATE_DIE
};
enum class Direction
{
	LEFT, RIGHT, UP, DOWN
};
struct EnemyInfo
{
	enemyState state;
	Direction direction;
	const char* animation;
	const char* enemyName1;
	const char* enemyName2;
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
	EnemyInfo* _enemyInfo;				//���ʹ� ����(����ü)
	//enemyState _state;
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

	//Enemy���� �Լ� (float x, float y, float HP, float damage, const char* enemyName)
	virtual void EnemyCreate(float x, float y, float HP,float damage,const char* enemyName1,const char* enemyName2);


	//Enemy���� ������
	virtual EnemyInfo* getEnemyInfo() { return _enemyInfo; }

};

