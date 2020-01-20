#pragma once
#include"animation.h"
#include"gameNode.h"
#include<vector>

struct EnemyInfo
{
	animation* animation;
	image* image;
	float x, y;
	RECT rc;
	float HP;
	float damage;
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

	//Enemy생성 함수 (float x, float y, float HP, float damage, const char* enemyName)
	virtual void EnemyCreate(float x, float y, float HP,float damage,const char* enemyName);

	//Enemy정보 접근자
	virtual EnemyInfo* getVEnemyInfo() { return _enemyInfo; }
};

