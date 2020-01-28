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
	bool collision_Player_Find_Enemy(player* playerInfo, Enemy* enemyInfo);

	// 플레이어의 1칸 근처에 데스메탈이 있다면 true, 없다면 false를 반환한다.
	// 매개변수 : 맵(벡터), 타일 갯수(x 축), 플레이어 정보, 데스메탈 정보
	bool collision_Player_Find_Enamy(player* playerInfo, deathMetal* bossInfo);

	// 에너미의 1칸 근처에 플레이어를 공격한다. (에너미는 대훈이가 추가 하도록 하세요~)
	// 매개변수 : 맵(벡터_, 타일 갯수(x 축), 플레이어 정보, 에너미 정보
	void collision_Enemy_Find_Player(player* playerInfo, Enemy* enemyInfo);

	// 데스메탈의 1칸 근처에 플레이어가 있다면 true, 없다면 false를 반환한다.
	// 매개변수 : 맵(벡터), 타일 갯수(X 축), 플레이어 정보, 에너미 정보 
	bool collision_DeathMetal_Find_Player(player* playerInfo, deathMetal* bossInfo);


	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 함정 충돌 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// 맵 정보, 플레이어, 함정의 충돌을 연산 후 수정을 해준다.
	// 캐릭터가 밟은 타일에 함정이 있다면 true, 없다면 false를 반환한다. (캐릭터란? 플레이어, 에너미, 보스 모두 포함)
	// 매개변수 : 맵(벡터), 캐릭터 정보
	bool collision_Charactor_Trab(vector<tagTile>* mapInfo, player* playerInfo);
	bool collision_Charactor_Trab(vector<tagTile>* mapInfo, Enemy* enemyInfo);
	bool collision_Charactor_Trab(vector<tagTile>* mapInfo, deathMetal* deathMetalInfo);


	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 오브젝트 충돌 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// 맵 정보, 플레이어 정보를 가져와서 이동 불가능 오브젝트를 연산해준다. (이동 가능 true, 이동 불가능 false 반환)
	bool collision_Charactor_Object(vector<tagTile>* mapInfo, player* playerInfo);

	// 맵 정보, 에너미 정보를 가져와서 이동 불가능 오브젝트를 연산해준다. (이동 가능 true, 이동 불가능 false 반환)
	bool collision_Charactor_Object(vector<tagTile>* mapInfo, Enemy* enemyInfo);

	// 맵 정보, 데스메탈 정보를 가져와서 이동 불가능 오브젝트를 연산해준다. (이동 가능 true, 이동 불가능 false 반환)
	bool collision_Charactor_Object(vector<tagTile>* mapInfo, deathMetal* deathMetalInfo);

	//락훈추가
	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 플레이어 타일 충돌 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

	//하나로
	map<PLAYERDIRECTION, tagTile*>  collision_player_tile(vector<tagTile*>* mapInfo, player* playerInfo);

	map<PLAYERDIRECTION, Enemy*>  collision_player_Enemy_tile(vector<tagTile*>* mapInfo, player* playerInfo, PLAYERWAEPON weapon, Enemy* enemy);


};

