#include "stdafx.h"
#include "EnemyManager.h"
#include "player.h"
HRESULT EnemyManager::init()
{
	imageAdd();	//이미지 추가 함수
	AnimationAdd(); //애니메이션 추가 함수
	임시enemy생성();
	_player = new player;

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
		//플레이어의 좌표값을 전달
		(*_viEnemy)->setPlayerInfo(_player->getPlayer().x, _player->getPlayer().y, _player->getPlayer().idx, _player->getPlayer().idy);
		cout << _player->getPlayer().idx << endl;
		
	}
	EnemyRemove();
	EnemyInspection();

}

void EnemyManager::render()
{
	for (_viEnemy = _vEnemy.begin();_viEnemy != _vEnemy.end();++_viEnemy)
	{
		(*_viEnemy)->render();
		
	}

}

void EnemyManager::EnemyRemove()
{
	for (_viEnemy = _vEnemy.begin();_viEnemy != _vEnemy.end();)
	{
		if ((*_viEnemy)->getEnemyInfo()->state == enemyState::STATE_DIE)
		{
			_vEnemy.erase(_viEnemy);
			break;
		}
		else
		{
			++_viEnemy;
		}
	}
}

//for문을 도느라 bool값이 true false 반복하며 바뀜 else문을 바꿔야 할거 같음
void EnemyManager::EnemyInspection()
{
	for (int i = 0;i < _vEnemy.size();++i)
	{
		for (int j = 0;j < _vEnemy.size();++j)
		{
			//오른쪽에 에너미가 있으면
			if (_vEnemy[i]->getEnemyInfo()->idx + 1 == _vEnemy[j]->getEnemyInfo()->idx && _vEnemy[i]->getEnemyInfo()->idy == _vEnemy[j]->getEnemyInfo()->idy)
			{
				_vEnemy[i]->getEnemyInfo()->right = true;
			}
			else
			{
				_vEnemy[i]->getEnemyInfo()->right = false;
			}
			//왼쪽에 에너미가 있으면
			if (_vEnemy[i]->getEnemyInfo()->idx - 1 == _vEnemy[j]->getEnemyInfo()->idx && _vEnemy[i]->getEnemyInfo()->idy == _vEnemy[j]->getEnemyInfo()->idy)
			{
				_vEnemy[i]->getEnemyInfo()->left = true;
			}
			else
			{
				_vEnemy[i]->getEnemyInfo()->left = false;
			}
			//위쪽에 에너미가 있으면
			if (_vEnemy[i]->getEnemyInfo()->idx == _vEnemy[j]->getEnemyInfo()->idx && _vEnemy[i]->getEnemyInfo()->idy-1 == _vEnemy[j]->getEnemyInfo()->idy)
			{
				_vEnemy[i]->getEnemyInfo()->up = true;
			}
			else
			{
				_vEnemy[i]->getEnemyInfo()->up = false;
			}
			//아래쪽에 에너미가 있으면
			if (_vEnemy[i]->getEnemyInfo()->idx == _vEnemy[j]->getEnemyInfo()->idx && _vEnemy[i]->getEnemyInfo()->idy+1 == _vEnemy[j]->getEnemyInfo()->idy)
			{
				_vEnemy[i]->getEnemyInfo()->down = true;
			}
			else
			{
				_vEnemy[i]->getEnemyInfo()->down = false;
			}
		}
	}
}

void EnemyManager::임시enemy생성()
{
	_enemyType = EnemyType::BAT;
	EnemyCreate(10, 8, _enemyType);
	_enemyType = EnemyType::DRAGON;
	EnemyCreate(12, 8, _enemyType);
	_enemyType = EnemyType::GHOST;
	EnemyCreate(14, 8, _enemyType);
	_enemyType = EnemyType::MINOTAUR;
	EnemyCreate(16, 8, _enemyType);
	_enemyType = EnemyType::SKELETON;
	EnemyCreate(10, 10, _enemyType);
	_enemyType = EnemyType::SKELETON_YELLOW;
	EnemyCreate(12, 10, _enemyType);
	_enemyType = EnemyType::SLIME_BLUE;
	EnemyCreate(14, 10, _enemyType);
	_enemyType = EnemyType::SLIME_ORANGE;
	EnemyCreate(16, 10, _enemyType);
	_enemyType = EnemyType::WRAITH;
	EnemyCreate(10, 12, _enemyType);
	_enemyType = EnemyType::ZOMBIE;
	EnemyCreate(12, 12, _enemyType);
}

