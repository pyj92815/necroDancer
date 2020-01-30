#pragma once

// 보스 이미지를 추가하는 클래스
class ADD_BOSS_IMAGE
{
public:
	void add_BossImage()
	{
		// 보스 등장씬 이미지
		IMAGEMANAGER->addImage("deathMetal_Main", "./image/Enemy/boss/bossStageIMG/deathMetal_Main_Image.bmp", 960, 392, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("deathMetal_TopBlade", "./image/Enemy/boss/bossStageIMG/deathMetal_Main_TopBlade.bmp", 602, 68, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("deathMetal_BottomBlade", "./image/Enemy/boss/bossStageIMG/deathMetal_Main_Name.bmp", 728, 96, true, RGB(255, 0, 255));

		// 보스 이미지
		IMAGEMANAGER->addImage("deathMetal_SceneImage", "./image/Enemy/boss/deathMetal_Image.bmp", 960, 398, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("deathMetal_Shield", "./image/Enemy/boss/deathMetal_Shield.bmp", 90, 46, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Death_Metal", "./image/Enemy/boss/death_metal.bmp", 2112, 212, 12, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Boss_Ghost", "./image/Enemy/boss/boss_Ghost.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));

		// 보스의 스킬 이미지
		IMAGEMANAGER->addFrameImage("Boss_Fire_0", "./image/Enemy/boss/boss_Fire_0.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Boss_Fire_1", "./image/Enemy/boss/boss_Fire_1.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Boss_Fire_2", "./image/Enemy/boss/boss_Fire_2.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Boss_Fire_3", "./image/Enemy/boss/boss_Fire_3.bmp", 336, 96, 7, 2, true, RGB(255, 0, 255));

		// 테스트용 이미지
		IMAGEMANAGER->addFrameImage("Test_Heart", "./image/Enemy/boss/beat_heart_test.bmp", 164, 104, 2, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("Test_Floor", "./image/Enemy/boss/floor_test.bmp", 156, 104, 3, 2, true, RGB(255, 0, 255));

		// 보스, 슬레이브 근접 공격 이펙트
		IMAGEMANAGER->addFrameImage("base_Attack", "./image/Enemy/boss/slave/boss_Slave_Attack.bmp", 270, 48, 5, 1, true, RGB(255, 0, 255));
	
		// 보스 체력 이미지
		IMAGEMANAGER->addImage("Boss_Hp_Full", "./image/Enemy/boss/life_Point_Full.bmp", 24, 22, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Boss_Hp_Null", "./image/Enemy/boss/life_Point_Null.bmp", 24, 22, true, RGB(255, 0, 255));
	

	}

	void add_BossAnimation()
	{
		// 실드 있을때 이용하는 애니메이션
		int Left[] = { 2, 3 };
		KEYANIMANAGER->addArrayFrameAnimation("deathMetal_Left", "Death_Metal", Left, 2, 10, true);

		int ShadowLeft[] = { 14, 15 };
		KEYANIMANAGER->addArrayFrameAnimation("deathMetal_SLeft", "Death_Metal", ShadowLeft, 2, 10, true);

		int Up[] = { 6, 7 };
		KEYANIMANAGER->addArrayFrameAnimation("deathMetal_Up", "Death_Metal", Up, 2, 10, true);

		int ShadowUp[] = { 18, 19 };
		KEYANIMANAGER->addArrayFrameAnimation("deathMetal_SUp", "Death_Metal", ShadowUp, 2, 10, true);

		int Right[] = { 0, 1 };
		KEYANIMANAGER->addArrayFrameAnimation("deathMetal_Right", "Death_Metal", Right, 2, 10, true);

		int ShadowRight[] = { 12, 13 };
		KEYANIMANAGER->addArrayFrameAnimation("deathMetal_SRight", "Death_Metal", ShadowRight, 2, 10, true);

		int Down[] = { 4, 5 };
		KEYANIMANAGER->addArrayFrameAnimation("deathMetal_Down", "Death_Metal", Down, 2, 10, true);

		int ShadowDown[] = { 16, 17 };
		KEYANIMANAGER->addArrayFrameAnimation("deathMetal_SDown", "Death_Metal", ShadowDown, 2, 10, true);

		// 실드 없을때 이용하는 애니메이션
		int Attack[] = { 8, 9 };
		KEYANIMANAGER->addArrayFrameAnimation("deathMetal_Attack", "Death_Metal", Attack, 2, 10, true);

		int ShadowAttack[] = { 20, 21 };
		KEYANIMANAGER->addArrayFrameAnimation("deathMetal_SAttack", "Death_Metal", ShadowAttack, 2, 10, true);

		int Idle[] = { 10, 11 };
		KEYANIMANAGER->addArrayFrameAnimation("deathMetal_Idle", "Death_Metal", Idle, 2, 10, true);

		int ShadowIdle[] = { 22, 23 };
		KEYANIMANAGER->addArrayFrameAnimation("deathMetal_SIdle", "Death_Metal", ShadowIdle, 2, 10, true);

		// 보스, 슬레이브 근접 공격 애니메이션
		int baseAtt[] = { 0, 1, 2, 3, 4 };
		KEYANIMANAGER->addArrayFrameAnimation("Base_Attack", "base_Attack", baseAtt, 5, 10, false);
	}
};




// 슬레이브 이미지를 추가하는 클래스
class ADD_SLAVE_IMAGE
{
public:
	void add_SlaveImage()
	{
		// 슬레이브의 이미지를 추가한다.
		IMAGEMANAGER->addFrameImage("boss_Bat", "./image/Enemy/boss/slave/bat/boss_Bat.bmp", 192, 192, 4, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("boss_Ghost", "./image/Enemy/boss/slave/ghost/boss_Ghost.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("boss_Skeleton", "./image/Enemy/boss/slave/skel/boss_Skeleton.bmp", 432, 200, 9, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("boss_Skeleton_Head", "./image/Enemy/boss/slave/skel/boss_Skeleton_Yellow.bmp", 36, 18, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("boss_Skeleton_Yellow", "./image/Enemy/boss/slave/skel/boss_Skeleton_Yellow.bmp", 432, 200, 9, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("boss_Skeleton_Yellow_Head", "./image/Enemy/boss/slave/skel/boss_Skeleton_Yellow_Head.bmp", 36, 18, true, RGB(255, 0, 255));

		// 슬레이브의 공격 이미지를 추가한다.
		IMAGEMANAGER->addFrameImage("boss_Slave_Attack", "./image/Enemy/boss/slave/boss_Slave_Attack.bmp", 270, 48, 5, 1, true, RGB(255, 0, 255));

		// 슬레이브의 그림자 이미지를 추가한다.
		IMAGEMANAGER->addImage("boss_Slave_Shadow", "./image/Enemy/boss/slave/large_shadow.bmp", 43, 14, true, RGB(255, 0, 255));
	};

	void add_SlaveAnimation()
	{
		// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 박쥐 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		// 박쥐 왼쪽 애니메이션 추가
		int bat_Left[] = { 8, 9, 10, 11 };
		KEYANIMANAGER->addArrayFrameAnimation("bat_Left", "boss_Bat", bat_Left, 4, 10, true);

		// 박쥐 쉐도우 왼쪽 애니메이션 추가
		int sBat_Left[] = { 12, 13, 14, 15 };
		KEYANIMANAGER->addArrayFrameAnimation("sBat_Left", "boss_Bat", sBat_Left, 4, 10, true);

		// 박쥐 오른쪽 애니메이션 추가
		int bat_Right[] = { 0, 1, 2, 3 };
		KEYANIMANAGER->addArrayFrameAnimation("bat_Right", "boss_Bat", bat_Right, 4, 10, true);

		// 박쥐 쉐도우 오른쪽 애니메이션 추가
		int sBat_Right[] = { 4, 5, 6, 7 };
		KEYANIMANAGER->addArrayFrameAnimation("sBat_Right", "boss_Bat", sBat_Right, 4, 10, true);



		// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 고스트 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		// 고스트 왼쪽 애니메이션 추가
		int ghost_Left[] = { 0, 1 };
		KEYANIMANAGER->addArrayFrameAnimation("ghost_Left", "boss_Ghost", ghost_Left, 2, 10, true);

		// 고스트 쉐도우 왼쪽 애니메이션 추가
		int sGhost_Left[] = { 2, 3 };
		KEYANIMANAGER->addArrayFrameAnimation("sGhost_Left", "boss_Ghost", sGhost_Left, 2, 10, true);

		// 고스트 오른쪽 애니메이션 추가
		int ghost_Right[] = { 6, 7 };
		KEYANIMANAGER->addArrayFrameAnimation("ghost_Right", "boss_Ghost", ghost_Right, 2, 10, true);

		// 고스트 쉐도우 오른쪽 애니메이션 추가
		int sGhost_Right[] = { 4, 5 };
		KEYANIMANAGER->addArrayFrameAnimation("sGhost_Right", "boss_Ghost", sGhost_Right, 2, 10, true);



		// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 스켈레톤 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		// 스켈레톤 왼쪽 애니메이션 추가
		int skel_Left[] = { 0, 1, 2, 3, 4, 5, 6, 7};
		KEYANIMANAGER->addArrayFrameAnimation("skel_Left", "boss_Skeleton", skel_Left, 8, 10, true);

		// 스켈레톤 쉐도우 왼쪽 애니메이션 추가
		int sSkel_Left[] = { 9, 10, 11, 12, 13, 14, 15, 16};
		KEYANIMANAGER->addArrayFrameAnimation("sSkel_Left", "boss_Skeleton", sSkel_Left, 8, 10, true);

		// 스켈레톤 오른쪽 애니메이션 추가
		int skel_Right[] = {19, 20, 21, 22, 23, 24, 25, 26 };
		KEYANIMANAGER->addArrayFrameAnimation("skel_Right", "boss_Skeleton", skel_Right, 8, 10, true);

		// 스켈레톤 쉐도우 오른쪽 애니메이션 추가
		int sSkel_Right[] = {28, 29, 30, 31, 32, 33, 34, 35 };
		KEYANIMANAGER->addArrayFrameAnimation("sSkel_Right", "boss_Skeleton", sSkel_Right, 8, 10, true);



		// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 스켈레톤(옐로우) ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		// 스켈레톤 옐로우 왼쪽 애니메이션 추가
		int skelY_Left[] = { 0, 1, 2, 3, 4, 5, 6, 7};
		KEYANIMANAGER->addArrayFrameAnimation("skelY_Left", "boss_Skeleton_Yellow", skelY_Left, 8, 10, true);

		// 스켈레톤 옐로우 쉐도우 왼쪽 애니메이션 추가
		int sSkelY_Left[] = { 9, 10, 11, 12, 13, 14, 15, 16};
		KEYANIMANAGER->addArrayFrameAnimation("sSkelY_Left", "boss_Skeleton_Yellow", sSkelY_Left, 8, 10, true);

		// 스켈레톤 옐로우 오른쪽 애니메이션 추가
		int skelY_Right[] = {19, 20, 21, 22, 23, 24, 25, 26 };
		KEYANIMANAGER->addArrayFrameAnimation("skelY_Right", "boss_Skeleton_Yellow", skelY_Right, 8, 10, true);

		// 스켈레톤 옐로우 쉐도우 오른쪽 애니메이션 추가
		int sSkelY_Right[] = {28, 29, 30, 31, 32, 33, 34, 35 };
		KEYANIMANAGER->addArrayFrameAnimation("sSkelY_Right", "boss_Skeleton_Yellow", sSkelY_Right, 8, 10, true);
	};
};