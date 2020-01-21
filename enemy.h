#pragma once
#include"animation.h"
#include"gameNode.h"
#include<vector>
enum class enemyState
{
	STATE_IDLE,STATE_DISCOVERY,STATE_MOVE,STATE_ATTACK,STATE_DIE
};
struct EnemyInfo
{
	enemyState state;
	animation* animation1;
	animation* animation2;
	animation* animation3;
	animation* animation4;
	image* image1;
	image* image2;
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

	//Enemy���� �Լ� (float x, float y, float HP, float damage, const char* enemyName)
	virtual void EnemyCreate(float x, float y, float HP,float damage,const char* enemyName1,const char* enemyName2);

	//Enemy���� ������
	virtual EnemyInfo* getEnemyInfo() { return _enemyInfo; }
};

