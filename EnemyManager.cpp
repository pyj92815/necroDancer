#include "stdafx.h"
#include "EnemyManager.h"

HRESULT EnemyManager::init()
{
	imageAdd();	//이미지 추가 함수
	Enemy* enemy;
	enemy = new Enemy_Bat;
	enemy->init();
	_vEnemy.push_back(enemy);
	for (_viEnemy = _vEnemy.begin();_viEnemy != _vEnemy.end();++_viEnemy)
	{
		(*_viEnemy)->init();
	}
	return S_OK;
}

void EnemyManager::release()
{
}

void EnemyManager::update()
{
	for (_viEnemy = _vEnemy.begin();_viEnemy != _vEnemy.end();++_viEnemy)
	{
		(*_viEnemy)->update();
	}
}

void EnemyManager::render()
{
	for (_viEnemy = _vEnemy.begin();_viEnemy != _vEnemy.end();++_viEnemy)
	{
		(*_viEnemy)->render();
	}
}

void EnemyManager::EnemyCreate(float x, float y,EnemyType enemyType)
{
	switch (_enemyType)
	{
	case EnemyType::BAT:
		Enemy_Bat_Create(x,y);
		break;
	case EnemyType::DRAGON:
		Enemy_Dragon_Create(x, y);
		break;
	case EnemyType::GHOST:
		Enemy_Ghost_Create(x,y);
		break;
	case EnemyType::MINOTAUR:
		Enemy_Minotaur_Create(x, y);
		break;
	case EnemyType::SKELETON:
		Enemy_Skeleton_Create(x, y);
		break;
	case EnemyType::SKELETON_YELLOW:
		Enemy_Skeleton_Yellow_Create(x, y);
		break;
	case EnemyType::SLIME_BLUE:
		Enemy_Slime_Blue_Create(x, y);
		break;
	case EnemyType::SLIME_ORANGE:
		Enemy_Slime_Orange_Create(x, y);
		break;
	case EnemyType::WRAITH:
		Enemy_Wraith_Create(x, y);
		break;
	case EnemyType::ZOMBIE:
		Enemy_Zombie_Create(x, y);
		break;
	default:
		break;
	}
}

void EnemyManager::Enemy_Bat_Create(float x, float y)
{
	Enemy* Bat;
	Bat = new Enemy_Bat;
	Bat->EnemyCreate(x, y, 1.0f, 0.5f,"Enemy_bat");
	_vEnemy.push_back(Bat);
}
void EnemyManager::Enemy_Dragon_Create(float x, float y)
{
	Enemy* Dragon;
	Dragon = new Enemy_Dragon;
	Dragon->EnemyCreate(x, y, 4.0f, 2.0f, "Enemy_dragon");
	_vEnemy.push_back(Dragon);
}
void EnemyManager::Enemy_Ghost_Create(float x, float y)
{
	Enemy* Ghost;
	Ghost = new Enemy_Ghost;
	Ghost->EnemyCreate(x, y, 1.0f, 1.0f, "Enemy_ghost");
	_vEnemy.push_back(Ghost);
}
void EnemyManager::Enemy_Minotaur_Create(float x, float y)
{
	Enemy* Minotaur;
	Minotaur = new Enemy_Minotaur;
	Minotaur->EnemyCreate(x, y, 3.0f, 2.0f, "Enemy_minotaur");
	_vEnemy.push_back(Minotaur);
}
void EnemyManager::Enemy_Skeleton_Create(float x, float y)
{
	Enemy* Skeleton;
	Skeleton = new Enemy_Skeleton;
	Skeleton->EnemyCreate(x, y, 1.0f, 0.5f, "Enemy_skeleton");
	_vEnemy.push_back(Skeleton);
}
void EnemyManager::Enemy_Skeleton_Yellow_Create(float x, float y)
{
	Enemy* Skeleton_Yellow;
	Skeleton_Yellow = new Enemy_Skeleton_Yellow;
	Skeleton_Yellow->EnemyCreate(x, y, 2.0f, 1.5f, "Enemy_skeleton_yellow");
	_vEnemy.push_back(Skeleton_Yellow);
}
void EnemyManager::Enemy_Slime_Blue_Create(float x, float y)
{
	Enemy* Slime_Blue;
	Slime_Blue = new Enemy_Slime_Blue;
	Slime_Blue->EnemyCreate(x, y, 2.0f, 1.0f, "Enemy_slime_blue");
	_vEnemy.push_back(Slime_Blue);
}
void EnemyManager::Enemy_Slime_Orange_Create(float x, float y)
{
	Enemy* Slime_Orange;
	Slime_Orange = new Enemy_Slime_Orange;
	Slime_Orange->EnemyCreate(x, y, 1.0f, 0.5f, "Enemy_slime_orange");
	_vEnemy.push_back(Slime_Orange);
}
void EnemyManager::Enemy_Wraith_Create(float x, float y)
{
	Enemy* Wraith;
	Wraith = new Enemy_Warith;
	Wraith->EnemyCreate(x, y, 1.0f, 0.5f, "Enemy_wraith");
	_vEnemy.push_back(Wraith);
}
void EnemyManager::Enemy_Zombie_Create(float x, float y)
{
	Enemy* Zombie;
	Zombie = new Enemy_Zombie;
	Zombie->EnemyCreate(x, y, 1.0f, 1.0f, "Enemy_zombie");
	_vEnemy.push_back(Zombie);
}

