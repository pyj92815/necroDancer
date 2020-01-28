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
	float idx, idy;
	float x, y;			
	RECT rc;
	RECT discoveryRc;					//�÷��̾ �߰��� �ν� ����
	float HP;
	float damage;
	bool Light;							//�þ� �ȿ� �ִ��� ���θ� �Ǵ��ϱ� ���� bool��
	bool aniChange;						//�ִϸ��̼��� �ٲ���� �Ǵ��ϱ� ���� bool��
	int beat;							//���ڸ��� �����̴� enemy�� Ư���� ���� ���ڸ�  ǥ���� ���� ex)beat++ if(beat==2){enemy������ beat=0;}
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
	
	virtual void Beat();				//Beat�� ���� enemy�� �����̰� �ϱ� ���� ���� ������ �ϴ� �Լ�
	virtual void Action();				//enemy�� ���¸� �ٲ��ֱ� ���� �Լ�
	virtual void Move();				//enemy�� ������ ������ ������ �Լ�
	virtual void AniChange();			//enemy�� �ִϸ��̼��� �ٲ��ֱ� ���� �Լ�
	virtual void Attack();				//enemy�� ������ ������ �Լ�

	//Enemy���� �Լ�
	virtual void EnemyCreate(float x, float y, float HP,float damage);
	virtual void EnemyCreate(float x, float y, float HP, float damage,Direction direction);
	virtual void EnemyCreate(float x, float y, float HP, float damage, const char* enemyName, const char* enemyAnimation);
	virtual void EnemyCreate(float x, float y, float HP, float damage, const char* enemyName, const char* enemyAnimation,Direction direction);

	virtual void Hit(float damage) { _enemyInfo->HP -= damage; }
	//,������,��������,�ð��� ��
	virtual float LinearInterpolation(float value1,float value2,float amount);

	//Enemy���� ������
	virtual EnemyInfo* getEnemyInfo() { return _enemyInfo; }

};