void EnemyManager::EnemyCreate(float x, float y, EnemyType enemyType)
{
	switch (_enemyType)
	{
	case EnemyType::BAT:
		Enemy_Bat_Create(x, y);
		break;
	case EnemyType::DRAGON:
		Enemy_Dragon_Create(x, y);
		break;
	case EnemyType::GHOST:
		Enemy_Ghost_Create(x, y);
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

void EnemyManager::imageAdd()
{
	IMAGEMANAGER->addFrameImage("Enemy_bat", "image/Enemy/bat.bmp", 384, 96, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_dragon", "image/Enemy/dragon.bmp", 432, 204, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_ghost", "image/Enemy/ghost.bmp", 192, 96, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_minotaur", "image/Enemy/minotaur.bmp", 1800, 196, 18, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_skeleton", "image/Enemy/skeleton.bmp", 768, 100, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_skeleton_yellow", "image/Enemy/skeleton_yellow.bmp", 816, 100, 17, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_slime_blue", "image/Enemy/slime_blue.bmp", 416, 100, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_slime_orange", "image/Enemy/slime_orange.bmp", 208, 104, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_wraith", "image/Enemy/wraith.bmp", 288, 96, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_zombie", "image/Enemy/zombie.bmp", 1536, 100, 32, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Attack_LEFT", "image/particles/swipe_enemy_LEFT.bmp", 135, 24, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Attack_RIGHT", "image/particles/swipe_enemy_RIGHT.bmp", 135, 24, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Attack_UP", "image/particles/swipe_enemy_UP.bmp", 120, 27,5,1 , true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Attack_DOWN", "image/particles/swipe_enemy_DOWN.bmp", 120, 27,5, 1, true, RGB(255, 0, 255));

}
void EnemyManager::Enemy_Bat_Create(float x, float y)
{
	Enemy* Bat;
	Bat = new Enemy_Bat;
	Bat->EnemyCreate(x, y, 1.0f, 0.5f, "Enemy_bat", "Bat_L_IDLE_Ani");
	_vEnemy.push_back(Bat);
}
void EnemyManager::Enemy_Dragon_Create(float x, float y)
{
	Enemy* Dragon;
	Dragon = new Enemy_Dragon;
	Dragon->EnemyCreate(x, y, 4.0f, 2.0f, "Enemy_dragon", "Dragon_L_IDLE_Ani");
	_vEnemy.push_back(Dragon);
}
void EnemyManager::Enemy_Ghost_Create(float x, float y)
{
	Enemy* Ghost;
	Ghost = new Enemy_Ghost;
	Ghost->EnemyCreate(x, y, 1.0f, 1.0f, "Enemy_ghost", "Ghost_L_IDLE_Ani");
	_vEnemy.push_back(Ghost);
}
void EnemyManager::Enemy_Minotaur_Create(float x, float y)
{
	Enemy* Minotaur;
	Minotaur = new Enemy_Minotaur;
	Minotaur->EnemyCreate(x, y, 3.0f, 2.0f, "Enemy_minotaur", "Minotaur_L_IDLE_Ani");
	_vEnemy.push_back(Minotaur);
}
void EnemyManager::Enemy_Skeleton_Create(float x, float y)
{
	Enemy* Skeleton;
	Skeleton = new Enemy_Skeleton;
	Skeleton->EnemyCreate(x, y, 1.0f, 0.5f, "Enemy_skeleton", "skeleton_L_IDLE_Ani");
	_vEnemy.push_back(Skeleton);
}
void EnemyManager::Enemy_Skeleton_Yellow_Create(float x, float y)
{
	Enemy* Skeleton_Yellow;
	Skeleton_Yellow = new Enemy_Skeleton_Yellow;
	Skeleton_Yellow->EnemyCreate(x, y, 2.0f, 1.5f, "Enemy_skeleton_yellow", "skeleton_yellow_L_IDLE_Ani");
	_vEnemy.push_back(Skeleton_Yellow);
}
void EnemyManager::Enemy_Slime_Blue_Create(float x, float y)
{
	Enemy* Slime_Blue;
	Slime_Blue = new Enemy_Slime_Blue;
	Slime_Blue->EnemyCreate(x, y, 2.0f, 1.0f, "Enemy_slime_blue", "Enemy_slime_blue_IDLE_Ani", Direction::UP);
	_vEnemy.push_back(Slime_Blue);
}
void EnemyManager::Enemy_Slime_Orange_Create(float x, float y)
{
	Enemy* Slime_Orange;
	Slime_Orange = new Enemy_Slime_Orange;
	Slime_Orange->EnemyCreate(x, y, 1.0f, 0.5f, "Enemy_slime_orange", "Enemy_slime_orange_IDLE_Ani", Direction::RIGHT);
	_vEnemy.push_back(Slime_Orange);
}
void EnemyManager::Enemy_Wraith_Create(float x, float y)
{
	Enemy* Wraith;
	Wraith = new Enemy_Warith;
	Wraith->EnemyCreate(x, y, 1.0f, 0.5f, "Enemy_wraith", "Enemy_wraith_L_IDLE_Ani");
	_vEnemy.push_back(Wraith);
}
void EnemyManager::Enemy_Zombie_Create(float x, float y)
{
	Enemy* Zombie;
	Zombie = new Enemy_Zombie;

	if (RND->getInt(2) == 0)
	{
		Zombie->EnemyCreate(x, y, 1.0f, 1.0f, "Enemy_zombie", "Enemy_zombie_LEFT_Ani", Direction::LEFT);
	}
	else
	{
		Zombie->EnemyCreate(x, y, 1.0f, 1.0f, "Enemy_zombie", "Enemy_zombie_UP_Ani", Direction::UP);
	}

	_vEnemy.push_back(Zombie);
}

void EnemyManager::AnimationAdd()
{
	//==================박 쥐 애 니 메 이 션=========================================
	int Bat_L_IDLE[] = { 0,1,2,3 };
	int Bat_R_IDLE[] = { 7,6,5,4 };
	KEYANIMANAGER->addArrayFrameAnimation("Bat_L_IDLE_Ani", "Enemy_bat", Bat_L_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Bat_R_IDLE_Ani", "Enemy_bat", Bat_R_IDLE, 4, 10, true);
	int Bat_L_Shadow[] = { 8,9,10,11 };
	int Bat_R_Shadow[] = { 15,14,13,12 };
	KEYANIMANAGER->addArrayFrameAnimation("Bat_L_Shadow_IDLE_Ani", "Enemy_bat", Bat_L_Shadow, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Bat_R_Shadow_IDLE_Ani", "Enemy_bat", Bat_R_Shadow, 4, 10, true);
	//==================용 애 니 메 이 션============================================
	int Dragon_L_IDLE[] = { 0,1 };
	int Dragon_R_IDLE[] = { 3,2 };
	KEYANIMANAGER->addArrayFrameAnimation("Dragon_L_IDLE_Ani", "Enemy_dragon", Dragon_L_IDLE, 2, 2, true);
	KEYANIMANAGER->addArrayFrameAnimation("Dragon_R_IDLE_Ani", "Enemy_dragon", Dragon_R_IDLE, 2, 2, true);
	int Dragon_L_Shadow[] = { 4,5 };
	int Dragon_R_Shadow[] = { 7,6 };
	KEYANIMANAGER->addArrayFrameAnimation("Dragon_L_Shadow_IDLE_Ani", "Enemy_dragon", Dragon_L_Shadow, 2, 2, true);
	KEYANIMANAGER->addArrayFrameAnimation("Dragon_R_Shadow_IDLE_Ani", "Enemy_dragon", Dragon_R_Shadow, 2, 2, true);
	//==================유 령 애 니 메 이 션==========================================
	int Ghost_L_IDLE[] = { 0,1 };
	int Ghost_R_IDLE[] = { 3,2 };
	KEYANIMANAGER->addArrayFrameAnimation("Ghost_L_IDLE_Ani", "Enemy_ghost", Ghost_L_IDLE, 2, 5, true);
	KEYANIMANAGER->addArrayFrameAnimation("Ghost_R_IDLE_Ani", "Enemy_ghost", Ghost_L_IDLE, 2, 5, true);
	int Ghost_R_Shadow[] = { 4,5 };
	int Ghost_L_Shadow[] = { 7,6 };
	KEYANIMANAGER->addArrayFrameAnimation("Ghost_L_Shadow_IDLE_Ani", "Enemy_ghost", Ghost_L_Shadow, 2, 5, true);
	KEYANIMANAGER->addArrayFrameAnimation("Ghost_R_Shadow_IDLE_Ani", "Enemy_ghost", Ghost_L_Shadow, 2, 5, true);
	//=================미노타우로스 애 니 메 이 션======================================
	int Minotaur_L_IDLE[] = { 0,1,2,3 };
	int Minotaur_L_RUSH[] = { 4 };
	int Minotaur_L_STUN[] = { 5,6,7,8, };

	int Minotaur_R_IDLE[] = { 17,16,15,14 };
	int Minotaur_R_RUSH[] = { 13 };
	int Minotaur_R_STUN[] = { 12,11,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_L_IDLE_Ani", "Enemy_minotaur", Minotaur_L_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_L_RUSH_Ani", "Enemy_minotaur", Minotaur_L_RUSH, 1, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_L_STUN_Ani", "Enemy_minotaur", Minotaur_L_STUN, 4, 10, true);

	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_R_IDLE_Ani", "Enemy_minotaur", Minotaur_L_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_R_RUSH_Ani", "Enemy_minotaur", Minotaur_L_RUSH, 1, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_R_STUN_Ani", "Enemy_minotaur", Minotaur_L_STUN, 4, 10, true);
	//////////////////////////////////////////////////////////////////////////////////
	int Minotaur_L_Shadow_IDLE[] = { 18,19,20,21 };
	int Minotaur_L_Shadow_RUSH[] = { 22 };
	int Minotaur_L_Shadow_STUN[] = { 23,24,25,26 };

	int Minotaur_R_Shadow_IDLE[] = { 30,29,28,27 };
	int Minotaur_R_Shadow_RUSH[] = { 31 };
	int Minotaur_R_Shadow_STUN[] = { 35,34,33,32 };

	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_L_Shadow_IDLE_Ani", "Enemy_minotaur", Minotaur_L_Shadow_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_L_Shadow_RUSH_Ani", "Enemy_minotaur", Minotaur_L_Shadow_RUSH, 1, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_L_Shadow_STUN_Ani", "Enemy_minotaur", Minotaur_L_Shadow_STUN, 4, 10, true);

	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_R_Shadow_IDLE_Ani", "Enemy_minotaur", Minotaur_L_Shadow_IDLE, 4, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_R_Shadow_RUSH_Ani", "Enemy_minotaur", Minotaur_L_Shadow_RUSH, 1, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Minotaur_R_Shadow_STUN_Ani", "Enemy_minotaur", Minotaur_L_Shadow_STUN, 4, 10, true);
	//====================스 켈 레 톤 애 니 메 이 션============================================
	int Skeleton_L_IDLE[] = { 0,1,2,3,4,5,6,7 };
	int Skeleton_R_IDLE[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_L_IDLE_Ani", "Enemy_skeleton", Skeleton_L_IDLE, 8, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_R_IDLE_Ani", "Enemy_skeleton", Skeleton_R_IDLE, 8, 10, true);
	int Skeleton_L_Shadow_IDLE[] = { 31,30,29,28,27,26,25,24 };
	int Skeleton_R_Shadow_IDLE[] = { 16,17,18,19,20,21,22,23 };
	KEYANIMANAGER->addArrayFrameAnimation("Skeleton_L_Shadow_IDLE_Ani", "Enemy_skeleton", Skeleton_L_Shadow_IDLE, 8, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Skeleton_R_Shadow_IDLE_Ani", "Enemy_skeleton", Skeleton_R_Shadow_IDLE, 8, 10, true);
	//====================노랑 스켈레톤 애 니 메 이 션==============================================
	int skeleton_yellow_L_IDLE[] = { 0,1,2,3,4,5,6,7 };
	int skeleton_yellow_R_IDLE[] = { 15,14,13,12,11,10,9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_L_IDLE_Ani", "Enemy_skeleton_yellow", skeleton_yellow_L_IDLE, 8, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_R_IDLE_Ani", "Enemy_skeleton_yellow", skeleton_yellow_R_IDLE, 8, 10, true);
	int skeleton_yellow_L_Shadow_IDLE[] = { 16,17,18,19,20,21,22,23 };
	int skeleton_yellow_R_Shadow_IDLE[] = { 31,30,29,28,27,26,25,24 };
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_L_Shadow_IDLE_Ani", "Enemy_skeleton_yellow", skeleton_yellow_L_Shadow_IDLE, 8, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_R_Shadow_IDLE_Ani", "Enemy_skeleton_yellow", skeleton_yellow_R_Shadow_IDLE, 8, 10, true);
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	int skeleton_yellow_RUNAWAY[] = { 16 };
	int skeleton_yellow_Shadow_RUNAWAY[] = { 33 };
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_RUNAWAY_Ani", "Enemy_skeleton_yellow", skeleton_yellow_RUNAWAY, 1, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("skeleton_yellow_Shadow_RUNAWAY_Ani", "Enemy_skeleton_yellow", skeleton_yellow_Shadow_RUNAWAY, 1, 10, true);
	//==============================파랑 슬 라 임 애 니 메 이 션======================================
	int Enemy_slime_blue_L_IDLE[] = { 0,1,2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_slime_blue_IDLE_Ani", "Enemy_slime_blue", Enemy_slime_blue_L_IDLE, 8, 10, true);
	int Enemy_slime_blue_L_Shadow_IDLE[] = { 8,9,10,11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_slime_blue_Shadow_IDLE_Ani", "Enemy_slime_blue", Enemy_slime_blue_L_Shadow_IDLE, 8, 10, true);
	//==============================노랑 슬라임 애 니 메 이 션========================================
	int Enemy_slime_orange_L_IDLE[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_slime_orange_IDLE_Ani", "Enemy_slime_orange", Enemy_slime_orange_L_IDLE, 4, 10, true);
	int Enemy_slime_orange_L_Shadow_IDLE[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_slime_orange_Shadow_IDLE_Ani", "Enemy_slime_orange", Enemy_slime_orange_L_Shadow_IDLE, 4, 10, true);
	//==============================레 이 스 애 니 메 이 션============================================
	int Enemy_wraith_L_IDLE[] = { 0,1,2 };
	int Enemy_wraith_R_IDLE[] = { 5,4,3 };
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_wraith_L_IDLE_Ani", "Enemy_wraith", Enemy_wraith_L_IDLE, 3, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_wraith_R_IDLE_Ani", "Enemy_wraith", Enemy_wraith_R_IDLE, 3, 10, true);
	int Enemy_wraith_L_Shadow_IDLE[] = { 6,7,8 };
	int Enemy_wraith_R_Shadow_IDLE[] = { 11,10,9 };
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_wraith_L_Shadow_IDLE_Ani", "Enemy_wraith", Enemy_wraith_L_Shadow_IDLE, 3, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_wraith_R_Shadow_IDLE_Ani", "Enemy_wraith", Enemy_wraith_R_Shadow_IDLE, 3, 10, true);
	//==============================좀 비 애 니 메 이 션===============================================
	int Enemy_zombie_UP[] = { 0,1,2,3,4,5,6,7 };
	int Enemy_zombie_LEFT[] = { 8,9,10,11,12,13,14,15 };
	int Enemy_zombie_RIGHT[] = { 16,17,18,19,20,21,22,23 };
	int Enemy_zombie_DOWN[] = { 24,25,26,27,28,29,30,31 };

	int Enemy_zombie_Shadow_UP[] = { 32,33,34,35,36,37,38,39 };
	int Enemy_zombie_Shadow_LEFT[] = { 40,41,42,43,44,45,46,47 };
	int Enemy_zombie_Shadow_RIGHT[] = { 48,49,50,51,52,53,54,55 };
	int Enemy_zombie_Shadow_DOWN[] = { 56,57,58,59,60,61,62,63 };
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_zombie_UP_Ani", "Enemy_zombie", Enemy_zombie_UP, 8, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_zombie_LEFT_Ani", "Enemy_zombie", Enemy_zombie_LEFT, 8, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_zombie_RIGHT_Ani", "Enemy_zombie", Enemy_zombie_RIGHT, 8, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_zombie_DOWN_Ani", "Enemy_zombie", Enemy_zombie_DOWN, 8, 10, true);

	KEYANIMANAGER->addArrayFrameAnimation("Enemy_zombie_Shadow_UP_Ani", "Enemy_zombie", Enemy_zombie_Shadow_UP, 8, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_zombie_Shadow_LEFT_Ani", "Enemy_zombie", Enemy_zombie_Shadow_LEFT, 8, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_zombie_Shadow_RIGHT_Ani", "Enemy_zombie", Enemy_zombie_Shadow_RIGHT, 8, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_zombie_Shadow_DOWN_Ani", "Enemy_zombie", Enemy_zombie_Shadow_DOWN, 8, 10, true);
	//======================에너미 공격 애니메이션=======================================================
	int Enemy_Attack_LEFT[] = {4,3,2,1,0};
	int Enemy_Attack_RIGHT[] = {0,1,2,3,4};
	int Enemy_Attack_UP[] = {4,3,2,1,0};
	int Enemy_Attack_DOWN[] = {0,1,2,3,4};
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_Attack_LEFT_Ani", "Enemy_Attack_LEFT", Enemy_Attack_LEFT, 5, 10, false);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_Attack_RIGHT_Ani", "Enemy_Attack_RIGHT", Enemy_Attack_RIGHT, 5, 10, false);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_Attack_UP_Ani", "Enemy_Attack_UP", Enemy_Attack_UP, 5, 10, false);
	KEYANIMANAGER->addArrayFrameAnimation("Enemy_Attack_DOWN_Ani", "Enemy_Attack_DOWN", Enemy_Attack_DOWN, 5, 10, false);
}

