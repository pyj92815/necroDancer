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
	void imageAdd()
	{
		IMAGEMANAGER->addFrameImage("Enemy_bat", "./image./Enemy/bat.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_dragon", "./image./Enemy/dragon.bmp", 216, 204, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_ghost", "./image./Enemy/ghost.bmp", 48 * 2, 48 * 2, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_minotaur", "./image./Enemy/minotaur.bmp", 450 * 2, 98 * 2, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_skeleton", "./image./Enemy/skeleton.bmp", 192 * 2, 50 * 2, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_skeleton_yellow", "./image./Enemy/skeleton_yellow.bmp", 216 * 2, 50 * 2, 9, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_slime_blue", "./image./Enemy/slime_blue.bmp", 208 * 2, 50 * 2, 8, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_slime_orange", "./image./Enemy/slime_orange.bmp", 104 * 2, 52 * 2, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_wraith", "./image./Enemy/wraith.bmp", 72 * 2, 48 * 2, 3, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Enemy_zombie", "./image./Enemy/zombie.bmp", 576 * 2, 50 * 2, 24, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Boss_Image", "./image/Enemy/boss/boss_Image.bmp", 960, 398, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Boss_Shield", "./image/Enemy/boss/boss_Shield.bmp", 90, 46, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Death_Metal", "./image/Enemy/boss/death_metal.bmp", 2112, 212, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Boss_Ghost", "./image/Enemy/boss/boss_Ghost.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Boss_Fire_0", "./image/Enemy/boss/boss_Fire_0.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Boss_Fire_1", "./image/Enemy/boss/boss_Fire_1.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Boss_Fire_2", "./image/Enemy/boss/boss_Fire_2.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Boss_Fire_3", "./image/Enemy/boss/boss_Fire_3.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));
	}



	


























































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