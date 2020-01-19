#pragma once
#include"gameNode.h"
#include"Enemy_Bat.h"
#include"Enemy_Boss.h"
#include"Enemy_Dragon.h"
#include"Enemy_Ghost.h"
#include"Enemy_Minotaur.h"
#include"Enemy_Skeleton.h"
#include"Enemy_Skeleton_Yellow.h"
#include"Enemy_Slime_Blue.h"
#include"Enemy_Slime_Orange.h"
#include"Enemy_Warith.h"
#include"Enemy_Zombie.h"
#include<vector>

enum class EnemyType
{
	BAT,DRAGON,GHOST,MINOTAUR,SKELETON,SKELETON_YELLOW,SLIME_BLUE,SLIME_ORANGE,WRAITH,ZOMBIE,DEATH_METAL
};

class EnemyManager :public gameNode
{
private:
	vector<Enemy*> _vEnemy;
	vector<Enemy*>::iterator _viEnemy;

	EnemyType _enemyType;


public:
	EnemyManager() {};
	~EnemyManager() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void EnemyCreate(float x, float y, EnemyType enemyType);

	void Enemy_Bat_Create(float x, float y);
	void Enemy_Dragon_Create(float x, float y);
	void Enemy_Ghost_Create(float x, float y);
	void Enemy_Minotaur_Create(float x, float y);
	void Enemy_Skeleton_Create(float x, float y);
	void Enemy_Skeleton_Yellow_Create(float x, float y);
	void Enemy_Slime_Blue_Create(float x, float y);
	void Enemy_Slime_Orange_Create(float x, float y);
	void Enemy_Wraith_Create(float x, float y);
	void Enemy_Zombie_Create(float x, float y);
	void Enemy_Death_Metal_Create(float x, float y);

	//�̹��� �߰� �Լ�
	void imageAdd();
	void AnimationAdd();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ������Ż ����
	// �⺻���� ��ȣ���� �޷�����.
	// ó�� �����̺�� ��Ʈ 4����
	// ��Ʈ�� �÷��̾ �ٶ󺸸� ���������鼭 �������� �̵����� ����
	// �÷��̾ �ٶ󺸰� ���� ������ ����´�.
	// ��Ʈ�� ��� ���̸� �����̺� ��ȯ���� ���㰡 ���´�. 4����
	// ����� �������� �̵��ϰ�, ��ó�� �÷��̾ ������ ����
	// ���㰡 ��� �װ� �����̺� ��ȯ���� �ذ��� ���´�. 2���� ��ȯ
	// �ذ��� �÷��̾ a*�� �������, ���� ��� �� ������ ������ �Ѵ�.
	// �Ӹ��� �������� �÷��̾�� �־����� �̵��� ������
	// ������Ż�� ĳ���� �߿� �ǰ��� ���ϸ� ĳ������ ��ҵȴ�.
	// ������Ż�� ü���� 4ĭ���� �������� �ʷϻ� �ذ��� ��ȯ�Ѵ�.
	// ������Ż�� ���� ���ݿ� ���� ���ظ� �Դ´�. (��ų ����)
	// ü�� 9ĭ
	// ��ȣ���� ���� 2�뿡 ����
	// ��ȣ���� ������ �������� ���� ���ݿ� �������� ���� �ʴ´�.
	// ��ȣ���� �������� ��ȣ�� ��� �ִ� �̹��� 4���� (��, ��, ��, �Ʒ�)
	// ��ȣ���� ������� ������Ż�� ������ �̹����� 2�� (���, �յ��)
	// ���� ü�� ���Ͽ��� �÷��̾�� �¾����� �ڷ���Ʈ
	// ������Ż�� ���� ��鼭 �̻��� �Ҹ��� ��ġ�� 4ƽ �Ŀ� �����鼭 �����̺긦 ��ȯ�Ѵ�.
	// �����̺�� ����? (����, �ذ�)
	// ������Ż�� ���� ��鼭 �̻��� �Ҹ��� ��ġ�� 4ƽ �Ŀ� ���̾
	// ü���� �������� �÷��̾�Լ� �־����鼭 ���̾�� ��
	// ü��
	// �����̺� ��ȯ(��Ʈ, ����, �ذ�, ����ذ�)
	// ��ȣ��
	// ���̾
	// �ڷ���Ʈ
	// �ǰ� �� ĳ���� ���
	// 
};