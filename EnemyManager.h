#pragma once
#include"singletonBase.h"
#include"Enemy_Bat.h"
#include"Enemy_Bat_MiniBoss.h"
#include"Enemy_Dragon.h"
#include"Enemy_Ghost.h"
#include"Enemy_Minotaur.h"
#include"Enemy_Monkey.h"
#include"Enemy_Skeleton.h"
#include"Enemy_Skeleton_Yellow.h"
#include"Enemy_Slime_Blue.h"
#include"Enemy_Slime_Orange.h"
#include"Enemy_Warith.h"
#include"Enemy_Zombie.h"
class EnemyManager:public singletonBase<EnemyManager>
{
private:
public:
	EnemyManager() {};
	~EnemyManager() {};
	
	HRESULT init();
	void release();
	void update();
	void render();

	void EnemyCreate();
	void EnemyCreate(float x,float y,const char* EnemyName);

	void imageReset();

};


