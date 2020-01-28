#pragma once
#include "Collision_Library.h"

class Collision
{


public:
	Collision();
	~Collision();

	/////////////////////////////////////////// ĳ���� �浹 ///////////////////////////////////////////////

	//������������������������������������������ ĳ���� �浹 ������������������������������������������������
	// �÷��̾��� 1ĭ ��ó�� ���ʹ̰� �ִٸ� true, ���ٸ� false�� ��ȯ�Ѵ�.
	// �Ű����� : ��(����), Ÿ�� ����(X ��), �÷��̾� ����, ���ʹ� ���� 
	bool collision_Player_Find_Enemy(player* playerInfo, Enemy* enemyInfo);

	// �÷��̾��� 1ĭ ��ó�� ������Ż�� �ִٸ� true, ���ٸ� false�� ��ȯ�Ѵ�.
	// �Ű����� : ��(����), Ÿ�� ����(x ��), �÷��̾� ����, ������Ż ����
	bool collision_Player_Find_Enamy(player* playerInfo, deathMetal* bossInfo);

	// ���ʹ��� 1ĭ ��ó�� �÷��̾ �����Ѵ�. (���ʹ̴� �����̰� �߰� �ϵ��� �ϼ���~)
	// �Ű����� : ��(����_, Ÿ�� ����(x ��), �÷��̾� ����, ���ʹ� ����
	void collision_Enemy_Find_Player(player* playerInfo, Enemy* enemyInfo);

	// ������Ż�� 1ĭ ��ó�� �÷��̾ �ִٸ� true, ���ٸ� false�� ��ȯ�Ѵ�.
	// �Ű����� : ��(����), Ÿ�� ����(X ��), �÷��̾� ����, ���ʹ� ���� 
	bool collision_DeathMetal_Find_Player(player* playerInfo, deathMetal* bossInfo);


	//������������������������������������������ ���� �浹 ������������������������������������������������
	// �� ����, �÷��̾�, ������ �浹�� ���� �� ������ ���ش�.
	// ĳ���Ͱ� ���� Ÿ�Ͽ� ������ �ִٸ� true, ���ٸ� false�� ��ȯ�Ѵ�. (ĳ���Ͷ�? �÷��̾�, ���ʹ�, ���� ��� ����)
	// �Ű����� : ��(����), ĳ���� ����
	bool collision_Charactor_Trab(vector<tagTile>* mapInfo, player* playerInfo);
	bool collision_Charactor_Trab(vector<tagTile>* mapInfo, Enemy* enemyInfo);
	bool collision_Charactor_Trab(vector<tagTile>* mapInfo, deathMetal* deathMetalInfo);


	//������������������������������������������ ������Ʈ �浹 ������������������������������������������������
	// �� ����, �÷��̾� ������ �����ͼ� �̵� �Ұ��� ������Ʈ�� �������ش�. (�̵� ���� true, �̵� �Ұ��� false ��ȯ)
	bool collision_Charactor_Object(vector<tagTile>* mapInfo, player* playerInfo);

	// �� ����, ���ʹ� ������ �����ͼ� �̵� �Ұ��� ������Ʈ�� �������ش�. (�̵� ���� true, �̵� �Ұ��� false ��ȯ)
	bool collision_Charactor_Object(vector<tagTile>* mapInfo, Enemy* enemyInfo);

	// �� ����, ������Ż ������ �����ͼ� �̵� �Ұ��� ������Ʈ�� �������ش�. (�̵� ���� true, �̵� �Ұ��� false ��ȯ)
	bool collision_Charactor_Object(vector<tagTile>* mapInfo, deathMetal* deathMetalInfo);

	//�����߰�
	//������������������������������������������ �÷��̾� Ÿ�� �浹 ������������������������������������������������

	//�ϳ���
	map<PLAYERDIRECTION, tagTile*>  collision_player_tile(vector<tagTile*>* mapInfo, player* playerInfo);

	map<PLAYERDIRECTION, Enemy*>  collision_player_Enemy_tile(vector<tagTile*>* mapInfo, player* playerInfo, PLAYERWAEPON weapon, Enemy* enemy);


};

