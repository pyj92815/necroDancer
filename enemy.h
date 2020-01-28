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
	enemyState state;					//enemy의 상태를 지정할 enum문
	Direction direction;				//enemy의 방향을 지정할 enum문
	animation* animation;	
	image* image;
	float idx, idy;
	float x, y;			
	RECT rc;
	RECT discoveryRc;					//플레이어를 발견할 인식 범위
	float HP;
	float damage;
	bool Light;							//시야 안에 있는지 여부를 판단하기 위한 bool값
	bool aniChange;						//애니메이션을 바꿨는지 판단하기 위한 bool값
	int beat;							//박자마다 움직이는 enemy의 특성을 위해 박자를  표시할 변수 ex)beat++ if(beat==2){enemy움직임 beat=0;}
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
	
	virtual void Beat();				//Beat의 따라 enemy를 움직이게 하기 위해 관련 연산을 하는 함수
	virtual void Action();				//enemy의 상태를 바꿔주기 위한 함수
	virtual void Move();				//enemy의 움직임 패턴을 구현할 함수
	virtual void AniChange();			//enemy의 애니메이션을 바꿔주기 위한 함수
	virtual void Attack();				//enemy의 공격을 구현할 함수

	//Enemy생성 함수
	virtual void EnemyCreate(float x, float y, float HP,float damage);
	virtual void EnemyCreate(float x, float y, float HP, float damage,Direction direction);
	virtual void EnemyCreate(float x, float y, float HP, float damage, const char* enemyName, const char* enemyAnimation);
	virtual void EnemyCreate(float x, float y, float HP, float damage, const char* enemyName, const char* enemyAnimation,Direction direction);

	virtual void Hit(float damage) { _enemyInfo->HP -= damage; }
	//,시작점,마지막점,시간적 값
	virtual float LinearInterpolation(float value1,float value2,float amount);

	//Enemy정보 접근자
	virtual EnemyInfo* getEnemyInfo() { return _enemyInfo; }

};

