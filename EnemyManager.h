#pragma once
#include"gameNode.h"
#include"Enemy_Bat.h"
#include"Enemy_Boss.h"
#include"Enemy_Dragon.h"
#include"Enemy_Ghost.h"
#include"Enemy_Minotaur.h"
#include"Enemy_Skeleton.h"
#include"Enemy_Skeleton_Yellow.h"
#include"Enemy_Slime_Blue.h"
#include"Enemy_Slime_Orange.h"
#include"Enemy_Warith.h"
#include"Enemy_Zombie.h"
#include<vector>

enum class EnemyType
{
	BAT,DRAGON,GHOST,MINOTAUR,SKELETON,SKELETON_YELLOW,SLIME_BLUE,SLIME_ORANGE,WRAITH,ZOMBIE,DEATH_METAL
};

class EnemyManager :public gameNode
{
private:
	vector<Enemy*> _vEnemy;
	vector<Enemy*>::iterator _viEnemy;

	EnemyType _enemyType;


public:
	EnemyManager() {};
	~EnemyManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void EnemyCreate(float x, float y, EnemyType enemyType);

	void Enemy_Bat_Create(float x, float y);
	void Enemy_Dragon_Create(float x, float y);
	void Enemy_Ghost_Create(float x, float y);
	void Enemy_Minotaur_Create(float x, float y);
	void Enemy_Skeleton_Create(float x, float y);
	void Enemy_Skeleton_Yellow_Create(float x, float y);
	void Enemy_Slime_Blue_Create(float x, float y);
	void Enemy_Slime_Orange_Create(float x, float y);
	void Enemy_Wraith_Create(float x, float y);
	void Enemy_Zombie_Create(float x, float y);
	void Enemy_Death_Metal_Create(float x, float y);

	//이미지 추가 함수
	void imageAdd();
	void AnimationAdd();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 데스메탈 패턴
	// 기본으로 보호막이 달려있음.
	// 처음 슬레이브는 고스트 4마리
	// 고스트는 플레이어가 바라보면 투명해지면서 무적상태 이동하지 않음
	// 플레이어가 바라보고 있지 않으면 따라온다.
	// 고스트를 모두 죽이면 슬레이브 소환으로 박쥐가 나온다. 4마리
	// 박쥐는 랜덤으로 이동하고, 근처에 플레이어가 있으면 공격
	// 박쥐가 모두 죽고 슬레이브 소환으로 해골이 나온다. 2마리 소환
	// 해골은 플레이어를 a*로 따라오고, 손을 들고 그 다음에 공격을 한다.
	// 머리가 없어지면 플레이어에게 멀어지는 이동을 시작함
	// 데스메탈에 캐스팅 중에 피격을 당하면 캐스팅이 취소된다.
	// 데스메탈의 체력이 4칸으로 떨어지면 초록색 해골을 소환한다.
	// 데스메탈의 마법 공격에 적도 피해를 입는다. (팀킬 가능)
	// 체력 9칸
	// 보호막은 공격 2대에 깨짐
	// 보호막이 깨지기 전까지는 전방 공격에 데미지를 입지 않는다.
	// 보호막이 있을때는 보호막 들고 있는 이미지 4종류 (왼, 위, 오, 아래)
	// 보호막이 사라지면 데스메탈의 프레임 이미지는 2개 (대기, 손들기)
	// 일정 체력 이하에선 플레이어에게 맞았을때 텔레포트
	// 데스메탈은 손을 들면서 이상한 소리를 외치고 4틱 후에 내리면서 슬레이브를 소환한다.
	// 슬레이브는 랜덤? (유령, 해골)
	// 데스메탈은 손을 들면서 이상한 소리를 외치고 4틱 후에 파이어볼
	// 체력이 없을때는 플레이어에게서 멀어지면서 파이어볼만 쏨
	// 체력
	// 슬레이브 소환(고스트, 박쥐, 해골, 노란해골)
	// 보호막
	// 파이어볼
	// 텔레포트
	// 피격 시 캐스팅 취소
	// 
};