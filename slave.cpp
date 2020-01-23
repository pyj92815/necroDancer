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
	addSlaveImage();		// 슬레이브의 이미지 추가 함수
	addSlaveAnimation();	// 슬레이브의 애니메이션 추가 함수

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
	// 슬레이브의 이미지를 추가한다.
	IMAGEMANAGER->addFrameImage("boss_Bat", "./image/Enemy/boss/slave/bat/boss_Bat.bmp", 192, 192, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_Ghost", "./image/Enemy/boss/slave/ghost/boss_Ghost.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_Skeleton", "./image/Enemy/boss/slave/skel/boss_Skeleton.bmp", 432, 200, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss_Skeleton_Head", "./image/Enemy/boss/slave/skel/boss_Skeleton_Yellow.bmp", 36, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_Skeleton_Yellow", "./image/Enemy/sleva/skel/boss_Skeleton_Yellow.bmp", 432, 200, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("boss_Skeleton_Yellow_Head", "./image/Enemy/slave/skel/boss_Skeleton_Yellow_Head.bmp", 36, 18, true, RGB(255, 0, 255));

	// 슬레이브의 공격 이미지를 추가한다.
	IMAGEMANAGER->addFrameImage("boss_Slave_Attack", "./image/Enemy/boss/slave/boss_Slave_Attack.bmp", 270, 48, 5, 1, true, RGB(255, 0, 255));

	// 슬레이브의 그림자 이미지를 추가한다.
	IMAGEMANAGER->addImage("boss_Slave_Shadow", "./image/Enemy/boss/slave/large_shadow.bmp", 43, 14, true, RGB(255, 0, 255));
}

void slave::addSlaveAnimation()
{
	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 박쥐 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// 박쥐 왼쪽 애니메이션 추가
	int bat_Left[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("bat_Left", "boss_Bat", bat_Left, 4, 10, true);

	// 박쥐 쉐도우 왼쪽 애니메이션 추가
	int sBat_Left[] = { 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("sBat_Left", "boss_Bat", sBat_Left, 4, 10, true);

	// 박쥐 오른쪽 애니메이션 추가
	int bat_Right[] = { 8, 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("bat_Right", "boss_Bat", bat_Right, 4, 10, true);

	// 박쥐 쉐도우 오른쪽 애니메이션 추가
	int sBat_Right[] = { 12, 13, 14, 15 };
	KEYANIMANAGER->addArrayFrameAnimation("sBat_Right", "boss_Bat", sBat_Right, 4, 10, true);



	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 고스트 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// 고스트 왼쪽 애니메이션 추가
	int ghost_Left[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("ghost_Left", "boss_Ghost", ghost_Left, 2, 10, true);

	// 고스트 쉐도우 왼쪽 애니메이션 추가
	int sGhost_Left[] = { 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("sGhost_Left", "boss_Ghost", sGhost_Left, 2, 10, true);

	// 고스트 오른쪽 애니메이션 추가
	int ghost_Right[] = { 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("ghost_Right", "boss_Ghost", ghost_Right, 2, 10, true);

	// 고스트 쉐도우 오른쪽 애니메이션 추가
	int sGhost_Right[] = { 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("sGhost_Right", "boss_Ghost", sGhost_Right, 2, 10, true);



	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 스켈레톤 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// 스켈레톤 왼쪽 애니메이션 추가
	int skel_Left[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("skel_Left", "boss_Skeleton", skel_Left, 9, 10, true);

	// 스켈레톤 쉐도우 왼쪽 애니메이션 추가
	int sSkel_Left[] = { 9, 10, 11, 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("sSkel_Left", "boss_Skeleton", sSkel_Left, 9, 10, true);

	// 스켈레톤 오른쪽 애니메이션 추가
	int skel_Right[] = { 18, 19, 20, 21, 22, 23, 24, 25, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("skel_Right", "boss_Skeleton", skel_Right, 9, 10, true);

	// 스켈레톤 쉐도우 오른쪽 애니메이션 추가
	int sSkel_Right[] = { 27, 28, 29, 30, 31, 32, 33, 34, 35 };
	KEYANIMANAGER->addArrayFrameAnimation("sSkel_Right", "boss_Skeleton", sSkel_Right, 9, 10, true);



	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 스켈레톤(옐로우) ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// 스켈레톤 옐로우 왼쪽 애니메이션 추가
	int skelY_Left[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("skel_Left", "boss_Skeleton_Yellow", skelY_Left, 9, 10, true);

	// 스켈레톤 옐로우 쉐도우 왼쪽 애니메이션 추가
	int sSkelY_Left[] = { 9, 10, 11, 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("sSkel_Left", "boss_Skeleton_Yellow", sSkelY_Left, 9, 10, true);

	// 스켈레톤 옐로우 오른쪽 애니메이션 추가
	int skelY_Right[] = { 18, 19, 20, 21, 22, 23, 24, 25, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("skel_Right", "boss_Skeleton_Yellow", skelY_Right, 9, 10, true);

	// 스켈레톤 옐로우 쉐도우 오른쪽 애니메이션 추가
	int sSkelY_Right[] = { 27, 28, 29, 30, 31, 32, 33, 34, 35 };
	KEYANIMANAGER->addArrayFrameAnimation("sSkel_Right", "boss_Skeleton_Yellow", sSkelY_Right, 9, 10, true);
}
