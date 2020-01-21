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
	// �÷��̾��� ��ó�� ���ʹ̰� �ִٸ� true�� ������ �ٲ��,
	// true�� ���̶�� ���ʹ��� ü���� 1�� ���� �����ش�. �Ǵ� ü���� ���ҽ����ִ� �Լ��� ȣ���Ѵ�.
	bool isAttack = false;

	// �÷��̾��� ���⿡ ���� ������ �Ѵ�. (���� + ��ĭ�� ��밡 �ִ��� ã���ش�. ��밡 �ִٸ� true�� ���� ����)
	switch (playerInfo->getState())
	{
	case PLAYERSTATE_LEFT:
		// �÷��̾��� �ε���x -1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� ���ʿ� ���ʹ̰� �ִٴ� �� 
		if (playerInfo->getPlayer().idx - 1 == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;

	case PLAYERSTATE_UP:
		// �÷��̾��� �ε���y -1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� ���ʿ� ���ʹ̰� �ִٴ� ��
		if (playerInfo->getPlayer().idx == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy - 1 == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;

	case PLAYERSTATE_RIGHT:
		// �÷��̾��� �ε���x +1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� �����ʿ� ���ʹ̰� �ִٴ� ��
		if (playerInfo->getPlayer().idx + 1 == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;

	case PLAYERSTATE_DOWN:
		// �÷��̾��� �ε���y +1�� �� ���� ���ʹ̰� �ִٸ� �÷��̾��� �ٷ� �Ʒ��ʿ� ���ʹ̰� �ִٴ� ��
		if (playerInfo->getPlayer().idx == enemyInfo->getEnemyInfo()->x &&
			playerInfo->getPlayer().idy + 1 == enemyInfo->getEnemyInfo()->y)
		{
			isAttack = true;
		}
		break;
	}

	// ���ʹ̰� �÷��̾�� �ǰ��� ������ ���
	if (isAttack)
	{
		(*enemyInfo).getEnemyInfo()->HP--;

		// ���� true��� ���ʹ��� ü���� 1 ���� ��Ų��. ü���� 0 ���϶�� HP�� 0���� ���� �����ش�.
		if ((*enemyInfo).getEnemyInfo()->HP <= 0)
		{
			(*enemyInfo).getEnemyInfo()->HP = 0;

			// ���Ͱ� ü���� 0�̶�� ���� ���Ͱ� �׾��ٴ� ���̴�. �ش� ��ġ�� �ִ� Ÿ�� �Ӽ��� �⺻ Ÿ�Ϸ� �ٲ��ش�.
			(*mapInfo)[(*enemyInfo).getEnemyInfo()->x + (*enemyInfo).getEnemyInfo()->y * tileSize].type = TYPE_NONE;
		}
	}

	// �� �Ŀ� �߰��� �ؾ� �ϴ� ��
	// ���Ϳ� Ÿ�Կ� ���� � ���ʹ� Ư�� ��Ȳ�� ���� �Ұ��� ���Ͱ� ����
	// ������ Ÿ�Ե� ������ �ϴ��� �����ؾ���

}

void Collision::collision_Enemy_Attack_Player()
{
}

void Collision::collision_Player_DeathMetal(vector<tagTile>* mapInfo, player* playerInfo, deathMetal* bossInfo)
{
	// �÷��̾�� ������Ż�� �浹�� �����Ѵ�.
	// �� �� ���� �� ���� ���� ���� ���ش�.
	// ���� ��ġ�� �ٲ�ų� ���� ��쿡�� ���� ������ ���� ���ش�.

	for (int i = 0; i < mapInfo->size(); ++i)
	{

	}

}

void Collision::collision_Player_Trab(vector<tagTile>* mapInfo, player* playerInfo)
{
	// �÷��̾ ������ �浹 ���� ��츦 �������ش�.
	// �� �� ���� �� ���� ���� ���� ���ش�. 
	// ���� ��ġ�� �ٲ�ų� ���� ��쿡�� ���� ������ �������ش�.

	for (int i = 0; i < mapInfo->size(); ++i)
	{

	}

}

void Collision::collision_Player_Object(vector<tagTile>* mapInfo, player* playerInfo)
{
	// �÷��̾��� ������Ʈ �浹 ������ ���ش�.
	// ���� �̵��� �����ϴٸ� �� �ڸ��� �̵� �����ش�.


}

void Collision::collision_Enemy_Object(vector<tagTile>* mapInfo, Enemy* enemyInfo)
{
	// ���ʹ��� ������Ʈ �浹 ������ ���ش�.
	// ���� �̵��� �����ϴٸ� �� �ڸ��� �̵� �����ش�.


}

void Collision::collision_Boss_Object(vector<tagTile>* mapInfo, deathMetal* bossInfo)
{
	// ������ ������Ʈ �浹 ������ ���ش�.
	// ���� �̵��� �����ϴٸ� �� �ڸ��� �̵� �����ش�.

	
}

