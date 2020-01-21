#pragma once
#include "Collision_Library.h"

class Collision
{


public:
	Collision();
	~Collision();

	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 캐릭터 충돌 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// 플레이어의 1칸 근처에 에너미를 공격한다. (공격력 1)
	// 매개변수 : 맵(벡터), 타일 갯수(X 축), 플레이어 정보, 에너미 정보 
	void collision_Player_Attack_Enemy(vector<tagTile>* mapInfo, int tileSize, player* playerInfo,  Enemy* enemyInfo);

	// 에너미의 1칸 근처에 플레이어를 공격한다. 
	void collision_Enemy_Attack_Player();
	
	// 맵 정보, 플레이어, 보스의 정보를 가져와서 충돌 연산 후 수정을 해준다. (데스메탈)
	void collision_Player_DeathMetal(vector<tagTile>* mapInfo, player* playerInfo, deathMetal* bossInfo);

	// 맵 정보, 플레이어, 함정의 충돌을 연산 후 수정을 해준다.
	void collision_Player_Trab(vector<tagTile>* mapInfo, player* playerInfo);


	//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 오브젝트 충돌 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// 맵 정보, 플레이어 정보를 가져와서 이동 불가능 오브젝트를 연산해준다. (이동 가능 true, 이동 불가능 false 반환)
	void collision_Player_Object(vector<tagTile>* mapInfo, player* playerInfo);

	// 맵 정보, 에너미 정보를 가져와서 이동 불가능 오브젝트를 연산해준다. (이동 가능 true, 이동 불가능 false 반환)
	void collision_Enemy_Object(vector<tagTile>* mapInfo, Enemy* enemyInfo);

	// 맵 정보, 데스메탈 정보를 가져와서 이동 불가능 오브젝트를 연산해준다. (이동 가능 true, 이동 불가능 false 반환)
	void collision_Boss_Object(vector<tagTile>* mapInfo, deathMetal* bossInfo);

};

