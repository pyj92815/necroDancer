#pragma once
#include"animation.h"
#include"gameNode.h"
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
	Direction parentDirection;
	Direction AttackDirection;			//
	animation* Animation;	
	image* Image;
	animation* attackAnimation;
	image* attackImage;
	int idx, idy;
	float x, y;			
	RECT rc;
	RECT discoveryRc;					//플레이어를 발견할 인식 범위
	int beatCount;						//
	float HP;
	float damage;
	bool Light;							//시야 안에 있는지 여부를 판단하기 위한 bool값
	bool aniChange;						//애니메이션을 바꿨는지 판단하기 위한 bool값
	bool Beat;
	bool Attack;

	bool left;
	bool right;
	bool up;
	bool down;
};
struct playerInfo
{
	float x, y;
	int idx, idy;
};
class Enemy:public gameNode
{
protected:
	EnemyInfo* _enemyInfo;				//에너미 정보(구조체)
	playerInfo* _playerInfo;			//전달받아올 플레이어 정보(구조체) (좌표값만 받아옴)
public:
	Enemy() {};
	~Enemy() {};

	virtual HRESULT init();
	//virtual HRESULT init(int idx, int idy, string enemyName);
	virtual void relase();
	virtual void update();
	virtual void render();

	void AniStart();					//_enemyInfo의 anichange값이 true가 되면 animation의 start()함수를 실행

	virtual void Beat();				//
	virtual void Action();				//enemy의 상태를 바꿔주기 위한 함수
	virtual void Idle();
	virtual void Move();				//enemy의 움직임 패턴을 구현할 함수
	virtual void HalfMove();			//enemy의 벽에 부딪히거나 플레이어와 부딪힐때 절반만 움직이고 제자리로 돌아오는 움직임을 구현할 함수
	virtual void AniChange();			//enemy의 애니메이션을 바꿔주기 위한 함수(원래 update의 넣었지만 Move함수에서 direction을 바꿀 때에만 실행)
	virtual void Attack();				//enemy의 공격을 구현할 함수
	virtual void Die();

	//Enemy생성 함수
	virtual void EnemyCreate(float x, float y, float HP,float damage);
	virtual void EnemyCreate(float x, float y, float HP, float damage,Direction direction);
	virtual void EnemyCreate(float x, float y, float HP, float damage, const char* enemyName, const char* enemyAnimation);
	virtual void EnemyCreate(float x, float y, float HP, float damage, const char* enemyName, const char* enemyAnimation,Direction direction);

	virtual void Hit(float damage) { _enemyInfo->HP -= damage; }

	//virtual void wallCheck()

	//Enemy정보 접근자
	virtual EnemyInfo* getEnemyInfo() { return _enemyInfo; }
	virtual void setPlayerInfo(float x, float y, float idx, float idy) { _playerInfo->idx = idx; _playerInfo->idy = idy; _playerInfo->x = x;_playerInfo->y = y; }
};

