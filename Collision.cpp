#include "stdafx.h"
#include "Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::collision_Player_Attack_Enemy(vector<tagTile>* mapInfo, int tileSize, player* playerInfo, Enemy* enemyInfo)
{
	// �÷��̾��� ��ó�� ���ʹ̰� �ִٸ� true�� ������ �ٲ��,
	bool isAttack = false;

	// �÷��̾��� ���⿡ ���� ������ �Ѵ�. (���� + ��ĭ�� ��밡 �ִ��� ã���ش�. ��밡 �ִٸ� true�� ���� ����)
	switch (playerInfo->getDirection())
	{
	case PLAYERDIRECTION_LEFT:
		// �÷��̾��� �ε���x -1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� ���ʿ� ���ʹ̰� �ִٴ� �� 
		if (playerInfo->getPlayer().idx - 1 == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;

	case PLAYERDIRECTION_UP:
		// �÷��̾��� �ε���y -1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� ���ʿ� ���ʹ̰� �ִٴ� ��
		if (playerInfo->getPlayer().idx == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy - 1 == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;

	case PLAYERDIRECTION_RIGHT:
		// �÷��̾��� �ε���x +1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� �����ʿ� ���ʹ̰� �ִٴ� ��
		if (playerInfo->getPlayer().idx + 1 == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;

	case PLAYERDIRECTION_DOWN:
		// �÷��̾��� �ε���y +1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� �Ʒ��ʿ� ���ʹ̰� �ִٴ� ��
		if (playerInfo->getPlayer().idx == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy + 1 == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;
	}

	// ��ó�� ���ʹ̰� �ִٸ� true, �ƴϸ� false
	return isAttack;

	//// ���ʹ̰� �÷��̾�� �ǰ��� ������ ���
	//if (isAttack)
	//{
	//	(*enemyInfo).getEnemyInfo()->HP--;
	//
	//	// ���� true��� ���ʹ��� ü���� 1 ���� ��Ų��. ü���� 0 ���϶�� HP�� 0���� ���� �����ش�.
	//	if ((*enemyInfo).getEnemyInfo()->HP <= 0)
	//	{
	//		(*enemyInfo).getEnemyInfo()->HP = 0;
	//
	//		// ���Ͱ� ü���� 0�̶�� ���� ���Ͱ� �׾��ٴ� ���̴�. �ش� ��ġ�� �ִ� Ÿ�� �Ӽ��� �⺻ Ÿ�Ϸ� �ٲ��ش�.
	//		(*mapInfo)[(*enemyInfo).getEnemyInfo()->x + (*enemyInfo).getEnemyInfo()->y * tileSize].type = TYPE_NONE;
	//	}
	//}

	// �� �Ŀ� �߰��� �ؾ� �ϴ� ��
	// ���Ϳ� Ÿ�Կ� ���� � ���ʹ� Ư�� ��Ȳ�� ���� �Ұ��� ���Ͱ� ����
	// ������ Ÿ�Ե� ������ �ϴ��� �����ؾ���

}

void Collision::collision_Enemy_Attack_Player()
{
	
}

bool Collision::collision_Player_DeathMetal(vector<tagTile>* mapInfo,int tileSize, player* playerInfo, deathMetal* bossInfo)
{
	// ������Ż�� ���� ������ ��ҿ� �÷��̾ �ִٸ� �� ���� true�� �ٲ��.
	bool isAttack = false;

	// ������Ż�� �ٶ󺸴� ���� �ٷ� �տ� �÷��̾ �ִ��� ã���ش�.
	// ã���� �ϴ� �ε����� �÷��̾��� �ε����� ���ٸ� �װ��� �÷��̾ �ִٴ°�
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
		if (bossInfo->getBoss_Index().x  == playerInfo->getPlayer().idx &&
			bossInfo->getBoss_Index().y + 1 == playerInfo->getPlayer().idy)
		{
			isAttack = true;
		}
		break;
	}

	// ��ó�� ���ʹ̰� �ִٸ� true, �ƴϸ� false
	return isAttack;
}

bool Collision::collision_Charactor_Trab(vector<tagTile>* mapInfo, player* playerInfo)
{
	// ������ ã�Ҵٸ� isTrab�� ���� true�� ���Ѵ�.
	bool isTrab = false;

	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// ĳ���Ͱ� ���� Ÿ�Ͽ� ������ �ִٸ� true
		if ((*mapInfo)[i].type == TYPE_TRAP &&
			(*mapInfo)[i].idX == playerInfo->getPlayer().idx &&
			(*mapInfo)[i].idY == playerInfo->getPlayer().idy)
		{
			isTrab = true;
		}

		// Ʈ���� ã�Ҵٸ� for���� ���͵� �ȴ�.
		if (isTrab) break;
	}

	// ������ ã�Ҵٸ� true, �ƴ϶�� false�� ������ �ȴ�.
	return isTrab;

	// ������ ã�� �� �Ŀ� �ؾ� �Ұ�
	// � �������� ã�ƾ� �ϰ�, �� ������ ����� ���� ���Ѿ���
}

bool Collision::collision_Charactor_Trab(vector<tagTile>* mapInfo, Enemy* enemyInfo)
{
	// ������ ã�Ҵٸ� isTrab�� ���� true�� ���Ѵ�.
	bool isTrab = false;

	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// ĳ���Ͱ� ���� Ÿ�Ͽ� ������ �ִٸ� true
		if ((*mapInfo)[i].type == TYPE_TRAP &&
			(*mapInfo)[i].idX == enemyInfo->getEnemyInfo()->x &&
			(*mapInfo)[i].idY == enemyInfo->getEnemyInfo()->y)
		{
			isTrab = true;
		}

		// Ʈ���� ã�Ҵٸ� for���� ���͵� �ȴ�.
		if (isTrab) break;
	}

	// ������ ã�Ҵٸ� true, �ƴ϶�� false�� ������ �ȴ�.
	return isTrab;

	// ������ ã�� �� �Ŀ� �ؾ� �Ұ�
	// � �������� ã�ƾ� �ϰ�, �� ������ ����� ���� ���Ѿ���
}

bool Collision::collision_Charactor_Trab(vector<tagTile>* mapInfo, deathMetal* deathMetalInfo)
{
	// ������ ã�Ҵٸ� isTrab�� ���� true�� ���Ѵ�.
	bool isTrab = false;

	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// ĳ���Ͱ� ���� Ÿ�Ͽ� ������ �ִٸ� true
		if ((*mapInfo)[i].type == TYPE_TRAP &&
			(*mapInfo)[i].idX == deathMetalInfo->getBoss_Index().x &&
			(*mapInfo)[i].idY == deathMetalInfo->getBoss_Index().y)
		{
			isTrab = true;
		}

		// Ʈ���� ã�Ҵٸ� for���� ���͵� �ȴ�.
		if (isTrab) break;
	}

	// ������ ã�Ҵٸ� true, �ƴ϶�� false�� ������ �ȴ�.
	return isTrab;

	// ������ ã�� �� �Ŀ� �ؾ� �Ұ�
	// � �������� ã�ƾ� �ϰ�, �� ������ ����� ���� ���Ѿ���
}

