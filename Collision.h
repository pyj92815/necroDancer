#pragma once
#include "Collision_Library.h"

class Collision
{


public:
	Collision();
	~Collision();

	/////////////////////////////////////////// 캐릭터 충돌 ///////////////////////////////////////////////

	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 캐릭터 충돌 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// 플레이어의 1칸 근처에 에너미가 있다면 true, 없다면 false를 반환한다.
	// 매개변수 : 맵(벡터), 타일 갯수(X 축), 플레이어 정보, 에너미 정보 
	bool collision_Player_Attack_Enemy(vector<tagTile>* mapInfo, int tileSize, player* playerInfo, Enemy* enemyInfo);

	// 에너미의 1칸 근처에 플레이어를 공격한다. (에너미는 대훈이가 추가 하도록 하세요~)
	void collision_Enemy_Attack_Player();

	// 데스메탈의 1칸 근처에 플레이어가 있다면 true, 없다면 false를 반환한다.
	// 매개변수 : 맵(벡터), 타일 갯수(X 축), 플레이어 정보, 에너미 정보 
	bool collision_Player_DeathMetal(vector<tagTile>* mapInfo, int tileSize, player* playerInfo, deathMetal* bossInfo);

	// 맵 정보, 플레이어, 함정의 충돌을 연산 후 수정을 해준다.
	// 캐릭터가 밟은 타일에 함정이 있다면 true, 없다면 false를 반환한다. (캐릭터란? 플레이어, 에너미, 보스 모두 포함)
	// 매개변수 : 맵(벡터), 캐릭터 정보
	bool collision_Charactor_Trab(vector<tagTile>* mapInfo, player* playerInfo);
	bool collision_Charactor_Trab(vector<tagTile>* mapInfo, Enemy* enemyInfo);	
	bool collision_Charactor_Trab(vector<tagTile>* mapInfo, deathMetal* deathMetalInfo);


	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 오브젝트 충돌 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// 맵 정보, 캐릭터 정보를 가져와서 이동 불가능 오브젝트를 연산해준다. (이동 가능 true, 이동 불가능 false 반환)
	bool collision_Charactor_Object(vector<tagTile>* mapInfo, player* playerInfo);

	// 맵 정보, 캐릭터 정보를 가져와서 이동 불가능 오브젝트를 연산해준다. (이동 가능 true, 이동 불가능 false 반환)
	bool collision_Charactor_Object(vector<tagTile>* mapInfo, Enemy* enemyInfo);

	// 맵 정보, 캐릭터 정보를 가져와서 이동 불가능 오브젝트를 연산해준다. (이동 가능 true, 이동 불가능 false 반환)
	bool collision_Charactor_Object(vector<tagTile>* mapInfo, deathMetal* deathMetalInfo);

};

