#include "stdafx.h"
#include "EnemyManager.h"

HRESULT EnemyManager::init()
{
	
	return S_OK;
}

void EnemyManager::release()
{
}

void EnemyManager::update()
{
}

void EnemyManager::render()
{
	

}

void EnemyManager::EnemyCreate()
{
}

void EnemyManager::EnemyCreate(float x, float y, const char* EnemyName)
{

}

void EnemyManager::imageReset()
{
	IMAGEMANAGER->addFrameImage("Enemy_bat", "./image./Enemy/bat.bmp", 96, 48, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_bat_Miniboss", "./image./Enemy/bat_miniboss.bmp", 144, 48, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_dragon", "./image./Enemy/dragon.bmp", 108, 102, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_ghost", "./image./Enemy/ghost.bmp", 48, 48, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_minotaur", "./image./Enemy/minotaur.bmp", 450, 98, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_monkey", "./image./Enemy/monkey.bmp", 150, 48, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_skeleton", "./image./Enemy/skeleton.bmp", 192, 50, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_skeleton_yellow", "./image./Enemy/skeleton_yellow.bmp", 216, 50, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_slime_blue", "./image./Enemy/slime_blue.bmp", 208, 50, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_slime_orange", "./image./Enemy/slime_orange.bmp", 104, 52, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_wraith", "./image./Enemy/wraith.bmp", 72, 48, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_zombie", "./image./Enemy/zombie.bmp", 576, 50, 24, 2, true, RGB(255, 0, 255));
}
