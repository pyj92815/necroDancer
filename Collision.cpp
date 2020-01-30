#include "stdafx.h"
#include "Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::collision_Player_Find_Enemy(player* playerInfo, Enemy* enemyInfo)
{
	// 플레이어의 근처에 에너미가 있다면 true의 값으로 바뀌고,
	bool isAttack = false;

	// 플레이어의 방향에 따라 연산을 한다. (방향 + 한칸에 상대가 있는지 찾아준다. 상대가 있다면 true의 값을 리턴)
	switch (playerInfo->getDirection())
	{
	case PLAYERDIRECTION_LEFT:
		// 플레이어의 인덱스x -1을 한 값에 에너미가 있다면 플레이어의 바로 왼쪽에 에너미가 있다는 뜻 
		if (playerInfo->getPlayer().idx - 1 == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;

	case PLAYERDIRECTION_UP:
		// 플레이어의 인덱스y -1을 한 값에 에너미가 있다면 플레이어의 바로 위쪽에 에너미가 있다는 뜻
		if (playerInfo->getPlayer().idx == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy - 1 == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;

	case PLAYERDIRECTION_RIGHT:
		// 플레이어의 인덱스x +1을 한 값에 에너미가 있다면 플레이어의 바로 오른쪽에 에너미가 있다는 뜻
		if (playerInfo->getPlayer().idx + 1 == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;

	case PLAYERDIRECTION_DOWN:
		// 플레이어의 인덱스y +1을 한 값에 에너미가 있다면 플레이어의 바로 아래쪽에 에너미가 있다는 뜻
		if (playerInfo->getPlayer().idx == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy + 1 == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;
	}

	// 근처에 에너미가 있다면 true, 아니면 false
	return isAttack;

	//// 에너미가 플레이어에게 피격을 당했을 경우
	//if (isAttack)
	//{
	//	(*enemyInfo).getEnemyInfo()->HP--;
	//
	//	// 만약 true라면 에너미의 체력을 1 감소 시킨다. 체력이 0 이하라면 HP는 0으로 고정 시켜준다.
	//	if ((*enemyInfo).getEnemyInfo()->HP <= 0)
	//	{
	//		(*enemyInfo).getEnemyInfo()->HP = 0;
	//
	//		// 몬스터가 체력이 0이라는 뜻은 몬스터가 죽었다는 뜻이다. 해당 위치에 있는 타일 속성을 기본 타일로 바꿔준다.
	//		(*mapInfo)[(*enemyInfo).getEnemyInfo()->x + (*enemyInfo).getEnemyInfo()->y * tileSize].type = TYPE_NONE;
	//	}
	//}

	// 이 후에 추가를 해야 하는 것
	// 몬스터에 타입에 따라 어떤 몬스터는 특정 상황에 공격 불가능 몬스터가 있음
	// 몬스터의 타입도 만들어야 하는지 생각해야함

}

bool Collision::collision_Player_Find_Enamy(player* playerInfo, deathMetal* bossInfo)
{
	// 플레이어의 근처에 데스메탈이 있다면 true의 값으로 바뀌고,
	bool isAttack = false;

	// 플레이어의 방향에 따라 연산을 한다. (방향 + 한칸에 상대가 있는지 찾아준다. 상대가 있다면 true의 값을 리턴)
	switch (playerInfo->getDirection())
	{
	case PLAYERDIRECTION_LEFT:
		// 플레이어의 인덱스x -1을 한 값에 에너미가 있다면 플레이어의 바로 왼쪽에 에너미가 있다는 뜻 
		if (playerInfo->getPlayer().idx - 1 == bossInfo->getBoss_Index().x &&
			playerInfo->getPlayer().idy == bossInfo->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;

	case PLAYERDIRECTION_UP:
		// 플레이어의 인덱스y -1을 한 값에 에너미가 있다면 플레이어의 바로 위쪽에 에너미가 있다는 뜻
		if (playerInfo->getPlayer().idx == bossInfo->getBoss_Index().x &&
			playerInfo->getPlayer().idy - 1 == bossInfo->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;

	case PLAYERDIRECTION_RIGHT:
		// 플레이어의 인덱스x +1을 한 값에 에너미가 있다면 플레이어의 바로 오른쪽에 에너미가 있다는 뜻
		if (playerInfo->getPlayer().idx + 1 == bossInfo->getBoss_Index().x &&
			playerInfo->getPlayer().idy == bossInfo->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;

	case PLAYERDIRECTION_DOWN:
		// 플레이어의 인덱스y +1을 한 값에 에너미가 있다면 플레이어의 바로 아래쪽에 에너미가 있다는 뜻
		if (playerInfo->getPlayer().idx == bossInfo->getBoss_Index().x &&
			playerInfo->getPlayer().idy + 1 == bossInfo->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;
	}

	// 근처에 데스메탈이 있다면 true, 아니면 false
	return isAttack;
}

void Collision::collision_Enemy_Find_Player(player* playerInfo, Enemy* enemyInfo)
{
	// 에너미 방향 정보가 없음
}

bool Collision::collision_DeathMetal_Find_Player(player* playerInfo, deathMetal* bossInfo)
{
	// 데스메탈이 공격 가능한 장소에 플레이어가 있다면 이 값이 true로 바뀐다.
	bool isAttack = false;

	// 데스메탈이 바라보는 방향 바로 앞에 플레이어가 있는지 찾아준다.
	// 찾고자 하는 인덱스와 플레이어의 인덱스가 같다면 그곳에 플레이어가 있다는것
	switch (bossInfo->getBoss_Direction())
	{
	case BD_LEFT:
		if (bossInfo->getBoss_Index().x - 1 == playerInfo->getPlayer().idx &&
			bossInfo->getBoss_Index().y == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;

	case BD_UP:
		if (bossInfo->getBoss_Index().x == playerInfo->getPlayer().idx &&
			bossInfo->getBoss_Index().y - 1 == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;

	case BD_RIGHT:
		if (bossInfo->getBoss_Index().x + 1 == playerInfo->getPlayer().idx &&
			bossInfo->getBoss_Index().y == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;

	case BD_DOWN:
		if (bossInfo->getBoss_Index().x == playerInfo->getPlayer().idx &&
			bossInfo->getBoss_Index().y + 1 == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;
	}

	// 근처에 에너미가 있다면 true, 아니면 false
	return isAttack;
}

bool Collision::collision_DeathMetal_Find_Slave(deathMetal* deathMetal, vector<slave*> _vSlaveList)
{
	// 데스메탈이 공격 가능한 장소에 슬레이브 있다면 이 값이 true로 바뀐다.
	bool isAttack = false;

	// 데스메탈이 바라보는 방향 바로 앞에 슬레이브 있는지 찾아준다.
	// 찾고자 하는 인덱스와 슬레이브의 인덱스가 같다면 그곳에 슬레이브가 있다는것
	for (int i = 0; i < _vSlaveList.size(); ++i)
	{
		switch (deathMetal->getBoss_Direction())
		{
		case BD_LEFT:
			if (deathMetal->getBoss_Index().x - 1 == _vSlaveList[i]->get_Slave()->pos.index.x &&
				deathMetal->getBoss_Index().y == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;
	
		case BD_UP:
			if (deathMetal->getBoss_Index().x  == _vSlaveList[i]->get_Slave()->pos.index.x &&
				deathMetal->getBoss_Index().y - 1 == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;
	
		case BD_RIGHT:
			if (deathMetal->getBoss_Index().x + 1 == _vSlaveList[i]->get_Slave()->pos.index.x &&
				deathMetal->getBoss_Index().y == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;
	
		case BD_DOWN:
			if (deathMetal->getBoss_Index().x == _vSlaveList[i]->get_Slave()->pos.index.x &&
				deathMetal->getBoss_Index().y + 1 == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;
		}
	}

	// 근처에 슬레이브 있다면 true, 아니면 false
	return isAttack;
}

bool Collision::collision_Slave_Find_Player(player* playerInfo, SLAVE_INFO* slave)
{
	// 슬레이브가 공격 가능한 장소에 플레이어가 있다면 이 값이 true로 바뀐다.
	bool isAttack = false;

	// 슬레이브가 바라보는 방향 바로 앞에 플레이어가 있는지 찾아준다.
	// 찾고자 하는 인덱스와 플레이어의 인덱스가 같다면 그곳에 플레이어가 있다는것
	switch (slave->status.direction)
	{
	case SLAVE_DIRECTION::SD_LEFT:
		if (slave->pos.index.x - 1== playerInfo->getPlayer().idx &&
			slave->pos.index.y == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_UP:
		if (slave->pos.index.x == playerInfo->getPlayer().idx &&
			slave->pos.index.y - 1 == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_RIGHT:
		if (slave->pos.index.x + 1 == playerInfo->getPlayer().idx &&
			slave->pos.index.y == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_DOWN:
		if (slave->pos.index.x == playerInfo->getPlayer().idx &&
			slave->pos.index.y + 1 == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;
	}

	// 근처에 에너미가 있다면 true, 아니면 false
	return isAttack;
}

bool Collision::collision_Slave_Find_DeathMetal(deathMetal* deathMetal, SLAVE_INFO* slave)
{
	// 데스메탈이 공격 가능한 장소에 플레이어가 있다면 이 값이 true로 바뀐다.
	bool isAttack = false;

	// 데스메탈이 바라보는 방향 바로 앞에 플레이어가 있는지 찾아준다.
	// 찾고자 하는 인덱스와 플레이어의 인덱스가 같다면 그곳에 플레이어가 있다는것
	switch (slave->status.direction)
	{
	case SLAVE_DIRECTION::SD_LEFT:
		if (slave->pos.index.x - 1 == deathMetal->getBoss_Index().x &&
			slave->pos.index.y == deathMetal->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_UP:
		if (slave->pos.index.x == deathMetal->getBoss_Index().x &&
			slave->pos.index.y - 1 == deathMetal->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_RIGHT:
		if (slave->pos.index.x + 1 == deathMetal->getBoss_Index().x &&
			slave->pos.index.y == deathMetal->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;

	case SLAVE_DIRECTION::SD_DOWN:
		if (slave->pos.index.x == deathMetal->getBoss_Index().x &&
			slave->pos.index.y + 1 == deathMetal->getBoss_Index().y)
		{
			isAttack = true;
		}
		break;
	}

	// 근처에 에너미가 있다면 true, 아니면 false
	return isAttack;
}

bool Collision::collision_Slave_Find_Slave(SLAVE_INFO* _slave, vector<slave*> _vSlaveList)
{
	// 슬레이브가 이동 하는 장소에 슬레이브가 있다면 true로 바뀐다.
	bool isAttack = false;

	// 슬레이브가 바라보는 방향 바로 앞에 슬레이브가 있는지 찾아준다.
	// 찾고자 하는 인덱스와 슬레이브의 인덱스가 같다면 그곳에 슬레이브가 있다는것
	for (int i = 0; i < _vSlaveList.size(); ++i)
	{
		switch (_slave->status.direction)
		{
		case SLAVE_DIRECTION::SD_LEFT:
			if (_slave->pos.index.x - 1 == _vSlaveList[i]->get_Slave()->pos.index.x &&
				_slave->pos.index.y == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;

		case SLAVE_DIRECTION::SD_UP:
			if (_slave->pos.index.x == _vSlaveList[i]->get_Slave()->pos.index.x &&
				_slave->pos.index.y - 1 == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;

		case SLAVE_DIRECTION::SD_RIGHT:
			if (_slave->pos.index.x + 1 == _vSlaveList[i]->get_Slave()->pos.index.x &&
				_slave->pos.index.y == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;

		case SLAVE_DIRECTION::SD_DOWN:
			if (_slave->pos.index.x == _vSlaveList[i]->get_Slave()->pos.index.x &&
				_slave->pos.index.y + 1 == _vSlaveList[i]->get_Slave()->pos.index.y)
			{
				isAttack = true;
			}
			break;
		}
	}

	// 근처에 슬레이브가 있다면 true, 아니면 false
	return isAttack;
}

bool Collision::collision_Charactor_Trab(vector<tagTile>* mapInfo, player* playerInfo)
{
	// 함정을 찾았다면 isTrab의 값이 true로 변한다.
	bool isTrab = false;

	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// 캐릭터가 밟은 타일에 함정이 있다면 true
		if ((*mapInfo)[i].type == TYPE_TRAP &&
			(*mapInfo)[i].idX == playerInfo->getPlayer().idx &&
			(*mapInfo)[i].idY == playerInfo->getPlayer().idy)
		{
			isTrab = true;
		}

		// 트랩을 찾았다면 for문을 나와도 된다.
		if (isTrab) break;
	}

	// 함정을 찾았다면 true, 아니라면 false가 리턴이 된다.
	return isTrab;

	// 함정을 찾고 난 후에 해야 할것
	// 어떤 함정인지 찾아야 하고, 그 함정에 기능을 실행 시켜야함
}

bool Collision::collision_Charactor_Trab(vector<tagTile>* mapInfo, Enemy* enemyInfo)
{
	// 함정을 찾았다면 isTrab의 값이 true로 변한다.
	bool isTrab = false;

	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// 캐릭터가 밟은 타일에 함정이 있다면 true
		if ((*mapInfo)[i].type == TYPE_TRAP &&
			(*mapInfo)[i].idX == enemyInfo->getEnemyInfo()->x &&
			(*mapInfo)[i].idY == enemyInfo->getEnemyInfo()->y)
		{
			isTrab = true;
		}

		// 트랩을 찾았다면 for문을 나와도 된다.
		if (isTrab) break;
	}

	// 함정을 찾았다면 true, 아니라면 false가 리턴이 된다.
	return isTrab;

	// 함정을 찾고 난 후에 해야 할것
	// 어떤 함정인지 찾아야 하고, 그 함정에 기능을 실행 시켜야함
}

bool Collision::collision_Charactor_Trab(vector<tagTile>* mapInfo, deathMetal* deathMetalInfo)
{
	// 함정을 찾았다면 isTrab의 값이 true로 변한다.
	bool isTrab = false;

	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// 캐릭터가 밟은 타일에 함정이 있다면 true
		if ((*mapInfo)[i].type == TYPE_TRAP &&
			(*mapInfo)[i].idX == deathMetalInfo->getBoss_Index().x &&
			(*mapInfo)[i].idY == deathMetalInfo->getBoss_Index().y)
		{
			isTrab = true;
		}

		// 트랩을 찾았다면 for문을 나와도 된다.
		if (isTrab) break;
	}

	// 함정을 찾았다면 true, 아니라면 false가 리턴이 된다.
	return isTrab;

	// 함정을 찾고 난 후에 해야 할것
	// 어떤 함정인지 찾아야 하고, 그 함정에 기능을 실행 시켜야함
}

bool Collision::collision_Charactor_Object(vector<tagTile>* mapInfo, player* playerInfo)
{
	bool isObject = false;

	// 타일에서 오브젝트가 있는지 찾아준다. (벽, 상자 등등)
	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// 플레이어가 바라보는 방향에 오브젝트가 있다면 true의 값이 된다.
		switch (playerInfo->getPlayer().direction)
		{
		case PLAYERDIRECTION_LEFT:
			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
				playerInfo->getPlayer().idx - 1 == (*mapInfo)[i].idX &&
				playerInfo->getPlayer().idy == (*mapInfo)[i].idY)
			{
				isObject = true;
			}
			break;

		case PLAYERDIRECTION_UP:
			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
				playerInfo->getPlayer().idx == (*mapInfo)[i].idX &&
				playerInfo->getPlayer().idy - 1 == (*mapInfo)[i].idY)
			{
				isObject = true;
			}
			break;

		case PLAYERDIRECTION_RIGHT:
			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
				playerInfo->getPlayer().idx + 1 == (*mapInfo)[i].idX &&
				playerInfo->getPlayer().idy == (*mapInfo)[i].idY)
			{
				isObject = true;
			}
			break;

		case PLAYERDIRECTION_DOWN:
			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
				playerInfo->getPlayer().idx == (*mapInfo)[i].idX &&
				playerInfo->getPlayer().idy + 1 == (*mapInfo)[i].idY)
			{
				isObject = true;
			}
			break;
		}

		// 오브젝트를 찾았다면 반복문을 나간다.
		if (isObject) break;
	}
	// 캐릭터가 이동해야 하는곳에 오브젝트가 있다면 true 없으면 false
	return isObject;

	// 추가 하려면
	// 오브젝트라면 어떤 오브젝트인지
	// 오브젝트가 정해졌으면 어떤 효과가 있는지 처리?
}

bool Collision::collision_Charactor_Object(vector<tagTile>* mapInfo, Enemy* enemyInfo)
{
	bool isObject = false;

	// 에너미는 방향 정보가 없음

	// 캐릭터가 이동해야 하는곳에 오브젝트가 있다면 true 없으면 false
	return isObject;

	// 추가 하려면
	// 오브젝트라면 어떤 오브젝트인지
	// 오브젝트가 정해졌으면 어떤 효과가 있는지 처리?
}

bool Collision::collision_Charactor_Object(vector<tagTile>* mapInfo, deathMetal* deathMetalInfo)
{
	bool isObject = false;

	// 타일맵에 오브젝트가 있는지 찾는다. (벽, 상자 등등)
	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// 데스메탈이 바라보는 방향에 오브젝트가 있다면 true의 값이 된다.
		switch (deathMetalInfo->getBoss_Direction())
		{
		case BD_LEFT:
			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
				deathMetalInfo->getBoss_Index().x - 1 == (*mapInfo)[i].idX &&
				deathMetalInfo->getBoss_Index().y == (*mapInfo)[i].idY)
			{
				isObject = true;
			}
			break;

		case BD_UP:
			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
				deathMetalInfo->getBoss_Index().x == (*mapInfo)[i].idX &&
				deathMetalInfo->getBoss_Index().y - 1 == (*mapInfo)[i].idY)
			{
				isObject = true;
			}
			break;

		case BD_RIGHT:
			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
				deathMetalInfo->getBoss_Index().x + 1 == (*mapInfo)[i].idX &&
				deathMetalInfo->getBoss_Index().y == (*mapInfo)[i].idY)
			{
				isObject = true;
			}
			break;

		case BD_DOWN:
			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
				deathMetalInfo->getBoss_Index().x == (*mapInfo)[i].idX &&
				deathMetalInfo->getBoss_Index().y + 1 == (*mapInfo)[i].idY)
			{
				isObject = true;
			}
			break;
		}

		// 오브젝트를 찾았으면 반복문을 나간다.
		if (isObject) break;
	}

	// 캐릭터가 이동해야 하는곳에 오브젝트가 있다면 true 없으면 false
	return isObject;

	// 추가 하려면
	// 오브젝트라면 어떤 오브젝트인지
	// 오브젝트가 정해졌으면 어떤 효과가 있는지 처리?
}

bool Collision::collision_Charactor_Object(vector<tagTile>* mapInfo, SLAVE_INFO* slave)
{
	bool isObject = false;

	// 타일맵에 오브젝트가 있는지 찾는다. (벽, 상자 등등)
	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// 데스메탈이 바라보는 방향에 오브젝트가 있다면 true의 값이 된다.
		switch (slave->status.direction)
		{
		case SLAVE_DIRECTION::SD_LEFT:
			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
				slave->pos.index.x - 1 == (*mapInfo)[i].idX &&
				slave->pos.index.y == (*mapInfo)[i].idY)
			{
				isObject = true;
			}
			break;

		case SLAVE_DIRECTION::SD_UP:
			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
				slave->pos.index.x == (*mapInfo)[i].idX &&
				slave->pos.index.y - 1 == (*mapInfo)[i].idY)
			{
				isObject = true;
			}
			break;

		case SLAVE_DIRECTION::SD_RIGHT:
			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
				slave->pos.index.x + 1 == (*mapInfo)[i].idX &&
				slave->pos.index.y == (*mapInfo)[i].idY)
			{
				isObject = true;
			}
			break;

		case SLAVE_DIRECTION::SD_DOWN:
			if ((*mapInfo)[i].type == TYPE_OBJECT || (*mapInfo)[i].type == TYPE_WALL &&
				slave->pos.index.x == (*mapInfo)[i].idX &&
				slave->pos.index.y + 1 == (*mapInfo)[i].idY)
			{
				isObject = true;
			}
			break;
		}

		// 오브젝트를 찾았으면 반복문을 나간다.
		if (isObject) break;
	}

	// 캐릭터가 이동해야 하는곳에 오브젝트가 있다면 true 없으면 false
	return isObject;
}

map<PLAYERDIRECTION, tagTile*> Collision::collision_player_tile(vector<tagTile*>* mapInfo, player* playerInfo)
{
	map<PLAYERDIRECTION, tagTile*> _mPlayerTile;

	for (int i = 0; i < mapInfo->size(); ++i)
	{
		if (playerInfo->getPlayer().idx == (*mapInfo)[i]->idX &&
			playerInfo->getPlayer().idy - 1 == (*mapInfo)[i]->idY)
		{
			_mPlayerTile.emplace(pair<PLAYERDIRECTION, tagTile*>(PLAYERDIRECTION_UP, (*mapInfo)[i]));
			continue;
		}
		if (playerInfo->getPlayer().idx == (*mapInfo)[i]->idX &&
			playerInfo->getPlayer().idy + 1 == (*mapInfo)[i]->idY)
		{
			_mPlayerTile.emplace(pair<PLAYERDIRECTION, tagTile*>(PLAYERDIRECTION_DOWN, (*mapInfo)[i]));
			continue;
		}
		if (playerInfo->getPlayer().idx - 1 == (*mapInfo)[i]->idX &&
			playerInfo->getPlayer().idy == (*mapInfo)[i]->idY)
		{
			_mPlayerTile.emplace(pair<PLAYERDIRECTION, tagTile*>(PLAYERDIRECTION_LEFT, (*mapInfo)[i]));
			continue;
		}
		if (playerInfo->getPlayer().idx + 1 == (*mapInfo)[i]->idX &&
			playerInfo->getPlayer().idy == (*mapInfo)[i]->idY)
		{
			_mPlayerTile.emplace(pair<PLAYERDIRECTION, tagTile*>(PLAYERDIRECTION_RIGHT, (*mapInfo)[i]));
			continue;
		}
	}

	return _mPlayerTile;
}

map<PLAYERDIRECTION, Enemy*> Collision::collision_player_Enemy_tile(vector<Enemy*>* enemyInfo, player* playerInfo)
{
	map<PLAYERDIRECTION, Enemy*> _mEnemy;
	
	switch (playerInfo->getPlayer().weapon)
	{
	case PLAYERWAEPON_NONE:
	case PLAYERWAEPON_DAGGER:
		// 몬스터 for문을 돌린다
		for (int i = 0; i < enemyInfo->size(); ++i)
		{
			if (0 > enemyInfo->size()) break; // 몬스터가 없으면 끝 
			//상
			if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy - 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_UP, (*enemyInfo)[i]));
			}//하
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy + 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_DOWN, (*enemyInfo)[i]));
			}//좌
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx - 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_LEFT, (*enemyInfo)[i]));
			}//우
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx + 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_RIGHT, (*enemyInfo)[i]));
			}
		}// 끝
		return _mEnemy;
		break;
	case PLAYERWAEPON_LONGSWORD:
	case PLAYERWAEPON_RAPIER:
	case PLAYERWAEPON_SPEAR:
		// 몬스터 for문을 돌린다
		for (int i = 0; i < enemyInfo->size(); ++i)
		{
			//상
			if (((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy - 1) ||
				((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
					&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy - 2))
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_UP, (*enemyInfo)[i]));
			}//하
			else if (((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy + 1) ||
				((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
					&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy + 2))
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_DOWN, (*enemyInfo)[i]));
			}//좌
			else if (((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx - 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy) ||
				((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx - 2
					&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy))
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_LEFT, (*enemyInfo)[i]));
			}//우
			else if (((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx + 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy) ||
				((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx + 2
					&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy))
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_RIGHT, (*enemyInfo)[i]));
			}
		}// 끝
		return _mEnemy;
		break;
	case PLAYERWAEPON_BROADSWORD:
		// 몬스터 for문을 돌린다
		for (int i = 0; i < enemyInfo->size(); ++i)
		{
			//상
			if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy - 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_UP, (*enemyInfo)[i]));
			}//하
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy + 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_DOWN, (*enemyInfo)[i]));
			}//좌
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx - 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_LEFT, (*enemyInfo)[i]));
			}//우
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx + 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_RIGHT, (*enemyInfo)[i]));
			}// 대각 상좌
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx - 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy - 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_UP, (*enemyInfo)[i]));
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_LEFT, (*enemyInfo)[i]));
			}// 대각 상우
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx + 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy - 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_UP, (*enemyInfo)[i]));
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_RIGHT, (*enemyInfo)[i]));
			}// 대각 하좌
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx - 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy + 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION,Enemy*>(PLAYERDIRECTION_DOWN, (*enemyInfo)[i]));
				_mEnemy.insert(pair<PLAYERDIRECTION,Enemy*>(PLAYERDIRECTION_LEFT, (*enemyInfo)[i]));
			}// 대각 하우
			else if ((*enemyInfo)[i]->getEnemyInfo()->idx == playerInfo->getPlayer().idx + 1
				&& (*enemyInfo)[i]->getEnemyInfo()->idy == playerInfo->getPlayer().idy + 1)
			{
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_DOWN, (*enemyInfo)[i]));
				_mEnemy.insert(pair<PLAYERDIRECTION, Enemy*>(PLAYERDIRECTION_RIGHT, (*enemyInfo)[i]));
			}

		}// 끝
		return _mEnemy;
		break;
	}
	// 몬스터 충돌 처리 한후 전달하기 

	return _mEnemy;
}

