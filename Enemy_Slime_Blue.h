#pragma once
#include"Enemy.h"
class Enemy_Slime_Blue:public Enemy
{
public:
	void Action();
	void Move();
	void moveAction();
	void enemyAngle();
	void Attack();
	void AniChange();
};