bool Collision::collision_Charactor_Object(vector<tagTile>* mapInfo, player* playerInfo)
{
	bool isObject = false;

	// Ÿ�Ͽ��� ������Ʈ�� �ִ��� ã���ش�. (��, ���� ���)
	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// �÷��̾ �ٶ󺸴� ���⿡ ������Ʈ�� �ִٸ� true�� ���� �ȴ�.
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

		// ������Ʈ�� ã�Ҵٸ� �ݺ����� ������.
		if (isObject) break;
	}
	// ĳ���Ͱ� �̵��ؾ� �ϴ°��� ������Ʈ�� �ִٸ� true ������ false
	return isObject;

	// �߰� �Ϸ���
	// ������Ʈ��� � ������Ʈ����
	// ������Ʈ�� ���������� � ȿ���� �ִ��� ó��?
}

bool Collision::collision_Charactor_Object(vector<tagTile>* mapInfo, Enemy* enemyInfo)
{
	bool isObject = false;

// ���ʹ̴� ���� ������ ����

// ĳ���Ͱ� �̵��ؾ� �ϴ°��� ������Ʈ�� �ִٸ� true ������ false
return isObject;

// �߰� �Ϸ���
// ������Ʈ��� � ������Ʈ����
// ������Ʈ�� ���������� � ȿ���� �ִ��� ó��?
}

bool Collision::collision_Charactor_Object(vector<tagTile>* mapInfo, deathMetal* deathMetalInfo)
{
	bool isObject = false;

	// Ÿ�ϸʿ� ������Ʈ�� �ִ��� ã�´�. (��, ���� ���)
	for (int i = 0; i < mapInfo->size(); ++i)
	{
		// ������Ż�� �ٶ󺸴� ���⿡ ������Ʈ�� �ִٸ� true�� ���� �ȴ�.
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

		// ������Ʈ�� ã������ �ݺ����� ������.
		if (isObject) break;
	}

	// ĳ���Ͱ� �̵��ؾ� �ϴ°��� ������Ʈ�� �ִٸ� true ������ false
	return isObject;

	// �߰� �Ϸ���
	// ������Ʈ��� � ������Ʈ����
	// ������Ʈ�� ���������� � ȿ���� �ִ��� ó��?
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
		if (playerInfo->getPlayer().idx - 1== (*mapInfo)[i]->idX &&
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

map<PLAYERDIRECTION, Enemy*> Collision::collision_player_Enemy_tile(vector<tagTile*>* mapInfo, player* playerInfo, PLAYERWAEPON weapon, Enemy* enemy)
{
	map<PLAYERDIRECTION, Enemy*> _mEnemyTile;
	
	switch (playerInfo->getPlayer().weapon)
	{
	case PLAYERWAEPON_DAGGER:
		break;
	case PLAYERWAEPON_LONGSWORD:
		break;
	case PLAYERWAEPON_RAPIER:
		break;
	case PLAYERWAEPON_SPEAR:
		break;
	case PLAYERWAEPON_NONE:
		break;
	}

	return _mEnemyTile;
}

