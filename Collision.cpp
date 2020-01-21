#include "stdafx.h"
#include "Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

void Collision::collision_Player_Attack_Enemy(vector<tagTile>* mapInfo, int tileSize, player* playerInfo, Enemy* enemyInfo)
{
	// 플레이어의 근처에 에너미가 있다면 true의 값으로 바뀌고,
	// true의 값이라면 에너미의 체력을 1을 감소 시켜준다. 또는 체력을 감소시켜주는 함수를 호출한다.
	bool isAttack = false;

	// 플레이어의 방향에 따라 연산을 한다. (방향 + 한칸에 상대가 있는지 찾아준다. 상대가 있다면 true의 값을 리턴)
	switch (playerInfo->getState())
	{
	case PLAYERSTATE_LEFT:
		// 플레이어의 인덱스x -1을 한 값에 에너미가 있다면 플레이어의 바로 왼쪽에 에너미가 있다는 뜻 
		if (playerInfo->getPlayer().idx - 1 == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;

	case PLAYERSTATE_UP:
		// 플레이어의 인덱스y -1을 한 값에 에너미가 있다면 플레이어의 바로 위쪽에 에너미가 있다는 뜻
		if (playerInfo->getPlayer().idx == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy - 1 == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;

	case PLAYERSTATE_RIGHT:
		// 플레이어의 인덱스x +1을 한 값에 에너미가 있다면 플레이어의 바로 오른쪽에 에너미가 있다는 뜻
		if (playerInfo->getPlayer().idx + 1 == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;

	case PLAYERSTATE_DOWN:
		// 플레이어의 인덱스y +1을 한 값에 에너미가 있다면 플레이어의 바로 아래쪽에 에너미가 있다는 뜻
		if (playerInfo->getPlayer().idx == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy + 1 == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;
	}

	// 에너미가 플레이어에게 피격을 당했을 경우
	if (isAttack)
	{
		(*enemyInfo).getEnemyInfo()->HP--;

		// 만약 true라면 에너미의 체력을 1 감소 시킨다. 체력이 0 이하라면 HP는 0으로 고정 시켜준다.
		if ((*enemyInfo).getEnemyInfo()->HP <= 0)
		{
			(*enemyInfo).getEnemyInfo()->HP = 0;

			// 몬스터가 체력이 0이라는 뜻은 몬스터가 죽었다는 뜻이다. 해당 위치에 있는 타일 속성을 기본 타일로 바꿔준다.
			(*mapInfo)[(*enemyInfo).getEnemyInfo()->x + (*enemyInfo).getEnemyInfo()->y * tileSize].type = TYPE_NONE;
		}
	}

	// 이 후에 추가를 해야 하는 것
	// 몬스터에 타입에 따라 어떤 몬스터는 특정 상황에 공격 불가능 몬스터가 있음
	// 몬스터의 타입도 만들어야 하는지 생각해야함

}

void Collision::collision_Enemy_Attack_Player()
{
}

void Collision::collision_Player_DeathMetal(vector<tagTile>* mapInfo, player* playerInfo, deathMetal* bossInfo)
{
	// 플레이어와 데스메탈의 충돌을 연산한다.
	// 그 후 변경 된 값을 각각 갱신 해준다.
	// 만약 위치가 바뀌거나 했을 경우에는 맵의 정보도 갱신 해준다.

	for (int i = 0; i < mapInfo->size(); ++i)
	{

	}

}

void Collision::collision_Player_Trab(vector<tagTile>* mapInfo, player* playerInfo)
{
	// 플레이어가 함정과 충돌 했을 경우를 연산해준다.
	// 그 후 변경 된 값을 각각 갱신 해준다. 
	// 만약 위치가 바뀌거나 했을 경우에는 맵의 정보도 갱신해준다.

	for (int i = 0; i < mapInfo->size(); ++i)
	{

	}

}

void Collision::collision_Player_Object(vector<tagTile>* mapInfo, player* playerInfo)
{
	// 플레이어의 오브젝트 충돌 연산을 해준다.
	// 만약 이동이 가능하다면 그 자리로 이동 시켜준다.


}

void Collision::collision_Enemy_Object(vector<tagTile>* mapInfo, Enemy* enemyInfo)
{
	// 에너미의 오브젝트 충돌 연산을 해준다.
	// 만약 이동이 가능하다면 그 자리로 이동 시켜준다.


}

void Collision::collision_Boss_Object(vector<tagTile>* mapInfo, deathMetal* bossInfo)
{
	// 보스의 오브젝트 충돌 연산을 해준다.
	// 만약 이동이 가능하다면 그 자리로 이동 시켜준다.

	
}

