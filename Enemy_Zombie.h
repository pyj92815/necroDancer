#pragma once
#include"Enemy.h"

class Enemy_Zombie:public Enemy
{
public:
	void Action();
	void Move();
	void AniChange();
};