void EnemyManager::imageAdd()
{
	IMAGEMANAGER->addFrameImage("Enemy_batL", "./image./Enemy/batL.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_batR", "./image./Enemy/batR.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_dragonL","./image./Enemy/dragonL.bmp", 216, 204, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_dragonR", "./image./Enemy/dragonR.bmp", 216, 204, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_ghostL", "./image./Enemy/ghostL.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_ghostR", "./image./Enemy/ghostR.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_minotaurL", "./image./Enemy/minotaurL.bmp", 900, 196, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_minotaurR", "./image./Enemy/minotaurR.bmp", 900, 196, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_skeletonL", "./image./Enemy/skeletonL.bmp", 384, 100, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_skeletonR", "./image./Enemy/skeletonR.bmp", 384, 100, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_skeleton_yellowL", "./image./Enemy/skeleton_yellowL.bmp", 432, 100, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_skeleton_yellowR", "./image./Enemy/skeleton_yellowR.bmp", 432, 100, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_slime_blueL", "./image./Enemy/slime_blueL.bmp", 416, 100, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_slime_blueR", "./image./Enemy/slime_blueR.bmp", 416, 100, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_slime_orangeL", "/.image./Enemy/slime_orangeL.bmp", 208, 104, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_slime_orangeR", "/.image./Enemy/slime_orangeR.bmp", 208, 104, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_wraithL.bmp", "./image./Enemy/wraithL.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_wraithR.bmp", "./image./Enemy/wraithR.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_zombieL.bmp", "./image./Enemy/zombieL.bmp", 1152, 100, 24, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_zombieR.bmp", "./image./Enemy/zombieR.bmp", 1152, 100, 24, 2, true, RGB(255, 0, 255));
}

void EnemyManager::AnimationAdd()
{
	//==================박 쥐 애 니 메 이 션=========================================
	int Bat_L_IDLE[] = { 0,1,2,3 };
	int Bat_L_Shadow[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("Bat_L_IDLE_Ani", "Enemy_batL", Bat_L_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Bat_L_Shadow_Ani", "Enemy_batL", Bat_L_Shadow, 4, 10, true);
	int Bat_R_IDLE[] = { 3,2,1,0 };
	int Bat_R_Shadow[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("Bat_R_IDLE_Ani", "Enemy_batR", Bat_R_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Bat_R_IDLE_Ani", "Enemy_batR", Bat_R_Shadow, 4, 10, true);
	//==================용 애 니 메 이 션============================================
	int Dragon_L_IDLE[] = { 0,1 };
	int Dragon_L_Shadow[] = { 2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("Dragon_L_IDLE_Ani", "Enemy_dragonL", Dragon_L_IDLE, 2, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Dragon_L_Shadow_Ani", "Enemy_dragonL", Dragon_L_Shadow, 2, 10, true);
	int Dragon_R_IDLE[] = { 1,0 };
	int Dragon_R_Shadow[] = { 3,2 };
	KEYANIMANAGER->addArrayFrameAnimation("Dragon_R_IDLE_Ani", "Enemy_dragonR", Dragon_R_IDLE, 2, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Dragon_R_Shadow_Ani", "Enemy_dragonR", Dragon_R_Shadow, 2, 10, true);
	//==================유 령 애 니 메 이 션==========================================
	int Ghost_L_IDLE[] = { 0,1 };
	int Ghost_L_Shadow[] = { 2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("Ghost_L_IDLE_Ani", "Enemy_ghostL", Ghost_L_IDLE, 2, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Ghost_L_Shadow_Ani", "Enemy_ghostL", Ghost_L_Shadow, 2, 10, true);
	int Ghost_R_IDLE[] = { 1,0 };
	int Ghost_R_Shadow[] = { 3,2 };
	KEYANIMANAGER->addArrayFrameAnimation("Ghost_R_IDLE_Ani", "Enemy_ghostL", Ghost_L_IDLE, 2, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Ghost_R_Shadow_Ani", "Enemy_ghostL", Ghost_L_Shadow, 2, 10, true);
	//=================미노타우로스 애 니 메 이 션======================================
	int Minotaur_L_IDLE[] = { 0,1,2 };
	int Minotaur_L_DISCOVERY[] = { 3 };
	int Minotaur_L_RUSH[] = { 4 };
	int Minotaur_L_STUN[] = { 5,6,7,8 };

	int Minotaur_L_Shadow_IDLE[] = { 9,10,11 };
	int Minotaur_L_Shadow_DISCOVERY[] = { 12 };
	int Minotaur_L_Shadow_RUSH[] = { 13 };
	int Minotaur_L_Shadow_STUN[] = { 14,15,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_L_IDLE_Ani", "Enemy_minotaurL", Minotaur_L_IDLE, 3, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_L_DISCOVERY_Ani", "Enemy_minotaurL", Minotaur_L_DISCOVERY, 1, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_L_RUSH_Ani", "Enemy_minotaurL", Minotaur_L_RUSH, 1, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_L_STUN_Ani", "Enemy_minotaurL", Minotaur_L_STUN, 4, 10, true);

	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_L_Shadow_IDLE_Ani", "Enemy_minotaurL", Minotaur_L_Shadow_IDLE, 3, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_L_Shadow_DISCOVERY_Ani", "Enemy_minotaurL", Minotaur_L_Shadow_DISCOVERY, 1, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_L_Shadow_RUSH_Ani", "Enemy_minotaurL", Minotaur_L_Shadow_RUSH, 1, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_L_Shadow_STUN_Ani", "Enemy_minotaurL", Minotaur_L_Shadow_STUN, 4, 10, true);
	//////////////////////////////////////////////////////////////////////////////////
	int Minotaur_R_IDLE[] = { 8,7,6 };
	int Minotaur_R_DISCOVERY[] = { 5 };
	int Minotaur_R_RUSH[] = { 4 };
	int Minotaur_R_STUN[] = { 3,2,1,0 };

	int Minotaur_R_Shadow_IDLE[] = { 17,16,15 };
	int Minotaur_R_Shadow_DISCOVERY = { 14 };
	int Minotaur_R_Shadow_RUSH[] = { 13 };
	int Minotaur_R_Shadow_STUN[] = { 12,11,10,9 };

	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_R_IDLE_Ani", "Enemy_minotaurR", Minotaur_L_IDLE, 3, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_R_DISCOVERY_Ani", "Enemy_minotaurR", Minotaur_L_DISCOVERY, 1, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_R_RUSH_Ani", "Enemy_minotaurR", Minotaur_L_RUSH, 1, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_R_STUN_Ani", "Enemy_minotaurR", Minotaur_L_STUN, 4, 10, true);

	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_R_Shadow_IDLE_Ani", "Enemy_minotaurL", Minotaur_L_Shadow_IDLE, 3, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_R_Shadow_DISCOVERY_Ani", "Enemy_minotaurL", Minotaur_L_Shadow_DISCOVERY, 1, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_R_Shadow_RUSH_Ani", "Enemy_minotaurL", Minotaur_L_Shadow_RUSH, 1, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_R_Shadow_STUN_Ani", "Enemy_minotaurL", Minotaur_L_Shadow_STUN, 4, 10, true);
	//====================스 켈 레 톤 애 니 메 이 션============================================
	int Skeleton_L_IDLE[] = { 0,1,2,3 };
	int Skeleton_L_ATTACK[] = { 4,5,6,7 };

	int Skeleton_L_Shadow_IDLE[] = { 8,9,10,11 };
	int Skeleton_L_Shadow_ATTACK[] = { 12,13,14,15 };

	KEYANIMANAGER->addArrayFrameAnimation("skeleton_L_IDLE_Ani", "Enemy_skeletonL", Skeleton_L_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Skeleton_L_ATTACK_Ani", "Enemy_skeletonL", Skeleton_L_ATTACK, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Skeleton_L_Shadow_IDLE_Ani", "Enemy_skeletonL", Skeleton_L_Shadow_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Skeleton_L_Shadow_ATTACK_Ani", "Enemy_skeletonL", Skeleton_L_Shadow_ATTACK, 4, 10, true);
	//////////////////////////////////////////////////////////////////////////////////////////////
	int Skeleton_R_IDLE[] = { 7,6,5,4 };
	int Skeleton_R_ATTACK[] = { 3,2,1,0 };

	int Skeleton_R_Shadow_IDLE[] = { 15,14,13,12 };
	int Skeleton_R_Shadow_ATTACK[] = { 11,10,9,8 };

	KEYANIMANAGER->addArrayFrameAnimation("skeleton_R_IDLE_Ani", "Enemy_skeletonR", Skeleton_R_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Skeleton_R_ATTACK_Ani", "Enemy_skeletonR", Skeleton_R_ATTACK, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Skeleton_R_Shadow_IDLE_Ani", "Enemy_skeletonR", Skeleton_R_Shadow_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Skeleton_R_Shadow_ATTACK_Ani", "Enemy_skeletonR", Skeleton_R_Shadow_ATTACK, 4, 10, true);
	//====================노랑 스켈레톤 애 니 메 이 션==============================================
	int skeleton_yellow_L_IDLE[] = { 0,1,2,3 };
	int skeleton_yellow_L_ATTACK[] = { 4,5,6,7 };
	int skeleton_yellow_L_ESCAPE[] = { 8 };

	int skeleton_yellow_L_Shadow_IDLE[] = { 9,10,11,12 };
	int skeleton_yellow_L_Shadow_ATTACK[] = { 13,14,15,16 };
	int skeleton_yellow_L_Shadow_ESCAPE[] = { 17 };

	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_L_IDLE_Ani", "Enemy_skeleton_yellowL", skeleton_yellow_L_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_L_ATTACK_Ani", "Enemy_skeleton_yellowL", skeleton_yellow_L_ATTACK, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_L_ESCAPE_Ani", "Enemy_skeleton_yellowL", skeleton_yellow_L_ESCAPE, 1, 10, true);

	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_L_Shadow_IDLE_Ani", "Enemy_skeleton_yellowL", skeleton_yellow_L_Shadow_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_L_Shadow_ATTACK_Ani", "Enemy_skeleton_yellowL", skeleton_yellow_L_Shadow_ATTACK, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_L_Shadow_ESCAPE_Ani", "Enemy_skeleton_yellowL", skeleton_yellow_L_Shadow_ESCAPE, 1, 10, true);
	//////////////////////////////////////////////////////////////////////////////////////////////////
	int skeleton_yellow_R_IDLE[] = { 8,7,6,5 };
	int skeleton_yellow_R_ATTACK[] = { 4,3,2,1 };
	int skeleton_yellow_R_ESCAPE[] = { 0 };

	int skeleton_yellow_R_Shadow_IDLE[] = { 17,16,15,14 };
	int skeleton_yellow_R_Shadow_ATTACK[] = { 13,12,11,10 };
	int skeleton_yellow_R_Shadow_ESCAPE[] = { 9 };

	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_R_IDLE_Ani", "Enemy_skeleton_yellowR", skeleton_yellow_R_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_R_ATTACK_Ani", "Enemy_skeleton_yellowR", skeleton_yellow_R_ATTACK, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_R_ESCAPE_Ani", "Enemy_skeleton_yellowR", skeleton_yellow_R_ESCAPE, 1, 10, true);

	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_R_Shadow_IDLE_Ani", "Enemy_skeleton_yellowR", skeleton_yellow_R_Shadow_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_R_Shadow_ATTACK_Ani", "Enemy_skeleton_yellowR", skeleton_yellow_R_Shadow_ATTACK, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_R_Shadow_ESCAPE_Ani", "Enemy_skeleton_yellowR", skeleton_yellow_R_Shadow_ESCAPE, 1, 10, true);
	//==============================파랑 슬 라 임 애 니 메 이 션======================================
	int Enemy_slime_blue_L_IDLE[] = { 0,1,2,3,4,5,6,7 };
	int Enemy_slime_blue_L_Shadow_IDLE[] = { 8,9,10,11,12,13,14,15 };

	KEYANIMANAGER->addArrayFrameAnimation("Enemy_slime_blue_L_IDLE_Ani", "Enemy_slime_blueL", Enemy_slime_blue_L_IDLE, 8, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_slime_blue_L_Shadow_IDLE_Ani", "Enemy_slime_blueL", Enemy_slime_blue_L_Shadow_IDLE, 8, 10, true);

	int Enemy_slime_blue_R_IDLE[] = { 7,6,5,4,3,2,1,0 };
	int Enemy_slime_blue_R_Shadow_IDLE[] = { 15,14,13,12,11,10,9,8 };

	KEYANIMANAGER->addArrayFrameAnimation("Enemy_slime_blue_R_IDLE_Ani", "Enemy_slime_blueR", Enemy_slime_blue_R_IDLE, 8, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_slime_blue_R_Shadow_IDLE_Ani", "Enemy_slime_blueR", Enemy_slime_blue_R_Shadow_IDLE, 8, 10, true);
	//==============================노랑 슬라임 애 니 메 이 션========================================
	int Enemy_slime_orange_L_IDLE[] = { 0,1,2,3 };
	int Enemy_slime_orange_L_Shadow_IDLE[] = { 4,5,6,7 };

	KEYANIMANAGER->addArrayFrameAnimation("Enemy_slime_orange_L_IDLE_Ani", "Enemy_slime_orangeL", Enemy_slime_orange_L_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_slime_orange_L_Shadow_IDLE_Ani", "Enemy_slime_orangeL", Enemy_slime_orange_L_Shadow_IDLE, 4, 10, true);

	int Enemy_slime_orange_R_IDLE[] = { 3,2,1,0 };
	int Enemy_slime_orange_R_Shadow_IDLE[] = { 7,6,5,4 };

	KEYANIMANAGER->addArrayFrameAnimation("Enemy_slime_orange_R_IDLE_Ani", "Enemy_slime_orangeR", Enemy_slime_orange_R_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_slime_orange_R_Shadow_IDLE_Ani", "Enemy_slime_orangeR", Enemy_slime_orange_R_Shadow_IDLE, 4, 10, true);
	//==============================레 이 스 애 니 메 이 션============================================
	int Enemy_wraith_L_IDLE[] = { 0,1 };
	int Enemy_wraith_L_ATTACK[] = { 2 };

	KEYANIMANAGER->addArrayFrameAnimation("Enemy_wraith_L_IDLE_Ani", "Enemy_wraithL", Enemy_wraith_L_IDLE, 2, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_wraith_L_ATTACK_Ani", "Enemy_wraithL", Enemy_wraith_L_ATTACK, 1, 10, true);

	int Enemy_wraith_R_IDLE[] = { 2,1 };
	int Enemy_wraith_R_ATTACK[] = { 0 };

	KEYANIMANAGER->addArrayFrameAnimation("Enemy_wraith_R_IDLE_Ani", "Enemy_wraithR", Enemy_wraith_R_IDLE, 2, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_wraith_R_ATTACK_Ani", "Enemy_wraithR", Enemy_wraith_R_ATTACK, 1, 10, true);
	//==============================좀 비 애 니 메 이 션===============================================
	int Enemy_zombie_L_UP[] = {0,1,2,3,4,5,6,7,8};
	int Enemy_zombie_L_MOVE[] = { 9,10,11,12,13,14,15};
}
