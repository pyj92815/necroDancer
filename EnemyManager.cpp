#include "stdafx.h"
#include "EnemyManager.h"

HRESULT EnemyManager::init()
{
	imageAdd();	//이미지 추가 함수
	Enemy* enemy;
	enemy = new Enemy_Bat;
	enemy->init();
	_vEnemy.push_back(enemy);

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
	Bat->init();
	_vEnemy.push_back(Bat);
}
void EnemyManager::Enemy_Dragon_Create(float x, float y)
{
	Enemy* Dragon;
	Dragon = new Enemy_Dragon;
	Dragon->init();
	_vEnemy.push_back(Dragon);
}
void EnemyManager::Enemy_Ghost_Create(float x, float y)
{
	Enemy* Ghost;
	Ghost = new Enemy_Ghost;
	Ghost->init();
	_vEnemy.push_back(Ghost);
}
void EnemyManager::Enemy_Minotaur_Create(float x, float y)
{
	Enemy* Minotaur;
	Minotaur = new Enemy_Minotaur;
	Minotaur->init();
	_vEnemy.push_back(Minotaur);
}
void EnemyManager::Enemy_Skeleton_Create(float x, float y)
{
	Enemy* Skeleton;
	Skeleton = new Enemy_Skeleton;
	Skeleton->init();
	_vEnemy.push_back(Skeleton);
}
void EnemyManager::Enemy_Skeleton_Yellow_Create(float x, float y)
{
	Enemy* Skeleton_Yellow;
	Skeleton_Yellow = new Enemy_Skeleton_Yellow;
	Skeleton_Yellow->init();
	_vEnemy.push_back(Skeleton_Yellow);
}
void EnemyManager::Enemy_Slime_Blue_Create(float x, float y)
{
	Enemy* Slime_Blue;
	Slime_Blue = new Enemy_Slime_Blue;
	Slime_Blue->init();
	_vEnemy.push_back(Slime_Blue);
}
void EnemyManager::Enemy_Slime_Orange_Create(float x, float y)
{
	Enemy* Slime_Orange;
	Slime_Orange = new Enemy_Slime_Orange;
	Slime_Orange->init();
	_vEnemy.push_back(Slime_Orange);
}
void EnemyManager::Enemy_Wraith_Create(float x, float y)
{
	Enemy* Wraith;
	Wraith = new Enemy_Warith;
	Wraith->init();
	_vEnemy.push_back(Wraith);
}
void EnemyManager::Enemy_Zombie_Create(float x, float y)
{
	Enemy* Zombie;
	Zombie = new Enemy_Zombie;
	Zombie->init();
	_vEnemy.push_back(Zombie);
}
