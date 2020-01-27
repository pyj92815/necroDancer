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
	bool collision_Player_Attack_Enemy(vector<tagTile>* mapInfo, int tileSize, player* playerInfo, Enemy* enemyInfo);

	// ���ʹ��� 1ĭ ��ó�� �÷��̾ �����Ѵ�. (���ʹ̴� �����̰� �߰� �ϵ��� �ϼ���~)
	void collision_Enemy_Attack_Player();

	// ������Ż�� 1ĭ ��ó�� �÷��̾ �ִٸ� true, ���ٸ� false�� ��ȯ�Ѵ�.
	// �Ű����� : ��(����), Ÿ�� ����(X ��), �÷��̾� ����, ���ʹ� ���� 
	bool collision_Player_DeathMetal(vector<tagTile>* mapInfo, int tileSize, player* playerInfo, deathMetal* bossInfo);

	// �� ����, �÷��̾�, ������ �浹�� ���� �� ������ ���ش�.
	// ĳ���Ͱ� ���� Ÿ�Ͽ� ������ �ִٸ� true, ���ٸ� false�� ��ȯ�Ѵ�. (ĳ���Ͷ�? �÷��̾�, ���ʹ�, ���� ��� ����)
	// �Ű����� : ��(����), ĳ���� ����
	bool collision_Charactor_Trab(vector<tagTile>* mapInfo, player* playerInfo);
	bool collision_Charactor_Trab(vector<tagTile>* mapInfo, Enemy* enemyInfo);	
	bool collision_Charactor_Trab(vector<tagTile>* mapInfo, deathMetal* deathMetalInfo);


	//������������������������������������������ ������Ʈ �浹 ������������������������������������������������
	// �� ����, ĳ���� ������ �����ͼ� �̵� �Ұ��� ������Ʈ�� �������ش�. (�̵� ���� true, �̵� �Ұ��� false ��ȯ)
	bool collision_Charactor_Object(vector<tagTile>* mapInfo, player* playerInfo);

	// �� ����, ĳ���� ������ �����ͼ� �̵� �Ұ��� ������Ʈ�� �������ش�. (�̵� ���� true, �̵� �Ұ��� false ��ȯ)
	bool collision_Charactor_Object(vector<tagTile>* mapInfo, Enemy* enemyInfo);

	// �� ����, ĳ���� ������ �����ͼ� �̵� �Ұ��� ������Ʈ�� �������ش�. (�̵� ���� true, �̵� �Ұ��� false ��ȯ)
	bool collision_Charactor_Object(vector<tagTile>* mapInfo, deathMetal* deathMetalInfo);

};

