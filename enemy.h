#pragma once
#include"animation.h"
#include"gameNode.h"
#include<vector>
enum class state
{
	STATE_IDLE,STATE_DISCOVERY,STATE_MOVE,STATE_ATTACK,STATE_DIE,
};
struct EnemyInfo
{
	animation* animation1;
	animation* animation2;
	animation* animation3;
	animation* animation4;
	image* image1;
	image* image2;
	float x, y;
	RECT rc;
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

	//Enemy생성 함수 (float x, float y, float HP, float damage, const char* enemyName)
	virtual void EnemyCreate(float x, float y, float HP,float damage,const char* enemyName1,const char* enemyName2);

	//Enemy정보 접근자
	virtual EnemyInfo* getVEnemyInfo() { return _enemyInfo; }
};

