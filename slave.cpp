#include "stdafx.h"
#include "slave.h"

slave::slave()
{
}

slave::~slave()
{
}

HRESULT slave::init()
{
	addSlaveImage();		// �����̺��� �̹��� �߰� �Լ�
	addSlaveAnimation();	// �����̺��� �ִϸ��̼� �߰� �Լ�

	return S_OK;
}

void slave::release()
{
}

void slave::update()
{
}

void slave::render()
{
}

void slave::addSlaveImage()
{
	// �����̺��� �̹����� �߰��Ѵ�.
	IMAGEMANAGER->addFrameImage("boss_Bat", "./image/Enemy/boss/slave/bat/boss_Bat.bmp", 192, 192, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_Ghost", "./image/Enemy/boss/slave/ghost/boss_Ghost.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_Skeleton", "./image/Enemy/boss/slave/skel/boss_Skeleton.bmp", 432, 200, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss_Skeleton_Head", "./image/Enemy/boss/slave/skel/boss_Skeleton_Yellow.bmp", 36, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_Skeleton_Yellow", "./image/Enemy/sleva/skel/boss_Skeleton_Yellow.bmp", 432, 200, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss_Skeleton_Yellow_Head", "./image/Enemy/slave/skel/boss_Skeleton_Yellow_Head.bmp", 36, 18, true, RGB(255, 0, 255));

	// �����̺��� ���� �̹����� �߰��Ѵ�.
	IMAGEMANAGER->addFrameImage("boss_Slave_Attack", "./image/Enemy/boss/slave/boss_Slave_Attack.bmp", 270, 48, 5, 1, true, RGB(255, 0, 255));

	// �����̺��� �׸��� �̹����� �߰��Ѵ�.
	IMAGEMANAGER->addImage("boss_Slave_Shadow", "./image/Enemy/boss/slave/large_shadow.bmp", 43, 14, true, RGB(255, 0, 255));
}

void slave::addSlaveAnimation()
{
	// ������������������������������������ ���� ��������������������������������������������
	// ���� ���� �ִϸ��̼� �߰�
	int bat_Left[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("bat_Left", "boss_Bat", bat_Left, 4, 10, true);

	// ���� ������ ���� �ִϸ��̼� �߰�
	int sBat_Left[] = { 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("sBat_Left", "boss_Bat", sBat_Left, 4, 10, true);

	// ���� ������ �ִϸ��̼� �߰�
	int bat_Right[] = { 8, 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("bat_Right", "boss_Bat", bat_Right, 4, 10, true);

	// ���� ������ ������ �ִϸ��̼� �߰�
	int sBat_Right[] = { 12, 13, 14, 15 };
	KEYANIMANAGER->addArrayFrameAnimation("sBat_Right", "boss_Bat", sBat_Right, 4, 10, true);



	// ������������������������������������� ��Ʈ �������������������������������������������
	// ��Ʈ ���� �ִϸ��̼� �߰�
	int ghost_Left[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("ghost_Left", "boss_Ghost", ghost_Left, 2, 10, true);

	// ��Ʈ ������ ���� �ִϸ��̼� �߰�
	int sGhost_Left[] = { 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("sGhost_Left", "boss_Ghost", sGhost_Left, 2, 10, true);

	// ��Ʈ ������ �ִϸ��̼� �߰�
	int ghost_Right[] = { 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("ghost_Right", "boss_Ghost", ghost_Right, 2, 10, true);

	// ��Ʈ ������ ������ �ִϸ��̼� �߰�
	int sGhost_Right[] = { 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("sGhost_Right", "boss_Ghost", sGhost_Right, 2, 10, true);



	// ������������������������������������� ���̷��� �����������������������������������������
	// ���̷��� ���� �ִϸ��̼� �߰�
	int skel_Left[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("skel_Left", "boss_Skeleton", skel_Left, 9, 10, true);

	// ���̷��� ������ ���� �ִϸ��̼� �߰�
	int sSkel_Left[] = { 9, 10, 11, 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("sSkel_Left", "boss_Skeleton", sSkel_Left, 9, 10, true);

	// ���̷��� ������ �ִϸ��̼� �߰�
	int skel_Right[] = { 18, 19, 20, 21, 22, 23, 24, 25, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("skel_Right", "boss_Skeleton", skel_Right, 9, 10, true);

	// ���̷��� ������ ������ �ִϸ��̼� �߰�
	int sSkel_Right[] = { 27, 28, 29, 30, 31, 32, 33, 34, 35 };
	KEYANIMANAGER->addArrayFrameAnimation("sSkel_Right", "boss_Skeleton", sSkel_Right, 9, 10, true);



	// ��������������������������������� ���̷���(���ο�) ��������������������������������������
	// ���̷��� ���ο� ���� �ִϸ��̼� �߰�
	int skelY_Left[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("skel_Left", "boss_Skeleton_Yellow", skelY_Left, 9, 10, true);

	// ���̷��� ���ο� ������ ���� �ִϸ��̼� �߰�
	int sSkelY_Left[] = { 9, 10, 11, 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("sSkel_Left", "boss_Skeleton_Yellow", sSkelY_Left, 9, 10, true);

	// ���̷��� ���ο� ������ �ִϸ��̼� �߰�
	int skelY_Right[] = { 18, 19, 20, 21, 22, 23, 24, 25, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("skel_Right", "boss_Skeleton_Yellow", skelY_Right, 9, 10, true);

	// ���̷��� ���ο� ������ ������ �ִϸ��̼� �߰�
	int sSkelY_Right[] = { 27, 28, 29, 30, 31, 32, 33, 34, 35 };
	KEYANIMANAGER->addArrayFrameAnimation("sSkel_Right", "boss_Skeleton_Yellow", sSkelY_Right, 9, 10, true);
}
