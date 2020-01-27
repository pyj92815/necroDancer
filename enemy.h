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
	enemyState state;					//enemy�� ���¸� ������ enum��
	Direction direction;				//enemy�� ������ ������ enum��
	animation* animation;	
	image* image;
	float x, y;			
	RECT rc;
	RECT discoveryRc;					//�÷��̾ �߰��� �ν� ����
	float HP;
	float damage;
	bool Light;							//�þ� �ȿ� �ִ��� ���θ� �Ǵ��ϱ� ���� bool��
	bool aniChange;						//�ִϸ��̼��� �ٲ���� �Ǵ��ϱ� ���� bool��
};

class Enemy:public gameNode
{
protected:
	EnemyInfo* _enemyInfo;				//���ʹ� ����(����ü)
	
public:
	Enemy() {};
	~Enemy() {};

	virtual HRESULT init();
	//virtual HRESULT init(int idx, int idy, string enemyName);
	virtual void relase();
	virtual void update();
	virtual void render();
	
	virtual void Action();				//enemy�� ���¸� �ٲ��ֱ� ���� �Լ�
	virtual void Move();				//enemy�� ������ ������ ������ �Լ�
	virtual void AniChange();			//enemy�� �ִϸ��̼��� �ٲ��ֱ� ���� �Լ�
	virtual void Attack();				//enemy�� ������ ������ �Լ�

	//Enemy���� �Լ� (float x, float y, float HP, float damage, const char* enemyName)
	virtual void EnemyCreate(float x, float y, float HP,float damage);
	virtual void EnemyCreate(float x, float y, float HP, float damage,Direction direction);

	//Enemy���� ������
	virtual EnemyInfo* getEnemyInfo() { return _enemyInfo; }

};

