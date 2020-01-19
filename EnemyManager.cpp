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
	case EnemyType::DEATH_METAL:
		Enemy_Death_Metal_Create(x, y);
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

void EnemyManager::Enemy_Death_Metal_Create(float x, float y)
{
	Enemy* Death_Metal;
	Death_Metal = new Enemy_Boss;
	Death_Metal->init();
	_vEnemy.push_back(Death_Metal);

}

void EnemyManager::imageAdd()
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

void EnemyManager::AnimationAdd()
{
	int Bat_IDLE[] = { 0,1,2,3 };

	
}
