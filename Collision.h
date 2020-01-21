#pragma once
#include "Collision_Library.h"

class Collision
{


public:
	Collision();
	~Collision();

	//������������������������������������������ ĳ���� �浹 ������������������������������������������������
	// �÷��̾��� 1ĭ ��ó�� ���ʹ̸� �����Ѵ�. (���ݷ� 1)
	// �Ű����� : ��(����), Ÿ�� ����(X ��), �÷��̾� ����, ���ʹ� ���� 
	void collision_Player_Attack_Enemy(vector<tagTile>* mapInfo, int tileSize, player* playerInfo,  Enemy* enemyInfo);

	// ���ʹ��� 1ĭ ��ó�� �÷��̾ �����Ѵ�. 
	void collision_Enemy_Attack_Player();
	
	// �� ����, �÷��̾�, ������ ������ �����ͼ� �浹 ���� �� ������ ���ش�. (������Ż)
	void collision_Player_DeathMetal(vector<tagTile>* mapInfo, player* playerInfo, deathMetal* bossInfo);

	// �� ����, �÷��̾�, ������ �浹�� ���� �� ������ ���ش�.
	void collision_Player_Trab(vector<tagTile>* mapInfo, player* playerInfo);


	//������������������������������������������ ������Ʈ �浹 ������������������������������������������������
	// �� ����, �÷��̾� ������ �����ͼ� �̵� �Ұ��� ������Ʈ�� �������ش�. (�̵� ���� true, �̵� �Ұ��� false ��ȯ)
	void collision_Player_Object(vector<tagTile>* mapInfo, player* playerInfo);

	// �� ����, ���ʹ� ������ �����ͼ� �̵� �Ұ��� ������Ʈ�� �������ش�. (�̵� ���� true, �̵� �Ұ��� false ��ȯ)
	void collision_Enemy_Object(vector<tagTile>* mapInfo, Enemy* enemyInfo);

	// �� ����, ������Ż ������ �����ͼ� �̵� �Ұ��� ������Ʈ�� �������ش�. (�̵� ���� true, �̵� �Ұ��� false ��ȯ)
	void collision_Boss_Object(vector<tagTile>* mapInfo, deathMetal* bossInfo);

};

